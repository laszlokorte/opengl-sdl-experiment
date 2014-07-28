//
//  object_node.cpp
//  OpenGLTest
//
//  Created by Laszlo Korte on 28.07.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//
#define GLM_FORCE_RADIANS

#include "object_node.hpp"
#include "object_node_renderer.hpp"


ObjectNode::ObjectNode(glm::vec3 pos, glm::quat rot, glm::vec3 scl,
                       Vertex vertices[], GLuint vCount, Triangle tris[], GLuint triCount, std::shared_ptr<Shader> shad) :
Node(pos, rot, scl), shader(shad), vertexCount(vCount), indexCount(3*triCount)
{
    // Vertex Array Object
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);
    
    // Generate vertex and index buffer
    glGenBuffers(1, &(buffers.Vertex));
    glGenBuffers(1, &(buffers.Index));
    
    glBindBuffer(GL_ARRAY_BUFFER, buffers.Vertex);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex), vertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers.Index);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, triCount * sizeof(Triangle), tris, GL_STATIC_DRAW);
    
    // Enable vertex attributes
    glEnableVertexAttribArray(shader->handles.positionLocation);
    glVertexAttribPointer(shader->handles.positionLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid *) offsetof(Vertex, Position));
    
    glEnableVertexAttribArray(shader->handles.normalLocation);
    glVertexAttribPointer(shader->handles.normalLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid *) offsetof(Vertex, Normal));
    
    glEnableVertexAttribArray(shader->handles.colorLocation);
    glVertexAttribPointer(shader->handles.colorLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid *) offsetof(Vertex, Color));
    
    
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

ObjectNode::ObjectNode(Vertex vertices[], GLuint vertexCount, Triangle tris[], GLuint triCount, std::shared_ptr<Shader> shad) :
ObjectNode(glm::vec3(), glm::quat(), glm::vec3(1), vertices, vertexCount, tris, triCount, shad)
{}

void ObjectNode::renderWith(const ObjectNodeRenderer &renderer) const {
    renderer.renderSingleNode(*this, getMatrix());
}

void ObjectNode::update() {
    rotation = glm::rotate(rotation, glm::radians(0.8f), glm::vec3(0.f,1.f,0.f));
    dirty = true;
};

ObjectNode::~ObjectNode() {
    glDeleteBuffers(2, &buffers.Vertex);
    glDeleteVertexArrays(1, &vertexArray);
}