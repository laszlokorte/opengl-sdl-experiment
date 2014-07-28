//
//  node.h
//  OpenGLTest
//
//  Created by Laszlo Korte on 28.07.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifdef __APPLE__
# define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
#endif

#ifndef __OpenGLTest__node__
#define __OpenGLTest__node__

#include <stdio.h>
#include <vector>

#include <OpenGL/gl3.h>
#include <SDL2/SDL_opengl.h>

#define GLM_FORCE_RADIANS
#include "../lib/glm/glm/glm.hpp"
#include "../lib/glm/glm/gtx/vector_angle.hpp"
#include "../graphics/shader.hpp"

class NodeRenderer;

class Node {
    glm::mat4 matrix;
    std::vector<const Node*> children;
    
public:
    glm::vec3 position;
    glm::quat rotation;
    glm::vec3 scale;
    bool dirty;
    
    Node(glm::vec3 pos, glm::quat rot, glm::vec3 scl);
    
    Node();
    
    void addChild(const Node* &c);
    
    virtual void renderWith(const NodeRenderer &renderer) const {
        
    };
    
    virtual void update() {
        
    };
    
    void refreshMatrix(glm::mat4 parent);
    
    const glm::mat4 getMatrix() const;
    
    ~Node();
    
    friend class NodeRenderer;
};


#endif /* defined(__OpenGLTest__node__) */
