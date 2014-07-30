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
    const glm::mat4 modelView = model.getMatrix();

    model.shader->prepareRender();

    glUniformMatrix4fv(model.shader->handles.modelViewMatrixUniform, 1, GL_FALSE, &modelView[0][0]);
    glUniformMatrix4fv(model.shader->handles.projectionMatrixUniform, 1, GL_FALSE, &projection[0][0]);
    GLenum err;
    if((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << GLErrorString(err);
    }

    glBindVertexArray(model.vertexArray);
    glDrawElements(GL_TRIANGLES, model.indexCount(), model.glType, (void*)0);

    glBindVertexArray(0);

    model.shader->finishRender();
}

