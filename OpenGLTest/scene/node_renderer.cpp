//
//  node_renderer.cpp
//  OpenGLTest
//
//  Created by Laszlo Korte on 28.07.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "node_renderer.hpp"

void NodeRenderer::render(const Node &node) const {
    for(auto n : node.children) {
        render(*n);
    }
}