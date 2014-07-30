//
//  mouse.h
//  OpenGLTest
//
//  Created by Laszlo Korte on 29.07.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLTest__mouse__
#define __OpenGLTest__mouse__

#import <array>

class Mouse {
    static const unsigned char BUTTON_COUNT = 3;
    
    std::array<bool, BUTTON_COUNT> buttonSet;
    std::array<bool, BUTTON_COUNT> prevButtonSet;
public:
    struct {
        int x;
        int y;
    } position;
    
    struct {
        int x;
        int y;
    } delta;
    
    struct {
        int x;
        int y;
    } wheel;
    
    Mouse();
    ~Mouse();
    
    bool isDown(unsigned char k) const;
    bool isUp(unsigned char k) const;
    bool pressed(unsigned char k) const;
    bool released(unsigned char k) const;
    
    void update();
private:
    void move(int x, int y);

    void scroll(int x, int y);

    void setPressed(const unsigned char button, bool pressed);
    
    friend class MouseAdapter;
};

#endif /* defined(__OpenGLTest__mouse__) */
