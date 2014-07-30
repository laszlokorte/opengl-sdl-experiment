//
//  gameloop.cpp
//  OpenGLTest
//
//  Created by Laszlo Korte on 28.07.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include <stdio.h>

#ifdef __APPLE__
# define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
#endif
#include <SDL2/SDL_opengl.h>
#include <OpenGL/OpenGL.h>
#include <iostream>
#include <stdio.h>


#include "gameloop.hpp"
#include "../utils/time.hpp"

GameLoop::GameLoop(const Config &c, GameLoopDelegate &del) :
    conf(c), delegate(del),
    updateDuration(1000000000 / conf.updateRate)
 {
     behind = -1;
     lastTime = -1;
     currentTime = -1;
     nanoDelta = 0;
     
     SDL_RendererInfo displayRendererInfo;
     
     SDL_Init(SDL_INIT_VIDEO);
     
     SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
     SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
     SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
     SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
     SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
     SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
     
     int windowOptions = SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE;

     SDL_CreateWindowAndRenderer(windowWidth, windowHeight, windowOptions, &displayWindow, &displayRenderer);
     SDL_SetWindowTitle(displayWindow, "OpenGL Test");
     
     SDL_GetRendererInfo(displayRenderer, &displayRendererInfo);

     if ((displayRendererInfo.flags & SDL_RENDERER_ACCELERATED) == 0)
     {
         SDL_DestroyWindow(displayWindow);
         SDL_Quit();
         throw 0;
     }
     
     if(!delegate.setup(*this))
     {
         SDL_DestroyWindow(displayWindow);
         SDL_Quit();
         throw 0;
     }
     
     if(conf.lockMouse) {
         SDL_SetRelativeMouseMode(SDL_TRUE);
     }
}

void GameLoop::start() {
    behind = updateDuration + 1;
    lastTime = hirestime();
    currentTime = lastTime;
    nanoDelta = 0;

    bool focused = true;
    
    SDL_Event e;
    long time = lowrestime();
    int frames = 0;
    int updates = 0;
    running = true;

    
    while(running)
    {
        lastTime = currentTime;
        currentTime = hirestime();
        nanoDelta = currentTime - lastTime;
        behind += nanoDelta;
        
        while(behind > updateDuration) {
            behind -= updateDuration;
            delegate.beforeUpdate(*this);
            while( SDL_PollEvent( &e ) != 0 )
            {
                switch(e.type) {
                    case SDL_QUIT:
                        running = false;
                        break;
                    case SDL_WINDOWEVENT:
                        switch (e.window.event)
                        {
                            case SDL_WINDOWEVENT_RESIZED:
                                windowWidth = e.window.data1;
                                windowHeight = e.window.data2;
                                delegate.setViewport(e.window.data1, e.window.data2);
                            case SDL_WINDOWEVENT_MINIMIZED:
                                focused = false;
                                SDL_SetRelativeMouseMode(SDL_FALSE);

                                break;
                            case SDL_WINDOWEVENT_RESTORED:
                                focused = true;
                                if(conf.lockMouse) {
                                    SDL_SetRelativeMouseMode(SDL_TRUE);
                                }
                                break;
                            case SDL_WINDOWEVENT_FOCUS_LOST:
                                SDL_SetRelativeMouseMode(SDL_FALSE);
                                break;
                            case SDL_WINDOWEVENT_FOCUS_GAINED:
                                if(conf.lockMouse) {
                                    SDL_SetRelativeMouseMode(SDL_TRUE);
                                }
                                break;
                        };
                        break;

                }
                delegate.handleEvent(e);

            }
            updates++;
            delegate.update(*this);
        }
        
        if(lowrestime() - time >= 1) {
            time = lowrestime();
            frames = 0;
            updates = 0;
        }
        
        if(focused) {
            long beforeRender = hirestime();
            delegate.render();
            renderTime = hirestime()-beforeRender;
            delegate.afterRender();
            SDL_RenderPresent(displayRenderer);
            frames++;
        } else {
            SDL_Delay(100);
        }
        
    }
}

void GameLoop::stop()
{
    running = false;
}

GameLoop::~GameLoop() {
    delegate.teardown(*this);
    SDL_DestroyRenderer(displayRenderer);
    SDL_DestroyWindow(displayWindow);
    SDL_Quit();
}
