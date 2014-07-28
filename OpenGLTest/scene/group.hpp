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
#include <list>
#include <vector>

#include <OpenGL/gl3.h>
#include <SDL2/SDL_opengl.h>

#define GLM_FORCE_RADIANS
#include "../lib/glm/glm/glm.hpp"
#include "../lib/glm/glm/gtx/vector_angle.hpp"
#include "../graphics/shader.hpp"
#include "visitor/visitor_base.hpp"
#include "component.hpp"

class NodeRenderer;
class ObjectNodeRenderer;

class Group : public Component {
    glm::mat4 matrix;
public:
    glm::vec3 position;
    glm::quat rotation;
    glm::vec3 scale;

    bool dirty = true;
    
    Group(glm::vec3 pos, glm::quat rot, glm::vec3 scl);
    
    Group();
    
    ~Group();
    
    void refreshMatrix(const glm::mat4 &parent);
    void update();
    
    const glm::mat4 getMatrix() const;
    
    void add( std::shared_ptr<Component> );
    void remove( std::shared_ptr<Component> );
    
    void accept( Visitor & );
private:
    typedef std::list<std::shared_ptr<Component>> CONTAINER_TYPE;
    typedef CONTAINER_TYPE::iterator ITERATOR;
    CONTAINER_TYPE container;
    
    friend class Model;
};


#endif /* defined(__OpenGLTest__node__) */
