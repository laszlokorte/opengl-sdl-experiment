//
//  keyboard.cpp
//  OpenGLTest
//
//  Created by Laszlo Korte on 28.07.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "keyboard.hpp"

Keyboard::Keyboard():keySet{},prevKeySet{} {
}

bool Keyboard::isDown(Key k) const {
    return keySet[k] && k != keyboard::OWNKNOWN;
}

bool Keyboard::isUp(Key k) const {
    return !keySet[k] && k != keyboard::OWNKNOWN;
}

bool Keyboard::pressed(Key k) const {
    return !prevKeySet[k] && keySet[k] && k != keyboard::OWNKNOWN;
}

bool Keyboard::released(Key k) const {
    return prevKeySet[k] && !keySet[k] && k != keyboard::OWNKNOWN;
}

void Keyboard::update() {
    prevKeySet = keySet;
    std::copy(std::begin(keySet), std::end(keySet), std::begin(prevKeySet));
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