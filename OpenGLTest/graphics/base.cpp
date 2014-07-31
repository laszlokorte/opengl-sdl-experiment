//
//  base.cpp
//  OpenGLTest
//
//  Created by Laszlo Korte on 30.07.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "base.hpp"
#include "glm/glm.hpp"
#include <cmath>
#include <iostream>


void Light::prepareRender(const LightHandle &h) const
{
    glUniform3f(h.colorUniform, color.R, color.G, color.B);
    glUniform1f(h.ambientIntensityUniform, ambientIntensity);
    glUniform3f(h.positionUniform, position.X, position.Y, position.Z);
    glUniform1f(h.diffuseIntensityUniform, diffuseIntensity);
}
void Light::finishRender(const LightHandle &h) const {}


namespace mesh {
    Mesh makeCube() {
        std::vector<Vertex> vertices = {
            // Front
            {.Position = { 1,-1, 1}, .Normal = {0,0,1}, .Color = {1, 1, 1, 1}, .TextureCoord = {1,1}},
            {.Position = { 1, 1, 1}, .Normal = {0,0,1}, .Color = {1, 1, 1, 1}, .TextureCoord = {1,0}},
            {.Position = {-1, 1, 1}, .Normal = {0,0,1}, .Color = {1, 1, 1, 1}, .TextureCoord = {0,0}},
            {.Position = {-1,-1, 1}, .Normal = {0,0,1}, .Color = {1, 1, 1, 1}, .TextureCoord = {0,1}},
            
            // Back
            {.Position = {-1,-1, -1}, .Normal = {0,0,-1}, .Color = {1, 1, 1, 1}, .TextureCoord = {1,1}},
            {.Position = {-1, 1, -1}, .Normal = {0,0,-1}, .Color = {1, 1, 1, 1}, .TextureCoord = {1,0}},
            {.Position = { 1, 1, -1}, .Normal = {0,0,-1}, .Color = {1, 1, 1, 1}, .TextureCoord = {0,0}},
            {.Position = { 1,-1, -1}, .Normal = {0,0,-1}, .Color = {1, 1, 1, 1}, .TextureCoord = {0,1}},
            
            // Left
            {.Position = {-1,-1, 1}, .Normal = {-1,0,0}, .Color = {1, 1, 1, 1}, .TextureCoord = {1,1}},
            {.Position = {-1, 1, 1}, .Normal = {-1,0,0}, .Color = {1, 1, 1, 1}, .TextureCoord = {1,0}},
            {.Position = {-1, 1, -1}, .Normal = {-1,0,0}, .Color = {1, 1, 1, 1}, .TextureCoord = {0,0}},
            {.Position = {-1,-1, -1}, .Normal = {-1,0,0}, .Color = {1, 1, 1, 1}, .TextureCoord = {0,1}},
            
            // Right
            {.Position = { 1,-1, -1}, .Normal = {1,0,0}, .Color = {1, 1, 1, 1}, .TextureCoord = {0,1}},
            {.Position = { 1, 1, -1}, .Normal = {1,0,0}, .Color = {1, 1, 1, 1}, .TextureCoord = {0,0}},
            {.Position = { 1, 1, 1}, .Normal = {1,0,0}, .Color = {1, 1, 1, 1}, .TextureCoord = {1,0}},
            {.Position = { 1,-1, 1}, .Normal = {1,0,0}, .Color = {1, 1, 1, 1}, .TextureCoord = {1,1}},

            // Top
            {.Position = { 1, 1, -1}, .Normal = {0,1,0}, .Color = {1, 1, 1, 1}, .TextureCoord = {1,1}},
            {.Position = {-1, 1, -1}, .Normal = {0,1,0}, .Color = {1, 1, 1, 1}, .TextureCoord = {0,1}},
            {.Position = {-1, 1, 1}, .Normal = {0,1,0}, .Color = {1, 1, 1, 1}, .TextureCoord = {0,0}},
            {.Position = { 1, 1, 1}, .Normal = {0,1,0}, .Color = {1, 1, 1, 1}, .TextureCoord = {1,0}},

            // Bottom
            {.Position = {-1,-1,  1}, .Normal = {0,-1,0}, .Color = {1, 1, 1, 1}, .TextureCoord = {1,1}},
            {.Position = {-1,-1, -1}, .Normal = {0,-1,0}, .Color = {1, 1, 1, 1}, .TextureCoord = {1,0}},
            {.Position = { 1,-1, -1}, .Normal = {0,-1,0}, .Color = {1, 1, 1, 1}, .TextureCoord = {0,0}},
            {.Position = { 1,-1,  1}, .Normal = {0,-1,0}, .Color = {1, 1, 1, 1}, .TextureCoord = {0,1}},
        };
        
        std::vector<Triangle> triangles = {
            // Front
            {0, 1, 2},
            {2, 3, 0},
            // Back
            {4, 5, 6},
            {6, 7, 4},
            // Left
            {8, 9, 10},
            {10, 11, 8},
            // Right
            {12, 13, 14},
            {14, 15, 12},
            // Top
            {16, 17, 18},
            {18, 19, 16},
            // Bottom
            {20, 21, 22},
            {22, 23, 20},
        };
        
        return Mesh(vertices, triangles);
    }
    
    Mesh makePyramid() {
        std::vector<Vertex> vertices = {
            // Base
            {.Position = { 1,-1, 1}, .Normal = {0,0,0}, .Color = {0, 1, 0, 1}},
            {.Position = {-1,-1, 1}, .Normal = {0,0,0}, .Color = {0, 0, 0, 1}},
            {.Position = {-1,-1, -1}, .Normal = {0,0,0}, .Color = {0, 0, 1, 1}},
            {.Position = { 1,-1, -1}, .Normal = {0,0,0}, .Color = {0, 1, 1, 1}},

            // Tip
            {.Position = {0, 1, 0}, .Normal = {0,0,0}, .Color = {1, 0, 1, 1}},
        };
        
        std::vector<Triangle> triangles = {
            // Floor
            {0, 1, 2},
            {2, 3, 0},

            //Sides
            {1, 0, 4},
            {2, 1, 4},
            {3, 2, 4},
            {0, 3, 4},
        };
        
        return Mesh(vertices, triangles);
    }
    
    Mesh makeCylinder(unsigned int sides, float height, float radius) {
        std::vector<Vertex> vertices;
        std::vector<Triangle> triangles;
        
        if(sides < 3) {
            sides = 3;
        }
        
        
        float h2 = height/2;
        
        float theta = 2 * M_PI / float(sides);
        float c = cos(theta);//precalculate the sine and cosine
        float s = sin(theta);
        float t;
        
        glm::vec2 p(radius, 0);
        
        for(GLuint ii = 0; ii < sides*2; ii++)
        {
            vertices.push_back(Vertex{{p.x,-h2, p.y},{0,0,0}, {1, 0, 1, 1}});
            vertices.push_back(Vertex{{p.x,h2, p.y},{0,0,0}, {1, 1, 0, 1}});
            
            //apply the rotation matrix
            t = p.x;
            p.x = c * p.x - s * p.y;
            p.y = s * t + c * p.y;
        }
        
        vertices.push_back(Vertex{{0,-h2, 0},{0,0,0}, {0, 1, 1, 1}});
        vertices.push_back(Vertex{{0,h2, 0},{0,0,0}, {0, 1, 1, 1}});
        
        for(GLuint ii = 0; ii <= sides*2; ii+=2) {
            triangles.push_back(Triangle{ii,ii+1,ii+2});
            triangles.push_back(Triangle{ii+2,ii+1,(ii+3)%(sides*2)});
            
            triangles.push_back(Triangle{sides*4, ii,(ii+2)});
            triangles.push_back(Triangle{ii+1,sides*4+1,(ii+3)});
        }
        
        return Mesh(vertices, triangles);
    }
}

Mesh::Mesh(const std::vector<Vertex> _vertices, const std::vector<Triangle> _triangles) : vertices(_vertices), triangles(_triangles) {
    
    
}