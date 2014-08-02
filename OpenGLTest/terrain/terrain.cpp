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
#include <SDL2_image/SDL_image.h>

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
                float h = (p&0xff)/3E1;
                float u = x/(float)width;
                float v = y/(float)height;
                printf("%x\n", p);
                std::cout << fx << "," << fy << "," << h << "\n";
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
        
        SDL_FreeSurface(img);
        
        return Mesh(vertices, triangles);
    };
};