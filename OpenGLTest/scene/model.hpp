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
#include "glm/glm.hpp"
#include "../graphics/shader.hpp"
#include "../graphics/texture.hpp"
#include "../graphics/material.hpp"

#include "group.hpp"

class Model : public Group {
    GLuint vertexArray;
    struct {
        GLuint Vertex;
        GLuint Index;
    } buffers;
    const int _indexCount;
    const GLenum glType = GL_UNSIGNED_INT;
    std::shared_ptr<Shader> shader;
    std::shared_ptr<Material> material;
public:
    Model(glm::vec3 pos, glm::quat rot, glm::vec3 scl, Mesh mesh, std::shared_ptr<Shader> shad, std::shared_ptr<Material> mat);

    Model(Mesh mesh, std::shared_ptr<Shader> shad, std::shared_ptr<Material> mat);
    
    int indexCount() const;
    
    virtual void update();
    
    void accept( Visitor & );
    
    ~Model();
    
    friend class ModelRenderer;
};


#endif /* defined(__OpenGLTest__object_node__) */
