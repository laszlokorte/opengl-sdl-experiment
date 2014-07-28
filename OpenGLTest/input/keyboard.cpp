//
//  keyboard.cpp
//  OpenGLTest
//
//  Created by Laszlo Korte on 28.07.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "keyboard.h"
#include <memory>

Keyboard::Keyboard():keySet{},prevKeySet{} {
}

bool Keyboard::isDown(Key k) {
    return keySet[k] && k != keyboard::OWNKNOWN;
}

bool Keyboard::isUp(Key k) {
    return !keySet[k] && k != keyboard::OWNKNOWN;
}

bool Keyboard::pressed(Key k) {
    return !prevKeySet[k] && keySet[k] && k != keyboard::OWNKNOWN;
}

bool Keyboard::released(Key k) {
    return prevKeySet[k] && !keySet[k] && k != keyboard::OWNKNOWN;
}

void Keyboard::update() {
}

void Keyboard::setKeyUp(Key k) {
    if(k != keyboard::OWNKNOWN) {
        keySet[k] = false;
    }
}

void Keyboard::setKeyDown(Key k) {
    if(k != keyboard::OWNKNOWN) {
        keySet[k] = true;
    }
}