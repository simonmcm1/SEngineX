//
//  Mesh.h
//  SEngineX
//
//  Created by Simon McMahon on 11/06/15.
//  Copyright (c) 2015 simonmc.net. All rights reserved.
//

#ifndef __SEngineX__Mesh__
#define __SEngineX__Mesh__

#include <iostream>
#include <glm/glm.hpp>
#include <String>
#include <vector>
#include "Object.h"

namespace SEngineX {

    struct Vertex {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 TexCoords;
    };

    class Mesh : Object {
    public:

        std::vector<Vertex> vertices;
        std::vector<GLuint> indices;
        
        Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices);
        ~Mesh();
        void Draw();
        void SetupMesh();
    private:
        GLuint VAO;
        GLuint VBO;
        GLuint EBO;
        
        
    };

}
#endif /* defined(__SEngineX__Mesh__) */
