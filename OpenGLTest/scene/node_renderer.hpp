//
//  node_renderer.h
//  OpenGLTest
//
//  Created by Laszlo Korte on 28.07.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifdef __APPLE__
# define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
#endif

#ifndef __OpenGLTest__node_renderer__
#define __OpenGLTest__node_renderer__

#include <stdio.h>
#include <OpenGL/gl3.h>
#include <SDL2/SDL_opengl.h>

#define GLM_FORCE_RADIANS
#include "../lib/glm/glm/glm.hpp"
#include "node.hpp"

class Node;
class ObjectNode;
class NodeRenderer {
public:
    glm::mat4 projection;
    glm::mat4 view;
    
    virtual void render(const Node &node) const = 0;
};

#endif /* defined(__OpenGLTest__node_renderer__) */
