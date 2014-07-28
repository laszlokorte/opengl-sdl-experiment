//
//  tree_updater.cpp
//  OpenGLTest
//
//  Created by Laszlo Korte on 28.07.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "updater.hpp"
#include "component.hpp"
#include "model.hpp"
#include "group.hpp"

Updater::~Updater() {
}

void Updater::update(Component& c) {
    c.accept(*this);
}

void Updater::visit(Group &g )
{
    updateComponent(g);
}

void Updater::visit(Model &m )
{
    updateComponent(m);
}

void Updater::leave(Group &g )
{
}

void Updater::leave( Model &m )
{
}

void Updater::updateComponent(Component &g)
{
    g.update();
}
