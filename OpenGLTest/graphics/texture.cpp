//
//  texture.cpp
//  OpenGLTut
//
//  Created by Laszlo Korte on 31.07.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include <string>
#include <iostream>

#include <OpenGL/OpenGL.h>

#include <SDL2/SDL_opengl.h>
#include <SDL2_image/SDL_image.h>

#include "texture.hpp"


Texture::Texture(std::string path) : textureID(loadImageFile(path))
{
}

Texture::Texture()
{
}

Texture::Texture(Texture&& t) : textureID(t.textureID)
{
    t.textureID = 0;
}


Texture::~Texture()
{
    if(textureID) {
        glDeleteTextures(1, &textureID);
    }
}

GLuint Texture::loadImageFile(std::string path) const
{
    int Mode;
    int ModeInternal;
    GLuint id = 0;
    SDL_Surface *image = IMG_Load(path.c_str());
    
    if(!image) {
        throw "Texture could not be loaded";
    }
    
    if(image->w != image->h || (image->w & (image->w - 1))) {
        throw "Image must be square and dimensions must be a power of 2.";
    }
    
    if(image->format->BytesPerPixel == 4) {
        Mode = GL_RGBA;
        ModeInternal = GL_BGRA;
    } else if(image->format->BytesPerPixel == 3) {
        Mode = GL_RGB;
        ModeInternal = GL_BGR;
    } else {
        throw "Invalid texture format";
    }
    
    glGenTextures(1, &id);
    if(!id) {
        throw "Texture could not be created";
    }
    
    glBindTexture(GL_TEXTURE_2D, id);
    
    
    glTexImage2D(GL_TEXTURE_2D, 0, Mode, image->w, image->h, 0, ModeInternal, GL_UNSIGNED_BYTE, image->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    SDL_FreeSurface(image);
    
    return id;
}

void Texture::prepareRender(const GLuint uniformHandle, GLenum texIndex) const {
    if(textureID) {
        glActiveTexture(texIndex);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glUniform1i(uniformHandle,texIndex - GL_TEXTURE0);
    }
}

void Texture::finishRender() const {
    if(textureID) {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}