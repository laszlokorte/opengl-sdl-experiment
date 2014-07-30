//
//  keyboard_adapter.cpp
//  OpenGLTest
//
//  Created by Laszlo Korte on 28.07.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "keyboard_adapter.hpp"

KeyboardAdapter::KeyboardAdapter(Keyboard &k) : keyboard(k)
{
}

void KeyboardAdapter::processEvent(const SDL_Event &e) const
{
    switch( e.type ){
        case SDL_KEYDOWN:
            keyboard.setKeyDown(mapKey(e.key.keysym.sym));
            break;
            
        case SDL_KEYUP:
            keyboard.setKeyUp(mapKey(e.key.keysym.sym));

            break;
    }
}

keyboard::Key KeyboardAdapter::mapKey(const int keycode) const {
    switch(keycode) {
        case SDLK_BACKSPACE: return keyboard::BACKSPACE;
        case SDLK_TAB: return keyboard::TAB;
        case SDLK_RETURN: return keyboard::ENTER;
        case SDLK_PAUSE: return keyboard::PAUSE;
        case SDLK_CAPSLOCK: return keyboard::CAPS_LOCK;
        case SDLK_ESCAPE: return keyboard::ESCAPE;
        case SDLK_SPACE: return keyboard::SPACE;
        case SDLK_PAGEUP: return keyboard::PAGE_UP;
        case SDLK_PAGEDOWN: return keyboard::PAGE_DOWN;
        case SDLK_END: return keyboard::END;
        case SDLK_HOME: return keyboard::HOME;
        case SDLK_LEFT: return keyboard::LEFT_ARROW;
        case SDLK_UP: return keyboard::UP_ARROW;
        case SDLK_RIGHT: return keyboard::RIGHT_ARROW;
        case SDLK_DOWN: return keyboard::DOWN_ARROW;
        case SDLK_INSERT: return keyboard::INSERT;
        case SDLK_DELETE: return keyboard::DELETE;
        case SDLK_0: return keyboard::NUMBER_0;
        case SDLK_1: return keyboard::NUMBER_1;
        case SDLK_2: return keyboard::NUMBER_2;
        case SDLK_3: return keyboard::NUMBER_3;
        case SDLK_4: return keyboard::NUMBER_4;
        case SDLK_5: return keyboard::NUMBER_5;
        case SDLK_6: return keyboard::NUMBER_6;
        case SDLK_7: return keyboard::NUMBER_7;
        case SDLK_8: return keyboard::NUMBER_8;
        case SDLK_9: return keyboard::NUMBER_9;
        case SDLK_a: return keyboard::LETTER_A;
        case SDLK_b: return keyboard::LETTER_B;
        case SDLK_c: return keyboard::LETTER_C;
        case SDLK_d: return keyboard::LETTER_D;
        case SDLK_e: return keyboard::LETTER_E;
        case SDLK_f: return keyboard::LETTER_F;
        case SDLK_g: return keyboard::LETTER_G;
        case SDLK_h: return keyboard::LETTER_H;
        case SDLK_i: return keyboard::LETTER_I;
        case SDLK_j: return keyboard::LETTER_J;
        case SDLK_k: return keyboard::LETTER_K;
        case SDLK_l: return keyboard::LETTER_L;
        case SDLK_m: return keyboard::LETTER_M;
        case SDLK_n: return keyboard::LETTER_N;
        case SDLK_o: return keyboard::LETTER_O;
        case SDLK_p: return keyboard::LETTER_P;
        case SDLK_q: return keyboard::LETTER_Q;
        case SDLK_r: return keyboard::LETTER_R;
        case SDLK_s: return keyboard::LETTER_S;
        case SDLK_t: return keyboard::LETTER_T;
        case SDLK_u: return keyboard::LETTER_U;
        case SDLK_v: return keyboard::LETTER_V;
        case SDLK_w: return keyboard::LETTER_W;
        case SDLK_x: return keyboard::LETTER_X;
        case SDLK_y: return keyboard::LETTER_Y;
        case SDLK_z: return keyboard::LETTER_Z;
        case SDLK_SELECT: return keyboard::SELECT_KEY;
        case SDLK_KP_0: return keyboard::NUMPAD_0;
        case SDLK_KP_1: return keyboard::NUMPAD_1;
        case SDLK_KP_2: return keyboard::NUMPAD_2;
        case SDLK_KP_3: return keyboard::NUMPAD_3;
        case SDLK_KP_4: return keyboard::NUMPAD_4;
        case SDLK_KP_5: return keyboard::NUMPAD_5;
        case SDLK_KP_6: return keyboard::NUMPAD_6;
        case SDLK_KP_7: return keyboard::NUMPAD_7;
        case SDLK_KP_8: return keyboard::NUMPAD_8;
        case SDLK_KP_9: return keyboard::NUMPAD_9;
        case SDLK_KP_MULTIPLY: return keyboard::MULTIPLY;
        case SDLK_KP_PLUS: return keyboard::ADD;
        case SDLK_KP_MINUS: return keyboard::SUBTRACT;
        case SDLK_KP_DECIMAL: return keyboard::DECIMAL_POINT;
        case SDLK_KP_DIVIDE: return keyboard::DIVIDE;
        case SDLK_F1: return keyboard::F_1;
        case SDLK_F2: return keyboard::F_2;
        case SDLK_F3: return keyboard::F_3;
        case SDLK_F4: return keyboard::F_4;
        case SDLK_F5: return keyboard::F_5;
        case SDLK_F6: return keyboard::F_6;
        case SDLK_F7: return keyboard::F_7;
        case SDLK_F8: return keyboard::F_8;
        case SDLK_F9: return keyboard::F_9;
        case SDLK_F10: return keyboard::F_10;
        case SDLK_F11: return keyboard::F_11;
        case SDLK_F12: return keyboard::F_12;
        case SDLK_NUMLOCKCLEAR: return keyboard::NUM_LOCK;
        case SDLK_SCROLLLOCK: return keyboard::SCROLL_LOCK;
        case SDLK_SEMICOLON: return keyboard::SEMICOLON;
        case SDLK_EQUALS: return keyboard::EQUAL_SIGN;
        case SDLK_COMMA: return keyboard::COMMA;
        case SDLK_MINUS: return keyboard::DASH;
        case SDLK_PERIOD: return keyboard::PERIOD;
        case SDLK_SLASH: return keyboard::FORWARD_SLASH;
        case SDLK_BACKQUOTE: return keyboard::GRAVE_ACCENT;
        case SDLK_LEFTBRACKET: return keyboard::OPEN_BRACKET;
        case SDLK_BACKSLASH: return keyboard::BACK_SLASH;
        case SDLK_RIGHTBRACKET: return keyboard::CLOSE_BRAKET;
        case SDLK_QUOTE: return keyboard::SINGLE_QUOTE;
    }
    return keyboard::OWNKNOWN;
};