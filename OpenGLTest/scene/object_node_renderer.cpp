//
//  object_node_renderer.cpp
//  OpenGLTest
//
//  Created by Laszlo Korte on 28.07.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include <iostream>
#include "object_node_renderer.hpp"
#include "../utils/opengl_utils.hpp"

void ObjectNodeRenderer::render(const Node &node) const {
    glm::mat4 modelView;
    node.renderWith(*this);
    
    NodeRenderer::render(node);
}

void ObjectNodeRenderer::render(const ObjectNode &node) const {
    glm::mat4 modelView;
    node.renderWith(*this);
    
    
    NodeRenderer::render(node);
}

void ObjectNodeRenderer::renderSingleNode(const Node &node, glm::mat4 modelView) const {
    
}

void ObjectNodeRenderer::renderSingleNode(const ObjectNode &node, glm::mat4 modelView) const {
    
    node.shader->prepareRender();
    
    glUniformMatrix4fv(node.shader->handles.modelViewMatrixUniform, 1, GL_FALSE, &modelView[0][0]);
    glUniformMatrix4fv(node.shader->handles.projectionMatrixUniform, 1, GL_FALSE, &projection[0][0]);
    GLenum err;
    if((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << GLErrorString(err);
    }
    
    glBindVertexArray(node.vertexArray);
    glDrawElements(GL_TRIANGLES, node.indexCount, node.glType, (void*)0);
    
    glBindVertexArray(0);
    
    node.shader->finishRender();
}

