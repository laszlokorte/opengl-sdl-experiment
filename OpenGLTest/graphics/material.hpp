//
//  material.h
//  OpenGLTut
//
//  Created by Laszlo Korte on 31.07.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLTut__material__
#define __OpenGLTut__material__

#include "base.hpp"
#include "texture.hpp"

struct MaterialHandle {
    GLuint shininessUniform;
    GLuint diffuseColorUniform;
    GLuint emittigColorUniform;
    GLuint specularColorUniform;
};

class Material {
    Texture diffuseColor;
    Texture emittigColor;
    Texture specularColor;
    
    GLfloat shininess;
public:
    Material(Texture dif, Texture emit, Texture spec, GLfloat shininess);
    Material(Material&& mat);
    ~Material();
    void prepareRender(const MaterialHandle &h) const;
    void finishRender(const MaterialHandle &h) const;
};

#endif /* defined(__OpenGLTut__material__) */
