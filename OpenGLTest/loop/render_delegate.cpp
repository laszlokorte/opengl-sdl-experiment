//
//  render_delegate.cpp
//  OpenGLTest
//
//  Created by Laszlo Korte on 28.07.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "render_delegate.hpp"


const GLchar* vertexShaderSource[] = {
#include "../shaders/base.vsh"
};


const GLchar* fragmentShaderSource[] = {
#include "../shaders/base.fsh"
};

SceneDelegate::SceneDelegate() {
    
}

SceneDelegate::~SceneDelegate() {
    
}

void SceneDelegate::handleEvent(SDL_Event &e) {
    switch( e.type ){
        case SDL_MOUSEBUTTONDOWN:
            mouse.down = true;
            scene.cube->scale = glm::vec3(1.5,1.5,1.5);
            break;
        case SDL_MOUSEBUTTONUP:
            scene.cube->scale = glm::vec3(1);
            mouse.down = false;
            break;
        case SDL_KEYDOWN:
            switch( e.key.keysym.sym ) {
                case SDLK_LEFT:
                    //movement.left = glm::vec3(0.05,0,0);
                    break;
                case SDLK_RIGHT:
                    //movement.right = glm::vec3(-0.05,0,0);
                    break;
                case SDLK_UP:
                    //movement.up = glm::vec3(0,-0.05,0);
                    break;
                case SDLK_DOWN:
                    //movement.down = glm::vec3(0,0.05,0);
                    break;
                case SDLK_q:
                    //movement.rotLeft = true;
                    break;
                case SDLK_e:
                    //movement.rotRight = true;
                    break;
                case SDLK_w:
                    //movement.rotDown = true;
                    break;
                case SDLK_s:
                    //movement.rotUp = true;
                    break;
                case SDLK_SPACE:
                    //camera.angleX = 0;
                    //camera.angleY = 0;
                    //camera.angleZ = 0;
                    break;
                    
            }
            break;
            
        case SDL_KEYUP:
            switch( e.key.keysym.sym ) {
                case SDLK_LEFT:
                    //movement.left = glm::vec3(0,0,0);
                    break;
                case SDLK_RIGHT:
                    //movement.right = glm::vec3(0,0,0);
                    break;
                case SDLK_UP:
                    //movement.up = glm::vec3(0,0,0);
                    break;
                case SDLK_DOWN:
                    //movement.down = glm::vec3(0,0,0);
                    break;
                case SDLK_q:
                    //movement.rotLeft = false;
                    break;
                case SDLK_e:
                    //movement.rotRight = false;
                    break;
                case SDLK_w:
                    //movement.rotDown = false;
                    break;
                case SDLK_s:
                    //movement.rotUp = false;
                    break;
                    
            }
            break;
        case SDL_MOUSEWHEEL:
            //movement.zoom += e.wheel.y / 4.f;
            break;
        case SDL_MOUSEMOTION:
            mouse.dx += e.motion.xrel;
            mouse.dy += e.motion.yrel;
            break;
        default:
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
    
    glEnable(GL_CULL_FACE);
    glEnable( GL_BLEND );
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    /* Enables Depth Testing */
    glEnable( GL_DEPTH_TEST );
    /* The Type Of Depth Test To Do */
    glDepthFunc( GL_LEQUAL );

    

    /* Really Nice Perspective Calculations */
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
    
    
    Vertex vertices[] = {
        // Front
        {.Position = { 1,-1, 1}, .Normal = {0,0,0}, .Color = {1, 0, 0, 1}},
        {.Position = { 1, 1, 1}, .Normal = {0,0,0}, .Color = {1, 1, 0, 1}},
        {.Position = {-1, 1, 1}, .Normal = {0,0,0}, .Color = {0, 1, 0, 1}},
        {.Position = {-1,-1, 1}, .Normal = {0,0,0}, .Color = {0, 0, 0, 1}},
        
        // Back
        {.Position = {-1,-1, -1}, .Normal = {0,0,0}, .Color = {0, 0, 1, 1}},
        {.Position = {-1, 1, -1}, .Normal = {0,0,0}, .Color = {1, 0, 1, 1}},
        {.Position = { 1, 1, -1}, .Normal = {0,0,0}, .Color = {1, 1, 1, 1}},
        {.Position = { 1,-1, -1}, .Normal = {0,0,0}, .Color = {0, 1, 1, 1}},
    };
    
    Triangle indices[] = {
        // Front
        {0, 1, 2},
        {2, 3, 0},
        // Back
        {4, 5, 6},
        {6, 7, 4},
        // Left
        {3, 2, 5},
        {5, 4, 3},
        // Right
        {7, 6, 1},
        {1, 0, 7},
        // Top
        {1, 6, 5},
        {5, 2, 1},
        // Bottom
        {3, 4, 7},
        {7, 0, 3},
    };
    
    
    try {
        scene.shader = std::make_shared<Shader>(vertexShaderSource,fragmentShaderSource);
    } catch (ShaderException e) {
        std::cerr << "Error loading shader: " << e.error << "\n";
        exit(0);
    }
    scene.root = std::make_shared<Group>();
    
    scene.cube = std::make_shared<Model>(vertices, 8, indices, 12, scene.shader);
    scene.root->add(scene.cube);
    
    ModelRenderer renderer;
    
    scene.renderer = renderer;
    
    scene.renderer.projection = glm::perspective(glm::radians(75.0f),16/9.0f,0.1f, 100.0f);
    scene.renderer.view =  glm::lookAt(
                                       glm::vec3(0.f,2.f,3.f),
                                       glm::vec3(0.f,0.f,0.f),
                                       glm::vec3(0.f,1.f,0.f)
                                       );
    
    
    scene.cube->position = glm::vec3(0.0f,0.f,0.f);
    scene.cube->scale = glm::vec3(0.9,0.9,0.9);
    scene.cube->rotation = glm::rotate(glm::quat(), glm::radians(135.f), glm::vec3(0,1,0));
   

    return true;
}

void SceneDelegate::teardown(GameLoop &l) {
}

void SceneDelegate::update(GameLoop &l) {
    updater.update(*scene.root);
    refresher.refresh(*scene.root, scene.renderer.view);
}

void SceneDelegate::render() {
    adjustViewport();
    
    /* Set the background black */
    glClearColor( .1f, .1f, .1f, 0 );
    /* Clear The Screen And The Depth Buffer */
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    scene.root->accept(scene.renderer);
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
