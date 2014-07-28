//
//  node.cpp
//  OpenGLTest
//
//  Created by Laszlo Korte on 28.07.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "node.hpp"

Node::Node(glm::vec3 pos, glm::quat rot, glm::vec3 scl) :
position(pos), rotation(rot), scale(scl), matrix(1)
{
}

Node::Node() : Node(glm::vec3(), glm::quat(), glm::vec3())
{
}

void Node::addChild(const Node* &c) {
    children.push_back(c);
}

void Node::refreshMatrix(glm::mat4 parent) {
    auto rot = glm::mat4_cast(rotation);
    
    matrix = glm::mat4(parent);
    matrix = glm::scale(matrix, scale);
    matrix = glm::translate(matrix, position);
    matrix = matrix * rot;
    dirty = false;
}

const glm::mat4 Node::getMatrix() const
{
    return matrix;
}

Node::~Node() {
}