//
//  util.cpp
//  SEngineX
//
//  Created by Simon McMahon on 15/04/15.
//  Copyright (c) 2015 simonmc.net. All rights reserved.
//

#include "util.h"

#include <fstream>
#include <streambuf>
#include <string>
#include <cerrno>

std::string get_file_contents(const char *filename)
{
    std::ifstream in(filename, std::ios::in | std::ios::binary);
    if (in)
    {
        return(std::string((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>()));
    }
    throw(errno);
}

std::string GetFileExtension(const std::string& FileName)
{
    if(FileName.find_last_of(".") != std::string::npos)
        return FileName.substr(FileName.find_last_of(".")+1);
        return "";
}

GLuint cubeIndices[] = {
    0, 2, 1,
    3,5, 4,
    6,7, 8,
    9,10, 11,
    12,13,14,
    15,16,17,
    18,20,19,
    21,23,22,
    24,25,26,
    27,28,29,
    30,32,31,
    33,35,34,
    
};

SEngineX::Vertex cubeVertices[] = {
    // Positions           // Normals           // Texture Coords
    glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec3(0.0f,  0.0f, -1.0f),  glm::vec2(0.0f, 0.0f),
    glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec3(0.0f,  0.0f, -1.0f),  glm::vec2(1.0f, 0.0f),
    glm::vec3(0.5f,  0.5f, -0.5f),  glm::vec3(0.0f,  0.0f, -1.0f),  glm::vec2(1.0f, 1.0f),
    glm::vec3(0.5f,  0.5f, -0.5f),  glm::vec3(0.0f,  0.0f, -1.0f),  glm::vec2(1.0f, 1.0f),
    glm::vec3(-0.5f,  0.5f, -0.5f),  glm::vec3(0.0f,  0.0f, -1.0f),  glm::vec2(0.0f, 1.0f),
    glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec3(0.0f,  0.0f, -1.0f),  glm::vec2(0.0f, 0.0f),
    
    glm::vec3(-0.5f, -0.5f,  0.5f),  glm::vec3(0.0f,  0.0f, 1.0f),   glm::vec2(0.0f, 0.0f),
    glm::vec3(0.5f, -0.5f,  0.5f),  glm::vec3(0.0f,  0.0f, 1.0f),   glm::vec2(1.0f, 0.0f),
    glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec3(0.0f,  0.0f, 1.0f),   glm::vec2(1.0f, 1.0f),
    glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec3(0.0f,  0.0f, 1.0f),   glm::vec2(1.0f, 1.0f),
    glm::vec3(-0.5f,  0.5f,  0.5f),  glm::vec3(0.0f,  0.0f, 1.0f),   glm::vec2(0.0f, 1.0f),
    glm::vec3(-0.5f, -0.5f,  0.5f),  glm::vec3(0.0f,  0.0f, 1.0f),   glm::vec2(0.0f, 0.0f),
    
    glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(-1.0f,  0.0f,  0.0f),  glm::vec2(1.0f, 0.0f),
    glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(-1.0f,  0.0f,  0.0f),  glm::vec2(1.0f, 1.0f),
    glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f,  0.0f,  0.0f),  glm::vec2(0.0f, 1.0f),
    glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f,  0.0f,  0.0f),  glm::vec2(0.0f, 1.0f),
    glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(-1.0f,  0.0f,  0.0f),  glm::vec2(0.0f, 0.0f),
    glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(-1.0f,  0.0f,  0.0f),  glm::vec2(1.0f, 0.0f),
    
    glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec3(1.0f,  0.0f,  0.0f),  glm::vec2(1.0f, 0.0f),
    glm::vec3(0.5f,  0.5f, -0.5f),  glm::vec3(1.0f,  0.0f,  0.0f),  glm::vec2(1.0f, 1.0f),
    glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec3(1.0f,  0.0f,  0.0f),  glm::vec2(0.0f, 1.0f),
    glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec3(1.0f,  0.0f,  0.0f),  glm::vec2(0.0f, 1.0f),
    glm::vec3(0.5f, -0.5f,  0.5f),  glm::vec3(1.0f,  0.0f,  0.0f),  glm::vec2(0.0f, 0.0f),
    glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec3(1.0f,  0.0f,  0.0f),  glm::vec2(1.0f, 0.0f),
    
    glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec3(0.0f, -1.0f,  0.0f),  glm::vec2(0.0f, 1.0f),
    glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec3(0.0f, -1.0f,  0.0f),  glm::vec2(1.0f, 1.0f),
    glm::vec3(0.5f, -0.5f,  0.5f),  glm::vec3(0.0f, -1.0f,  0.0f),  glm::vec2(1.0f, 0.0f),
    glm::vec3(0.5f, -0.5f,  0.5f),  glm::vec3(0.0f, -1.0f,  0.0f),  glm::vec2(1.0f, 0.0f),
    glm::vec3(-0.5f, -0.5f,  0.5f),  glm::vec3(0.0f, -1.0f,  0.0f),  glm::vec2(0.0f, 0.0f),
    glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec3(0.0f, -1.0f,  0.0f),  glm::vec2(0.0f, 1.0f),
    
    glm::vec3(-0.5f,  0.5f, -0.5f),  glm::vec3(0.0f,  1.0f,  0.0f),  glm::vec2(0.0f, 1.0f),
    glm::vec3(0.5f,  0.5f, -0.5f),  glm::vec3(0.0f,  1.0f,  0.0f),  glm::vec2(1.0f, 1.0f),
    glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec3(0.0f,  1.0f,  0.0f),  glm::vec2(1.0f, 0.0f),
    glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec3(0.0f,  1.0f,  0.0f),  glm::vec2(1.0f, 0.0f),
    glm::vec3(-0.5f,  0.5f,  0.5f),  glm::vec3(0.0f,  1.0f,  0.0f),  glm::vec2(0.0f, 0.0f),
    glm::vec3(-0.5f,  0.5f, -0.5f),  glm::vec3(0.0f,  1.0f,  0.0f),  glm::vec2(0.0f, 1.0f)
};


std::shared_ptr<SEngineX::Mesh> GetCube() {
    return std::make_shared<SEngineX::Mesh>(std::vector<SEngineX::Vertex>(std::begin(cubeVertices), std::end(cubeVertices)), std::vector<GLuint>(std::begin(cubeIndices), std::end(cubeIndices)));
}


SEngineX::Vertex planeVertices[] = {
    // Positions          // Normals         // Texture Coords
    glm::vec3(8.0f, -0.5f,  8.0f),  glm::vec3(0.0f, 1.0f, 0.0f),  glm::vec2(1.0f, 0.0f),
    glm::vec3(-8.0f, -0.5f,  8.0f),  glm::vec3(0.0f, 1.0f, 0.0f),  glm::vec2(0.0f, 0.0f),
    glm::vec3(-8.0f, -0.5f, -8.0f),  glm::vec3(0.0f, 1.0f, 0.0f),  glm::vec2(0.0f, 1.0f),
                                               
    glm::vec3(8.0f, -0.5f,  8.0f),  glm::vec3(0.0f, 1.0f, 0.0f),  glm::vec2(1.0f, 0.0f),
    glm::vec3(-8.0f, -0.5f, -8.0f),  glm::vec3(0.0f, 1.0f, 0.0f),  glm::vec2(0.0f, 1.0f),
    glm::vec3(8.0f, -0.5f, -8.0f),  glm::vec3(0.0f, 1.0f, 0.0f),  glm::vec2(1.0f, 1.0f)
};

//vertices ended up in CW somehow
GLuint planeIndices[] = {
    0,2,1,
    3,5,4
};

std::shared_ptr<SEngineX::Mesh> GetPlane() {
    return std::make_shared<SEngineX::Mesh>(std::vector<SEngineX::Vertex>(std::begin(planeVertices), std::end(planeVertices)), std::vector<GLuint>(std::begin(planeIndices), std::end(planeIndices)));
}


