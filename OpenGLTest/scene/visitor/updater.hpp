//
//  tree_updater.h
//  OpenGLTest
//
//  Created by Laszlo Korte on 28.07.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLTest__updater__
#define __OpenGLTest__updater__

#include "visitor_base.hpp"

class Updater : public Visitor {
public:
    ~Updater();
    void visit( Group & );
    void leave(  Group & );
    void visit(  Model & );
    void leave(  Model & );
    void update( class Component &c);

private:
    void updateComponent( Component &g);
};
#endif /* defined(__OpenGLTest__tree_updater__) */
