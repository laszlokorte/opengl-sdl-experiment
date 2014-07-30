//
//  first_person.cpp
//  OpenGLTest
//
//  Created by Laszlo Korte on 29.07.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "first_person.hpp"
#include <stdio.h>
#include <iostream>
#define glm_detail_intrinsic_integer
#include "../lib/glm/glm/ext.hpp"

FirstPersonMovement::FirstPersonMovement(Camera &cam) : camera(cam)
{

}

void FirstPersonMovement::rotateHorizontally(float radians) const
{
    auto q = glm::angleAxis(-radians, up);
    
    camera.rotation = q * camera.rotation;
    camera.dirty = true;
}

void FirstPersonMovement::rotateVertically(float radians) const
{
    glm::quat newRot = glm::rotate(camera.rotation, -radians, sideward);
    
    glm::vec3 test = glm::rotate(newRot, up);
    
    if(glm::dot(test, up) > 0) {
        camera.rotation = newRot;
    }
    camera.dirty = true;
}

void FirstPersonMovement::move(glm::vec2 dir2d, float amount) const
{
    if(glm::length(dir2d) == 0) return;
    
    auto dir = glm::rotate(camera.rotation,-glm::vec3(dir2d.x, 0, dir2d.y));
    camera.position += amount*glm::normalize(glm::vec3(dir.x,0,dir.z));
    camera.dirty = true;
}

void FirstPersonMovement::lookAt(glm::vec3 p) const
{
    glm::vec3 direction = glm::normalize(p - camera.position);
    
    glm::quat rot1 = glm::rotation(-forward, direction);
    // Recompute desiredUp so that it's perpendicular to the direction
    // You can skip that part if you really want to force desiredUp
    glm::vec3 right = glm::cross(direction, up);
    glm::vec3 desiredUp = glm::normalize(glm::cross(right, direction));
    
    // Because of the 1rst rotation, the up is probably completely screwed up.
    // Find the rotation between the "up" of the rotated object, and the desired up
    glm::vec3 newUp = rot1 * up;
    glm::quat rot2 = glm::rotation(newUp, desiredUp);
    camera.rotation = rot2 * rot1;
    
    camera.dirty = true;
}