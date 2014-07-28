//
//  componen.h
//  OpenGLTest
//
//  Created by Laszlo Korte on 28.07.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLTest__componen__
#define __OpenGLTest__componen__

#define GLM_FORCE_RADIANS
#include "../lib/glm/glm/glm.hpp"
#include "../lib/glm/glm/gtx/vector_angle.hpp"

#include "visitor/visitor_base.hpp"

class Component {
public:
    virtual ~Component();
    virtual void accept( Visitor & ) = 0;
    
    virtual void refreshMatrix(const glm::mat4 &parent) = 0;
    virtual const glm::mat4 getMatrix() const = 0;
    virtual void update() = 0;

};


#endif /* defined(__OpenGLTest__componen__) */
