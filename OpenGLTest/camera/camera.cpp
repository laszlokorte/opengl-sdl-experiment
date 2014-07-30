//
//  camera.cpp
//  OpenGLTest
//
//  Created by Laszlo Korte on 29.07.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "camera.hpp"

#include <stdio.h>

Camera::Camera()
{
}

const glm::mat4 &Camera::viewMatrix()
{
    if(dirty) {
        _viewMatrix = glm::inverse(glm::translate(glm::mat4(), position) * glm::toMat4(rotation));
        dirty = false;
    }
    return _viewMatrix;
}

void Camera::lookAt(glm::vec3 p)
{
    rotation = glm::rotation(glm::vec3(0,0,-1), glm::normalize(p-position));
    dirty = true;

}