//
//  terrain.h
//  OpenGLTut
//
//  Created by Laszlo Korte on 02.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLTut__terrain__
#define __OpenGLTut__terrain__

#include "../graphics/base.hpp"
#include <string>

namespace terrain {
    Mesh loadTerrain(std::string path);
};

#endif /* defined(__OpenGLTut__terrain__) */
