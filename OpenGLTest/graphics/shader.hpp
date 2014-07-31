//
//  shader.h
//  OpenGLTest
//
//  Created by Laszlo Korte on 28.07.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLTest__shader__
#define __OpenGLTest__shader__

#ifdef __APPLE__
# define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
#endif

#include <exception>
#include <string>

#include <OpenGL/gl3.h>
#include <SDL2/SDL_opengl.h>
#include "base.hpp"

class ShaderException : public std::exception {
public:
    const std::string error;

    ShaderException(char err[]) : error(err) {
    }
};

class Shader {
    enum Type {
        Vertex = GL_VERTEX_SHADER,
        Fragment = GL_FRAGMENT_SHADER
    };
    
    struct Handles {
        GLuint program = -1;
        GLuint positionLocation = -1;
        GLuint normalLocation = -1;
        GLuint colorLocation = -1;
        GLuint texCoordLocation = -1;
        GLuint modelMatrixUniform = -1;
        GLuint viewMatrixUniform = -1;
        GLuint projectionMatrixUniform = -1;
        GLuint textureUniform = -1;
        GLuint cameraPositionUniform = -1;
        
        LightHandle light;
        MaterialHandle material;
    };
    
    
public:
    const Handles handles;
    static const struct Identifiers {
        const char* uniformModelMatrix = "uModelMatrix";
        const char* uniformViewMatrix = "uViewMatrix";
        const char* uniformProjectionMatrix = "uProjectionMatrix";
        const char* uniformTexture = "uTexture";
        const char* vertexPosition = "vPosition";
        const char* vertexNormal = "vNormal";
        const char* vertexColor = "vColor";
        const char* vertexTexCoord = "vTexCoord";
        const char* cameraPosition = "cameraPosition";
        
        struct {
            const char* color = "uLight.color";
            const char* position = "uLight.position";
            const char* ambientIntensity = "uLight.ambientIntensity";
            const char* diffuseIntensity = "uLight.diffuseIntensity";
        } light;
        
        struct {
            const char* specularIntensity = "uMaterial.specularIntensity";
            const char* shininess = "uMaterial.shininess";
        } material;
    } identifiers;

    
    explicit Shader(const GLchar** vsh, const GLchar** fsh) throw (ShaderException);
    
    ~Shader();
    
    void prepareRender() const;
    
    void finishRender() const;
    
private:
    
    Handles createProgram(const GLchar** vertexShader, const GLchar** fragmentShader, Identifiers ident);
    
    GLuint compileShader(Type type, const GLchar** source);
    
};


#endif /* defined(__OpenGLTest__shader__) */
