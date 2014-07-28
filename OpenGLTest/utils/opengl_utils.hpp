//
//  opengl_utils.h
//  OpenGLTest
//
//  Created by Laszlo Korte on 28.07.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLTest__opengl_utils__
#define __OpenGLTest__opengl_utils__


#ifdef __APPLE__
# define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
#endif

#include <stdio.h>
#include <OpenGL/gl3.h>
#include <SDL2/SDL_opengl.h>


const char* GLErrorString(GLenum errorCode);

#endif /* defined(__OpenGLTest__opengl_utils__) */
