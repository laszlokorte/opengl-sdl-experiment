//
//  renderer_base.h
//  OpenGLTest
//
//  Created by Laszlo Korte on 28.07.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLTest__renderer_base__
#define __OpenGLTest__renderer_base__

class Visitor {
public:
    virtual ~Visitor();
    virtual void visit(  class Group & ) = 0;
    virtual void leave(  class Group & ) = 0;

    virtual void visit(  class Model & ) = 0;
    virtual void leave(  class Model & ) = 0;
};

#endif /* defined(__OpenGLTest__renderer_base__) */
