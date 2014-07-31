//
//  object_node_renderer.cpp
//  OpenGLTest
//
//  Created by Laszlo Korte on 28.07.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include <iostream>
#include "model_renderer.hpp"
#include "../../utils/opengl_utils.hpp"

ModelRenderer::ModelRenderer()
{
    light.color = ColorRGB{1.f,1.f,1.f};
    light.ambientIntensity = 0.5;
    light.diffuseIntensity = 1.5;
    light.position = Vec3{30,15,15};
}

ModelRenderer::~ModelRenderer()
{
}

void ModelRenderer::visit( Group &g )
{
}

void ModelRenderer::leave( Group &g )
{
}

void ModelRenderer::visit( Model &m )
{
    renderModel(m);
}

void ModelRenderer::leave( Model &m )
{
}

void ModelRenderer::renderModel(const Model &model) const {
    
    const glm::mat4 modelMatrix = model.getMatrix();

    model.shader->prepareRender();

    glUniformMatrix4fv(model.shader->handles.modelMatrixUniform, 1, GL_FALSE, &modelMatrix[0][0]);
    glUniformMatrix4fv(model.shader->handles.viewMatrixUniform, 1, GL_FALSE, &viewMatrix[0][0]);
    glUniformMatrix4fv(model.shader->handles.projectionMatrixUniform, 1, GL_FALSE, &projection[0][0]);
    glUniform3f(model.shader->handles.cameraPositionUniform, cameraPosition.X, cameraPosition.Y, cameraPosition.Z);
        
    model.material->prepareRender(model.shader->handles.material);
    light.prepareRender(model.shader->handles.light);
    
    
    GLenum err;
    if((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << GLErrorString(err);
    }

    glBindVertexArray(model.vertexArray);
    glDrawElements(GL_TRIANGLES, model.indexCount(), model.glType, (void*)0);

    glBindVertexArray(0);

    light.finishRender(model.shader->handles.light);

    
    model.material->finishRender(model.shader->handles.material);
    model.shader->finishRender();
}

