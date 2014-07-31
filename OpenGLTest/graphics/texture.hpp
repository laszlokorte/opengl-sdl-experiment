//
//  texture.h
//  OpenGLTut
//
//  Created by Laszlo Korte on 31.07.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLTut__texture__
#define __OpenGLTut__texture__

#include <stdio.h>

class Texture {
    GLuint textureID;
public:
    explicit Texture(std::string path);
    Texture(Texture&& t);
    Texture();
    ~Texture();
    
    void prepareRender(const GLuint uniformHandle, GLenum texIndex) const;
    
    void finishRender() const;
    
private:
    GLuint loadImageFile(std::string path) const;
};

#endif /* defined(__OpenGLTut__texture__) */
