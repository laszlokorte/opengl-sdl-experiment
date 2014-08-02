//
//  terrain.cpp
//  OpenGLTut
//
//  Created by Laszlo Korte on 02.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "terrain.hpp"

#include <iostream>
#include <vector>
#include <map>
#include <SDL2_image/SDL_image.h>

#include "glm/glm.hpp"

namespace terrain {
    Mesh loadTerrain(std::string path)
    {
        SDL_Surface * img = IMG_Load(path.c_str());
        
        GLuint width = img->w;
        GLuint height = img->h;
        Uint32 *pixels = (Uint32 *)img->pixels;
        std::vector<Vertex> vertices;
        std::vector<Triangle> triangles;
        GLuint vertexCount = width*height;
        
        for(int x=0;x<width;x++) {
            for(int y=0;y<height;y++) {
                Uint32 p = pixels[ ( y * width ) + x ];
                float fx = (float)x-width/2;
                float fy = (float)y-height/2;
                float h = (p&0xff)/1E1;
                float u = x/(float)width;
                float v = y/(float)height;
                vertices.push_back(Vertex{.Position={fx,h,fy}, .Normal={1,1,1},.Color={1,1,1,1},.TextureCoord={u,v}});
            }
        }
        
        for(GLuint i=0;i<vertexCount-height;i++) {
            if((i+1)%height == 0) {
                continue;
            }
            triangles.push_back(Triangle{i+height,i,i+height+1});
            triangles.push_back(Triangle{i,i+1, i+1+height});
        }
        
        GLuint triangleCount = (GLuint)triangles.size();
        std::map<int, std::vector<glm::vec3>> normalMap;
        
        for(GLuint i=0;i<triangleCount;i++) {
            Vertex v1 = vertices[triangles[i].A];
            Vertex v2 = vertices[triangles[i].B];
            Vertex v3 = vertices[triangles[i].C];
            
            Vec3 v1p = v1.Position;
            Vec3 v2p = v2.Position;
            Vec3 v3p = v3.Position;
            
            glm::vec3 a = glm::vec3(v1p.X-v2p.X, v1p.Y-v2p.Y, v1p.Z-v2p.Z);
            
            glm::vec3 b = glm::vec3(v1p.X-v3p.X, v1p.Y-v3p.Y, v1p.Z-v3p.Z);
            
            glm::vec3 normal = glm::normalize(glm::cross(a,b));
            
            if(normalMap.count(triangles[i].A) == 0) {
                normalMap.emplace(triangles[i].A, std::vector<glm::vec3>());
            }
            
            if(normalMap.count(triangles[i].B) == 0) {
                normalMap.emplace(triangles[i].B, std::vector<glm::vec3>());
            }
            
            if(normalMap.count(triangles[i].C) == 0) {
                normalMap.emplace(triangles[i].C, std::vector<glm::vec3>());
            }
            
            normalMap.at(triangles[i].A).push_back(normal);
            normalMap.at(triangles[i].B).push_back(normal);
            normalMap.at(triangles[i].C).push_back(normal);
        }
        
        
        for(GLuint i=0;i<vertexCount;i++) {
            auto normalList = normalMap.at(i);
            long normalCount = normalList.size();
            glm::vec3 avgNormal;

            for(long n=0;n<normalCount;n++) {
                avgNormal += normalList[n];
            }
            avgNormal /= normalCount;
            
            vertices[i].Normal = Vec3{avgNormal.x, avgNormal.y, avgNormal.z};
        }
        
        SDL_FreeSurface(img);
        
        return Mesh(vertices, triangles);
    };
};