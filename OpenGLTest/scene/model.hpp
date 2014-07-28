//
//  object_node.h
//  OpenGLTest
//
//  Created by Laszlo Korte on 28.07.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifdef __APPLE__
# define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
#endif

#ifndef __OpenGLTest__object_node__
#define __OpenGLTest__object_node__

#include <stdio.h>
#include <OpenGL/gl3.h>
#include <SDL2/SDL_opengl.h>

#define GLM_FORCE_RADIANS
#include "../lib/glm/glm/glm.hpp"
#include "../graphics/shader.hpp"

#include "group.hpp"

class Model : public Group {
    GLuint vertexArray;
    struct {
        GLuint Vertex;
        GLuint Index;
    } buffers;
    GLuint vertexCount;
    GLuint indexCount;
    const GLenum glType = GL_UNSIGNED_INT;
    std::shared_ptr<Shader> shader;
public:
    Model(glm::vec3 pos, glm::quat rot, glm::vec3 scl,
               Vertex vertices[], GLuint vCount, Triangle tris[], GLuint triCount, std::shared_ptr<Shader> shad);
    
    Model(Vertex vertices[], GLuint vertexCount, Triangle tris[], GLuint triCount, std::shared_ptr<Shader> shad);
        
    virtual void update();
    
    void accept( Visitor & );
    
    ~Model();
    
    friend class ModelRenderer;
};


#endif /* defined(__OpenGLTest__object_node__) */
