//
//  util.h
//  SEngineX
//
//  Created by Simon McMahon on 15/04/15.
//  Copyright (c) 2015 simonmc.net. All rights reserved.
//

#ifndef __SEngineX__util__
#define __SEngineX__util__

#include <iostream>
#include <glm/glm.hpp>

#ifdef _WINDOWS
	#include <memory>
#endif
#include "Mesh.h"


std::string get_file_contents(const char *filename);

std::string GetFileExtension(const std::string& FileName);

extern SEngineX::Vertex cubeVertices[];

extern GLuint cubeIndices[];

extern SEngineX::Vertex planeVertices[];

extern GLuint planeIndices[];

std::shared_ptr<SEngineX::Mesh> GetCube();

std::shared_ptr<SEngineX::Mesh> GetPlane();

#endif /* defined(__SEngineX__util__) */
