//
//  mouse.cpp
//  OpenGLTest
//
//  Created by Laszlo Korte on 29.07.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "mouse.hpp"

Mouse::Mouse()
{

}
Mouse::~Mouse()
{
}

bool Mouse::isDown(unsigned char k) const {
    return k < BUTTON_COUNT && buttonSet[k];
}

bool Mouse::isUp(unsigned char k) const {
    return k < BUTTON_COUNT && !buttonSet[k];
}

bool Mouse::pressed(unsigned char k) const {
    return k < BUTTON_COUNT && !prevButtonSet[k] && buttonSet[k];
}

bool Mouse::released(unsigned char k) const {
    return k < BUTTON_COUNT && prevButtonSet[k] && !buttonSet[k];
}

void Mouse::update()
{
    position.x += delta.x;
    position.y += delta.y;
    
    delta.x = delta.y = 0;
    prevButtonSet = buttonSet;
}

void Mouse::move(int x, int y)
{
    delta.x += x;
    delta.y += y;
}

void Mouse::scroll(int x, int y)
{
    wheel.x += x;
    wheel.y += y;
}

void Mouse::setPressed(const unsigned char button, bool pressed)
{
    if(button < BUTTON_COUNT) {
        prevButtonSet[button] = true;
    }
}