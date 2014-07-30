//
//  matrix_refresher.cpp
//  OpenGLTest
//
//  Created by Laszlo Korte on 28.07.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "matrix_refresher.hpp"

#include "group.hpp"
#include "model.hpp"

MatrixRefresher::~MatrixRefresher()
{
}

void MatrixRefresher::refresh(Component& c, const glm::mat4 view) {
    refresh(c, view);
}

void MatrixRefresher::refresh(Component& c, const glm::mat4 view, bool force) {
    if(force) dirtyCount++;
    dirtyCount++;
    stack.push(view);
    c.accept(*this);
    if(force) dirtyCount--;
}

void MatrixRefresher::visit(Group &g )
{
    if(g.dirty) {
        dirtyCount++;
    }
    refreshMatrix(g);
    stack.push(g.getMatrix());
}

void MatrixRefresher::visit(Model &m )
{
    if(m.dirty) {
        dirtyCount++;
    }
    refreshMatrix(m);
    stack.push(m.getMatrix());

}

void MatrixRefresher::leave(Group &g )
{
    if(g.dirty) {
        dirtyCount--;
        g.dirty = false;
    }
    stack.pop();
}

void MatrixRefresher::leave( Model &m )
{
    if(m.dirty) {
        dirtyCount--;
        m.dirty = false;
    }
    stack.pop();
}

void MatrixRefresher::refreshMatrix(Group &g)
{
    if(dirtyCount > 0) {
        g.refreshMatrix(stack.top());
    }
}
