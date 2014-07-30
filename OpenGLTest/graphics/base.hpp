//
//  base.h
//  OpenGLTest
//
//  Created by Laszlo Korte on 28.07.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef OpenGLTest_base_h
#define OpenGLTest_base_h

#ifdef __APPLE__
# define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
#endif

#include <OpenGL/gl3.h>
#include <vector>

struct Vec3 {
    GLfloat X;
    GLfloat Y;
    GLfloat Z;
};

struct TextureUVCoord {
    GLfloat U;
    GLfloat V;
};

struct ColorRGBA {
    GLfloat R;
    GLfloat G;
    GLfloat B;
    GLfloat A;
};

struct Vertex {
    Vec3 Position;
    Vec3 Normal;
    ColorRGBA Color;
    TextureUVCoord TextureCoord;
};

struct Triangle {
    GLuint A;
    GLuint B;
    GLuint C;
};

class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<Triangle> triangles;
    
    Mesh(const std::vector<Vertex> vertices, const std::vector<Triangle> triangles);
};

namespace mesh {
    Mesh makeCube();
    Mesh makePyramid();
    Mesh makeCylinder(unsigned int sides, float height = 2, float radius = 1);
}

#endif
