//
//  mouse_adapter.h
//  OpenGLTest
//
//  Created by Laszlo Korte on 29.07.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLTest__mouse_adapter__
#define __OpenGLTest__mouse_adapter__

#import <SDL2/SDL.h>

#include "mouse.hpp"

class MouseAdapter {
    Mouse &mouse;
    
public:
    MouseAdapter(Mouse &k);
    
    void processEvent(const SDL_Event &e) const;
};

#endif /* defined(__OpenGLTest__mouse_adapter__) */
