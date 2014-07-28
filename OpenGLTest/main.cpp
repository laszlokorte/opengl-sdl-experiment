#include <iostream>

#ifdef __APPLE__
# define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
#endif

#include <SDL2/SDL.h>
#include <OpenGL/gl3.h>
#include <SDL2/SDL_opengl.h>

#define GLM_FORCE_RADIANS
#include "lib/glm/glm/glm.hpp"

#include "utils/opengl_utils.hpp"
#include "utils/time.hpp"
#include "loop/gameloop.hpp"

#include "graphics/base.hpp"
#include "graphics/shader.hpp"

#include "scene/node.hpp"
#include "scene/object_node.hpp"
#include "scene/object_node_renderer.hpp"

struct {
    int updateRate = 100;
} config;

const GLchar* vertexShaderSource[] = {
#include "shaders/base.vsh"
};


const GLchar* fragmentShaderSource[] = {
#include "shaders/base.fsh"
};

struct {
    int width;
    int height;
} screen;

struct {
    int dx = 0;
    int dy = 0;
    bool down = false;
} mouse;

void HandleInput(SDL_Event e) {
    switch( e.type ){
        case SDL_MOUSEBUTTONDOWN:
            mouse.down = true;
            break;
        case SDL_MOUSEBUTTONUP:
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

void Screen_Viewport() {
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

int Display_InitGL()
{

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
    
    return 0;
}
/* function to reset our viewport after a window resize */
int Display_SetViewport( int w, int h )
{
    
    screen.width = w;
    screen.height = h;
    
    return 1;
}

struct {
    Node root;
    std::shared_ptr<ObjectNode> cube;
    ObjectNodeRenderer renderer;
    std::shared_ptr<Shader> shader;
} scene;

int Setup()
{
    
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
    scene.cube = std::make_shared<ObjectNode>(vertices, 8, indices, 12, scene.shader);
    
    ObjectNodeRenderer renderer;
    
    scene.renderer = renderer;
    
    return 0;
}

void Display_Render(SDL_Renderer* displayRenderer)
{
    Screen_Viewport();
    
    /* Set the background black */
    glClearColor( .1f, .1f, .1f, 0 );
    /* Clear The Screen And The Depth Buffer */
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    scene.renderer.render(*(scene.cube));
}



void Update() {
    scene.cube->update();
    if(scene.cube->dirty) {
        scene.cube->refreshMatrix(scene.renderer.view);
    }
}

int
main(int argc, char *argv[])
{

    SDL_Init(SDL_INIT_VIDEO);
    
    SDL_Event e;
    SDL_Window* displayWindow;
    SDL_Renderer* displayRenderer;
    SDL_RendererInfo displayRendererInfo;
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    
    SDL_CreateWindowAndRenderer(800, 600, SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE, &displayWindow, &displayRenderer);
    SDL_SetWindowTitle(displayWindow, "OpenGL Test");
    
  
    
    SDL_GetRendererInfo(displayRenderer, &displayRendererInfo);

    if ((displayRendererInfo.flags & SDL_RENDERER_ACCELERATED) == 0)
    {
        std::cerr << "OpenGL is not available" << "\n";
        SDL_Quit();
        return 0;
    }
  
    
    
    if(Display_InitGL() || Setup())
    {
        std::cerr << "OpenGL could not be initialized" << "\n";
        SDL_DestroyWindow(displayWindow);
        SDL_Quit();
        return 0;
    }
    
    scene.renderer.projection = glm::perspective(glm::radians(75.0f),16/9.0f,0.1f, 100.0f);
    scene.renderer.view =  glm::lookAt(
                                       glm::vec3(0.f,2.f,3.f),
                                       glm::vec3(0.f,0.f,0.f),
                                       glm::vec3(0.f,1.f,0.f)
                                       );

    
    scene.cube->position = glm::vec3(0.0f,0.f,0.f);
    scene.cube->scale = glm::vec3(0.9,0.9,0.9);
    scene.cube->rotation = glm::rotate(glm::quat(), glm::radians(135.f), glm::vec3(0,1,0));
    scene.cube->refreshMatrix(scene.renderer.view);
    
    Display_SetViewport(800, 600);
    
    bool quit = false;
    gameLoop loop;
    loop.updateDuration = 1000000000 / config.updateRate;
    loop.behind = loop.updateDuration +1;
    loop.lastTime = hirestime();
    loop.currentTime = loop.lastTime;
    loop.nanoDelta = 0;
    long time = lowrestime();
    int frames = 0;
    int updates = 0;
    
    GLenum err;
    if((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL error:" << GLErrorString(err) << "\n";
    }
    
    while(!quit)
    {
        loop.lastTime = loop.currentTime;
        loop.currentTime = hirestime();
        loop.nanoDelta = loop.currentTime - loop.lastTime;
        loop.behind += loop.nanoDelta;
        while(loop.behind > loop.updateDuration) {
            loop.behind -= loop.updateDuration;
            while( SDL_PollEvent( &e ) != 0 )
            {
                switch(e.type) {
                    case SDL_QUIT:
                        quit = true;
                    case SDL_WINDOWEVENT:
                        switch (e.window.event)
                        {
                            case SDL_WINDOWEVENT_RESIZED:
                                Display_SetViewport(e.window.data1, e.window.data2);
                        }
                    default:
                        if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_f) {
                            std::cout << loop.renderTime / 1000000.f << "\n";
                        }
                        HandleInput(e);
                }
            }
            updates++;
            Update();
        }
        
        if(lowrestime() - time >= 1) {
            time = lowrestime();
            frames = 0;
            updates = 0;
        }
        
        long beforeRender = hirestime();
        Display_Render(displayRenderer);
        loop.renderTime = hirestime()-beforeRender;
        SDL_RenderPresent(displayRenderer);
        frames++;
    }
    
    SDL_DestroyWindow(displayWindow);
    SDL_Quit();
    
    return 0;
}