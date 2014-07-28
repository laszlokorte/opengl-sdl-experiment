//
//  object_node_renderer.h
//  OpenGLTest
//
//  Created by Laszlo Korte on 28.07.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifdef __APPLE__
# define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
#endif

#ifndef __OpenGLTest__object_node_renderer__
#define __OpenGLTest__object_node_renderer__

#include <stdio.h>
#include <OpenGL/gl3.h>
#include <SDL2/SDL_opengl.h>

#define GLM_FORCE_RADIANS
#include "../lib/glm/glm/glm.hpp"

#include "node_renderer.hpp"
#include "node.hpp"
#include "object_node.hpp"

class ObjectNode;

class ObjectNodeRenderer : public NodeRenderer {
public:
    virtual void render(const Node &node) const;
    virtual void render(const ObjectNode &node) const;
    
private:
    void renderSingleNode(const Node &node, glm::mat4 modelView) const;
    void renderSingleNode(const ObjectNode &node, glm::mat4 modelView) const;
    
    friend class ObjectNode;
};

#endif /* defined(__OpenGLTest__object_node_renderer__) */
