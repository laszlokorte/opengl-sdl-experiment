//
//  keyboard_adapter.cpp
//  OpenGLTest
//
//  Created by Laszlo Korte on 28.07.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "keyboard_adapter.h"

KeyboardAdapter::KeyboardAdapter(Keyboard &k) : keyboard(k)
{
}

void KeyboardAdapter::processEvent(const SDL_Event &e)
{
    switch( e.type ){
        case SDL_KEYDOWN:
            keyboard.setKeyDown(mapKey(e.key.keysym.sym));
            break;
            
        case SDL_KEYUP:
            keyboard.setKeyDown(mapKey(e.key.keysym.sym));

            break;
    }
}

keyboard::Key KeyboardAdapter::mapKey(const int keycode) const {
    switch(keycode) {
        case 8: return keyboard::BACKSPACE;
        case 9: return keyboard::TAB;
        case 13: return keyboard::ENTER;
        case 19: return keyboard::PAUSE;
        case 20: return keyboard::CAPS_LOCK;
        case 27: return keyboard::ESCAPE;
        case 32: return keyboard::SPACE;
        case 33: return keyboard::PAGE_UP;
        case 34: return keyboard::PAGE_DOWN;
        case 35: return keyboard::END;
        case 36: return keyboard::HOME;
        case 37: return keyboard::LEFT_ARROW;
        case 38: return keyboard::UP_ARROW;
        case 39: return keyboard::RIGHT_ARROW;
        case 40: return keyboard::DOWN_ARROW;
        case 45: return keyboard::INSERT;
        case 46: return keyboard::DELETE;
        case 48: return keyboard::NUMBER_0;
        case 49: return keyboard::NUMBER_1;
        case 50: return keyboard::NUMBER_2;
        case 51: return keyboard::NUMBER_3;
        case 52: return keyboard::NUMBER_4;
        case 53: return keyboard::NUMBER_5;
        case 54: return keyboard::NUMBER_6;
        case 55: return keyboard::NUMBER_7;
        case 56: return keyboard::NUMBER_8;
        case 57: return keyboard::NUMBER_9;
        case 65: return keyboard::LETTER_A;
        case 66: return keyboard::LETTER_B;
        case 67: return keyboard::LETTER_C;
        case 68: return keyboard::LETTER_D;
        case 69: return keyboard::LETTER_E;
        case 70: return keyboard::LETTER_F;
        case 71: return keyboard::LETTER_G;
        case 72: return keyboard::LETTER_H;
        case 73: return keyboard::LETTER_I;
        case 74: return keyboard::LETTER_J;
        case 75: return keyboard::LETTER_K;
        case 76: return keyboard::LETTER_L;
        case 77: return keyboard::LETTER_M;
        case 78: return keyboard::LETTER_N;
        case 79: return keyboard::LETTER_O;
        case 80: return keyboard::LETTER_P;
        case 81: return keyboard::LETTER_Q;
        case 82: return keyboard::LETTER_R;
        case 83: return keyboard::LETTER_S;
        case 84: return keyboard::LETTER_T;
        case 85: return keyboard::LETTER_U;
        case 86: return keyboard::LETTER_V;
        case 87: return keyboard::LETTER_W;
        case 88: return keyboard::LETTER_X;
        case 89: return keyboard::LETTER_Y;
        case 90: return keyboard::LETTER_Z;
        case 93: return keyboard::SELECT_KEY;
        case 96: return keyboard::NUMPAD_0;
        case 97: return keyboard::NUMPAD_1;
        case 98: return keyboard::NUMPAD_2;
        case 99: return keyboard::NUMPAD_3;
        case 100: return keyboard::NUMPAD_4;
        case 101: return keyboard::NUMPAD_5;
        case 102: return keyboard::NUMPAD_6;
        case 103: return keyboard::NUMPAD_7;
        case 104: return keyboard::NUMPAD_8;
        case 105: return keyboard::NUMPAD_9;
        case 106: return keyboard::MULTIPLY;
        case 107: return keyboard::ADD;
        case 109: return keyboard::SUBTRACT;
        case 110: return keyboard::DECIMAL_POINT;
        case 111: return keyboard::DIVIDE;
        case 112: return keyboard::F_1;
        case 113: return keyboard::F_2;
        case 114: return keyboard::F_3;
        case 115: return keyboard::F_4;
        case 116: return keyboard::F_5;
        case 117: return keyboard::F_6;
        case 118: return keyboard::F_7;
        case 119: return keyboard::F_8;
        case 120: return keyboard::F_9;
        case 121: return keyboard::F_10;
        case 122: return keyboard::F_11;
        case 123: return keyboard::F_12;
        case 144: return keyboard::NUM_LOCK;
        case 145: return keyboard::SCROLL_LOCK;
        case 186: return keyboard::SEMICOLON;
        case 187: return keyboard::EQUAL_SIGN;
        case 188: return keyboard::COMMA;
        case 189: return keyboard::DASH;
        case 190: return keyboard::PERIOD;
        case 191: return keyboard::FORWARD_SLASH;
        case 192: return keyboard::GRAVE_ACCENT;
        case 219: return keyboard::OPEN_BRACKET;
        case 220: return keyboard::BACK_SLASH;
        case 221: return keyboard::CLOSE_BRAKET;
        case 222: return keyboard::SINGLE_QUOTE;
    }
    return keyboard::OWNKNOWN;
};