//
//  camera.h
//  OpenGLTest
//
//  Created by Laszlo Korte on 29.07.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLTest__camera__
#define __OpenGLTest__camera__

#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include "glm/gtx/vector_angle.hpp"


class Camera {
    glm::mat4 _viewMatrix;
    
public:    
    glm::quat rotation;
    glm::vec3 position;
    bool dirty = true;

    Camera();
    
    const glm::mat4 &viewMatrix();
    void lookAt(glm::vec3 p);
};

#endif /* defined(__OpenGLTest__camera__) */
