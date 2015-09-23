//
//  Serializer.h
//  SEngineX
//
//  Created by Simon McMahon on 16/06/15.
//  Copyright (c) 2015 simonmc.net. All rights reserved.
//

#ifndef __SEngineX__Serializer__
#define __SEngineX__Serializer__

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <iostream>
#include <string>
#include <vector>
#include "util.h"
#include "Shader.h"
#include "Material.h"
#include "Resources.h"

namespace SEngineX {
    class Serializer {
    public:
        static std::shared_ptr<Shader> LoadShader(std::string shaderName);
        static std::shared_ptr<Material> LoadMaterial(std::string materialName);
    };
}


#endif /* defined(__SEngineX__Serializer__) */
