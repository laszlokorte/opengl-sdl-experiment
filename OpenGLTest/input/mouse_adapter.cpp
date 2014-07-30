//
//  mouse_adapter.cpp
//  OpenGLTest
//
//  Created by Laszlo Korte on 29.07.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "mouse_adapter.hpp"

MouseAdapter::MouseAdapter(Mouse &k) : mouse(k)
{
}

void MouseAdapter::processEvent(const SDL_Event &e) const
{
    switch( e.type ){
        case SDL_MOUSEBUTTONDOWN:
            mouse.setPressed(e.button.which, true);
            break;
        case SDL_MOUSEBUTTONUP:
            mouse.setPressed(e.button.which, false);
            break;
        case SDL_MOUSEWHEEL:
            mouse.scroll(e.wheel.x, e.wheel.y);
            break;
        case SDL_MOUSEMOTION:
            mouse.move(e.motion.xrel, e.motion.yrel);
            break;
    }
}