//
//  first_person.h
//  OpenGLTest
//
//  Created by Laszlo Korte on 29.07.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLTest__first_person__
#define __OpenGLTest__first_person__

#include "../camera/camera.hpp"

class FirstPersonMovement {
    Camera &camera;
    const glm::vec3 up{0,1,0};
    const glm::vec3 forward{0,0,1};
    const glm::vec3 sideward{1,0,0};
public:
    explicit FirstPersonMovement(Camera &cam);
    
    void rotateHorizontally(float rad) const;

    void rotateVertically(float rad) const;
    
    void move(glm::vec2 dir2d, float amoun) const;

    void lookAt(glm::vec3 target) const;
};

#endif /* defined(__OpenGLTest__first_person__) */
