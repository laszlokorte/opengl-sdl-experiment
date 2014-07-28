//
//  gameloop.h
//  OpenGLTest
//
//  Created by Laszlo Korte on 28.07.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef OpenGLTest_gameloop_h
#define OpenGLTest_gameloop_h

struct gameLoop {
    long updateDuration = 60;
    long behind = 0;
    long lastTime = 0;
    long currentTime = 0;
    long nanoDelta = 0;
    long renderTime = 0;
};

#endif
