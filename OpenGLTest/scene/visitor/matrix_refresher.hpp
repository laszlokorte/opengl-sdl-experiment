//
//  matrix_refresher.h
//  OpenGLTest
//
//  Created by Laszlo Korte on 28.07.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLTest__matrix_refresher__
#define __OpenGLTest__matrix_refresher__

#include <stack>
#include "glm/glm.hpp"
#include "visitor_base.hpp"
#include "component.hpp"

class MatrixRefresher : public Visitor {
public:
    ~MatrixRefresher();
    void visit( Group & );
    void leave(  Group & );
    void visit(  Model & );
    void leave(  Model & );
    void refresh( Component &c);
    void refresh( Component &c, bool force);

private:
    std::stack<glm::mat4> stack;
    int dirtyCount = 0;
    void refreshMatrix( Group &g);
};

#endif /* defined(__OpenGLTest__matrix_refresher__) */
