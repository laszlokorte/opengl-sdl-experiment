//
//  node.cpp
//  OpenGLTest
//
//  Created by Laszlo Korte on 28.07.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "group.hpp"

Group::Group(glm::vec3 pos, glm::quat rot, glm::vec3 scl) :
position(pos), rotation(rot), scale(scl), matrix(1)
{
}

Group::Group() : Group(glm::vec3(0), glm::quat(), glm::vec3(1))
{
}

void Group::refreshMatrix(const glm::mat4 &parent) {
    auto rot = glm::mat4_cast(rotation);

    matrix = glm::mat4(parent);
    matrix = glm::scale(matrix, scale);
    matrix = glm::translate(matrix, position);
    matrix = matrix * rot;
}

void Group::add( std::shared_ptr<Component> c ) {
    container.push_back( c );
}

void Group::remove( std::shared_ptr<Component> c ) {
    container.remove( c );
}

void Group::accept( Visitor &v ) {
    v.visit(*this);
    for(auto n : container) {
        n->accept(v);
    }
    v.leave(*this);
}

void Group::update() {

};

const glm::mat4 Group::getMatrix() const
{
    return matrix;
}

Group::~Group() {
}
