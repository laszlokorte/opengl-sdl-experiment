//
//  gameloop.h
//  OpenGLTest
//
//  Created by Laszlo Korte on 28.07.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef OpenGLTest_gameloop_h
#define OpenGLTest_gameloop_h

#include <SDL2/SDL.h>


class GameLoop;
class GameLoopDelegate {
public:
    virtual void handleEvent(SDL_Event &e) = 0;
    virtual void setViewport(int x, int y) = 0;
    virtual bool setup(GameLoop &l) = 0;
    virtual void teardown(GameLoop &l) = 0;
    virtual void update(GameLoop &l) = 0;
    virtual void render() = 0;
    virtual void afterRender() const = 0;
};


class GameLoop {
    struct Config {
        int updateRate = 60;
        Config(int r) : updateRate(r) {}
        Config() {}
    } conf;
    
    SDL_Window* displayWindow;
    SDL_Renderer* displayRenderer;
    const long updateDuration = 60;
    GameLoopDelegate &delegate;
    long behind = 0;
    long lastTime = 0;
    long currentTime = 0;
    long nanoDelta = 0;
    long renderTime = 0;
    bool running = false;
    
public:
    GameLoop(const Config &c, GameLoopDelegate &del);
    
    void start();
    
    void stop();
    
    ~GameLoop();
};

#endif
