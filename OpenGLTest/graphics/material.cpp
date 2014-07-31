//
//  material.cpp
//  OpenGLTut
//
//  Created by Laszlo Korte on 31.07.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "material.hpp"
#include <iostream>

void Material::prepareRender(const MaterialHandle &h) const
{
    glUniform1f(h.shininessUniform, shininess);
    diffuseColor.prepareRender(h.diffuseColorUniform, GL_TEXTURE1);
    specularColor.prepareRender(h.specularColorUniform, GL_TEXTURE2);
    emittigColor.prepareRender(h.emittigColorUniform, GL_TEXTURE3);
}

void Material::finishRender(const MaterialHandle &h) const {
    diffuseColor.finishRender();
    specularColor.finishRender();
    emittigColor.finishRender();
}

Material::Material(Texture dif, Texture emit, Texture spec, GLfloat shin) :
diffuseColor(std::move(dif)), emittigColor(std::move(emit)), specularColor(std::move(spec)), shininess(shin){
    
}

Material::Material(Material&& mat) :
diffuseColor(std::move(mat.diffuseColor)), emittigColor(std::move(mat.emittigColor)), specularColor(std::move(mat.specularColor)){
    
}

Material::~Material() {

}
