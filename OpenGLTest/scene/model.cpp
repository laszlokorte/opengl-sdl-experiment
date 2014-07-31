//
//  object_node.cpp
//  OpenGLTest
//
//  Created by Laszlo Korte on 28.07.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//
#define GLM_FORCE_RADIANS

#include "model.hpp"
#include "model_renderer.hpp"


Model::Model(glm::vec3 pos, glm::quat rot, glm::vec3 scl, Mesh mesh, std::shared_ptr<Shader> shad, std::shared_ptr<Texture> tex) :
Group(pos, rot, scl), shader(shad), _indexCount(3*(GLuint)mesh.triangles.size()), texture(tex)
{
    // Vertex Array Object
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    // Generate vertex and index buffer
    glGenBuffers(1, &(buffers.Vertex));
    glGenBuffers(1, &(buffers.Index));

    glBindBuffer(GL_ARRAY_BUFFER, buffers.Vertex);
    glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(Vertex), &mesh.vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers.Index);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.triangles.size() * sizeof(Triangle), &mesh.triangles[0], GL_STATIC_DRAW);

    // Enable vertex attributes
    glEnableVertexAttribArray(shader->handles.positionLocation);
    glVertexAttribPointer(shader->handles.positionLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid *) offsetof(Vertex, Position));

    glEnableVertexAttribArray(shader->handles.normalLocation);
    glVertexAttribPointer(shader->handles.normalLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid *) offsetof(Vertex, Normal));

    glEnableVertexAttribArray(shader->handles.colorLocation);
    glVertexAttribPointer(shader->handles.colorLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid *) offsetof(Vertex, Color));

    glEnableVertexAttribArray(shader->handles.texCoordLocation);
    glVertexAttribPointer(shader->handles.texCoordLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid *) offsetof(Vertex, TextureCoord));


    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Model::Model(Mesh mesh, std::shared_ptr<Shader> shad, std::shared_ptr<Texture> tex) :
Model(glm::vec3(), glm::quat(), glm::vec3(1), mesh, shad, tex)
{}

Model::Model(Mesh mesh, std::shared_ptr<Shader> shad) :
Model(glm::vec3(), glm::quat(), glm::vec3(1), mesh, shad, std::make_shared<Texture>())
{}

void Model::update() {
    
};

int Model::indexCount() const {
    return _indexCount;
};

void Model::accept( Visitor &v ) {
    v.visit(*this);
    for(auto n : container) {
        n->accept(v);
    }
    v.leave(*this);
}

Model::~Model() {
    glDeleteBuffers(2, &buffers.Vertex);
    glDeleteVertexArrays(1, &vertexArray);
}
