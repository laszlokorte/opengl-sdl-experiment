//
//  keyboard_adapter.h
//  OpenGLTest
//
//  Created by Laszlo Korte on 28.07.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLTest__keyboard_adapter__
#define __OpenGLTest__keyboard_adapter__

#import <SDL2/SDL.h>
#import "keyboard.hpp"

class KeyboardAdapter {
    Keyboard &keyboard;
    
public:
    KeyboardAdapter(Keyboard &k);
    
    void processEvent(const SDL_Event &e) const;
    
    keyboard::Key mapKey(const int) const;
};

#endif /* defined(__OpenGLTest__keyboard_adapter__) */
