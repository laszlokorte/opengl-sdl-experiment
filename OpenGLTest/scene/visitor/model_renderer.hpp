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
#include "../../lib/glm/glm/glm.hpp"

#include "visitor_base.hpp"
#include "group.hpp"
#include "model.hpp"


class ModelRenderer : public Visitor {
public:
    glm::mat4 projection;
    glm::mat4 view;

    ~ModelRenderer();
    void visit( class Group & );
    void leave( class Group & );
    void visit( class Model & );
    void leave( class Model & );

private:
    void renderModel(const Model &model) const;
};

#endif /* defined(__OpenGLTest__object_node_renderer__) */
