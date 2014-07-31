//
//  shader.cpp
//  OpenGLTest
//
//  Created by Laszlo Korte on 28.07.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include <iostream>

#include "shader.hpp"

Shader::Shader(const GLchar** vsh, const GLchar** fsh) throw (ShaderException)
: handles(createProgram(vsh, fsh, {}))
{
    
}

Shader::~Shader() {
    glDeleteProgram(handles.program);
}

void Shader::prepareRender() const {
    glUseProgram(handles.program);
}

void Shader::finishRender() const {
    glUseProgram(0);
}

Shader::Handles Shader::createProgram(const GLchar** vertexShader, const GLchar** fragmentShader, Identifiers ident) {
    Handles h;
    h.positionLocation = 1;
    h.colorLocation = 2;
    h.normalLocation = 3;
    h.texCoordLocation = 4;
    
    GLint compileOk;
    GLint errLength;
    GLchar* errMsg;
    
    h.program = glCreateProgram();
    
    GLuint vsh = compileShader(Shader::Type::Vertex, vertexShader);
    GLuint fsh = compileShader(Shader::Type::Fragment, fragmentShader);
    
    glAttachShader(h.program, vsh);
    glAttachShader(h.program, fsh);
    
    if(ident.vertexPosition != NULL) {
        glBindAttribLocation(h.program, h.positionLocation, ident.vertexPosition);
    }
    
    if(ident.vertexNormal != NULL) {
        glBindAttribLocation(h.program, h.normalLocation, ident.vertexNormal);
    }
    if(ident.vertexColor != NULL) {
        glBindAttribLocation(h.program, h.colorLocation, ident.vertexColor);
    }
    if(ident.vertexColor != NULL) {
        glBindAttribLocation(h.program, h.colorLocation, ident.vertexColor);
    }
    if(ident.vertexTexCoord != NULL) {
        glBindAttribLocation(h.program, h.texCoordLocation, ident.vertexTexCoord);
    }
    
    
    glLinkProgram(h.program);
    glGetProgramiv(h.program, GL_LINK_STATUS, &compileOk);
    if(!compileOk) {
        glGetProgramiv(h.program, GL_INFO_LOG_LENGTH, &errLength);
        errMsg = new GLchar[errLength];
        glGetProgramInfoLog(h.program, errLength, &errLength, errMsg);
        
        throw ShaderException(errMsg);
    }
    
    h.modelMatrixUniform = glGetUniformLocation(h.program, ident.uniformModelMatrix);
    h.viewMatrixUniform = glGetUniformLocation(h.program, ident.uniformViewMatrix);
    h.projectionMatrixUniform = glGetUniformLocation(h.program, ident.uniformProjectionMatrix);
   // h.textureUniform = glGetUniformLocation(h.program, ident.uniformTexture);

    h.cameraPositionUniform = glGetUniformLocation(h.program, ident.cameraPosition);

    h.light.colorUniform = glGetUniformLocation(h.program, ident.light.color);
    h.light.positionUniform = glGetUniformLocation(h.program, ident.light.position);
    h.light.ambientIntensityUniform = glGetUniformLocation(h.program, ident.light.ambientIntensity);
    h.light.diffuseIntensityUniform = glGetUniformLocation(h.program, ident.light.diffuseIntensity);

    h.material.diffuseColorUniform = glGetUniformLocation(h.program, ident.material.diffuserColor);
    h.material.specularColorUniform = glGetUniformLocation(h.program, ident.material.specularColor);
    h.material.emittigColorUniform = glGetUniformLocation(h.program, ident.material.emittingColor);
    h.material.shininessUniform = glGetUniformLocation(h.program, ident.material.shininess);
    


    
    glDeleteProgram(vsh);
    glDeleteProgram(fsh);
    
    return h;
}

GLuint Shader::compileShader(Shader::Type type, const GLchar** source) {
    GLint compileOk;
    GLint errLength;
    GLchar* errMsg;
    GLuint shaderHandle = glCreateShader(type);
    
    glShaderSource(shaderHandle, 1, source, 0);
    glCompileShader(shaderHandle);
    
    glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &compileOk);
    if(!compileOk) {
        glGetShaderiv(shaderHandle, GL_INFO_LOG_LENGTH, &errLength);
        errMsg = new GLchar[errLength];
        glGetShaderInfoLog(shaderHandle, errLength, &errLength, errMsg);
        
        throw ShaderException(errMsg);
    }
    
    return shaderHandle;
}
