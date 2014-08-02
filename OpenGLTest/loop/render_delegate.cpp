//
//  render_delegate.cpp
//  OpenGLTest
//
//  Created by Laszlo Korte on 28.07.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "render_delegate.hpp"
#include "../graphics/texture.hpp"
#include "../terrain/terrain.hpp"


#define glm_detail_intrinsic_integer
#include "glm/glm.hpp"

const GLchar* vertexShaderSource[] = {
#include "../shaders/base.vsh"
};


const GLchar* fragmentShaderSource[] = {
#include "../shaders/base.fsh"
};

SceneDelegate::SceneDelegate() : keyboardAdapter(keyboard), mouseAdapter(mouse), scene{.movement = FirstPersonMovement(scene.camera)} {
    
}

SceneDelegate::~SceneDelegate() {

}

void SceneDelegate::beforeUpdate(GameLoop &l) {
    keyboard.update();
    mouse.update();
}

void SceneDelegate::handleEvent(SDL_Event &e) {
    switch( e.type ){
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
        case SDL_MOUSEWHEEL:
        case SDL_MOUSEMOTION:
            mouseAdapter.processEvent(e);
            break;
            
        case SDL_KEYDOWN:
        case SDL_KEYUP:
            keyboardAdapter.processEvent(e);
            break;
    }

}

void SceneDelegate::setViewport(int w, int h) {
    screen.width = w;
    screen.height = h;
}

bool SceneDelegate::setup(GameLoop &l) {

    /* Enable smooth shading */
    glShadeModel( GL_SMOOTH );

    /* Set the background black */
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    
    /* Depth buffer setup */
    glClearDepth( 1.0f );
    
    glEnable(GL_TEXTURE_2D);
    
    glEnable(GL_CULL_FACE);
    glEnable( GL_BLEND );
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    /* Enables Depth Testing */
    glEnable( GL_DEPTH_TEST );
    /* The Type Of Depth Test To Do */
    glDepthFunc( GL_LEQUAL );


    /* Really Nice Perspective Calculations */
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
    
    try {
        scene.shader = std::make_shared<Shader>(vertexShaderSource,fragmentShaderSource);
    } catch (ShaderException e) {
        std::cerr << "Error loading shader: " << e.error << "\n";
        exit(0);
    }
    scene.root = std::make_shared<Group>();
    
    auto base = std::string(SDL_GetBasePath());
    std::string pathD = base + "texture-d.png";
    std::string pathS = base + "texture-s.png";
    std::string pathE = base + "texture-e.png";

    Texture d(pathD);
    Texture s(pathS);
    Texture e(pathE);
    auto m = std::make_shared<Material>(std::move(d), std::move(e), std::move(s), 10);
    
    Texture cd(base + "cylinder-d.png");
    Texture cs(base + "cylinder-s.png");
    Texture ce(base + "cylinder-e.png");
    auto cm = std::make_shared<Material>(std::move(cd), std::move(ce), std::move(cs), 10);

    scene.cube = std::make_shared<Model>(mesh::makeCube(), scene.shader, m);
    scene.cube->scale = glm::vec3(10,10,10);
    scene.root->add(scene.cube);
    scene.cube->position = glm::vec3(0.0f,10.f,0.f);
    
    auto cyl = std::make_shared<Model>(mesh::makeCylinder(40, 2, 1), scene.shader, cm);
    cyl->rotation = glm::rotate(glm::quat(), glm::radians(235.f), glm::vec3(0,1,0)) * glm::rotate(glm::quat(), glm::radians(90.f), glm::vec3(1,0,0));
    cyl->scale = glm::vec3(5,5,5);
    cyl->position = glm::vec3(7.0f,4.f,30.f);
    
    scene.root->add(cyl);
    
    auto pyr = std::make_shared<Model>(mesh::makePyramid(), scene.shader, m);
    pyr->scale = glm::vec3(10,10,10);
    pyr->position = glm::vec3(-23.0f,10.f,30.f);
    
    scene.root->add(pyr);
    
    auto terr = std::make_shared<Model>(terrain::loadTerrain(base+"terrain.png"), scene.shader, m);
    terr->scale = glm::vec3(2,2,2);
    terr->position = glm::vec3(0,-20.f,0);
    
    scene.root->add(terr);
   
    
    renderer.projection = glm::perspective(glm::radians(65.0f),16/9.0f,2.f, 400.0f);
    scene.camera.position = glm::vec3(40.f,0.f,21.f);
    scene.movement.lookAt(glm::vec3(0,0,20));
    
    return true;
}

void SceneDelegate::teardown(GameLoop &l) {
}

void SceneDelegate::update(GameLoop &l) {
    glm::vec2 dir(0,0);
    
    if(keyboard.isDown(keyboard::LEFT_ARROW) || keyboard.isDown(keyboard::LETTER_A)) {
        dir.x+=1;
    }
    if(keyboard.isDown(keyboard::RIGHT_ARROW) || keyboard.isDown(keyboard::LETTER_D)) {
        dir.x-=1;
    }
    
    if(keyboard.isDown(keyboard::UP_ARROW) || keyboard.isDown(keyboard::LETTER_W)) {
        dir.y+=1;
    }
    if(keyboard.isDown(keyboard::DOWN_ARROW) || keyboard.isDown(keyboard::LETTER_S)) {
        dir.y-=1;
    }
    
    if(glm::length(dir)) {
        if(moveDelay<0.25) {
            moveDelay+=0.02;
        }
    } else if(moveDelay>0) {
        moveDelay-=0.02;
    }
    
    scene.movement.move(dir, moveDelay);
    
    if(keyboard.isDown(keyboard::ENTER)) {
        scene.movement.lookAt(glm::vec3(0,0,0));
    }
    
    if(mouse.delta.x != 0) {
        scene.movement.rotateHorizontally(glm::radians(.3f*mouse.delta.x));
    }
    if(mouse.delta.y != 0) {
        scene.movement.rotateVertically(glm::radians(.3f*mouse.delta.y));
    }
    
    
    int camHeight = 5;
    if(physic.position.y == camHeight) {
        if(keyboard.pressed(keyboard::SPACE)) {
            physic.velocity.y = 0.25;
        } else {
            physic.velocity *= 0.9;
        }
    } else {
    
    }
    
    
    physic.position = scene.camera.position;
    
    physic.velocity += .001f*physic.acceleration;
    physic.position += physic.velocity;
    
    if(physic.position.y < camHeight) {
        physic.position.y = camHeight;
        physic.velocity.y = 0;
    }
    
    scene.camera.position = physic.position;
    scene.camera.dirty = true;
    
    updater.update(*scene.root);
    refresher.refresh(*scene.root, true);
}

void SceneDelegate::render() {
    adjustViewport();
    
    /* Set the background black */
    glClearColor( .1f, .1f, .1f, 0 );
    /* Clear The Screen And The Depth Buffer */
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    renderer.viewMatrix = scene.camera.viewMatrix();
    renderer.cameraPosition.X = scene.camera.position.x;
    renderer.cameraPosition.Y = scene.camera.position.y;
    renderer.cameraPosition.Z = scene.camera.position.z;
    scene.root->accept(renderer);
}

void SceneDelegate::afterRender() const {
}

void SceneDelegate::adjustViewport() const {
    if (screen.height * 16 > screen.width * 9) {
        int newWidth = screen.height * 16 / 9;
        glViewport(-(newWidth - screen.width) / 2, 0, newWidth,
                   screen.height);
    } else {
        int newHeight = screen.width * 9 / 16;
        glViewport(0, -(newHeight - screen.height) / 2,
                   screen.width, newHeight);
    }
}
