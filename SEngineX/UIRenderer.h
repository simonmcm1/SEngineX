//
//  UIRenderer.h
//  SEngineX
//
//  Created by Simon McMahon on 11/08/15.
//  Copyright (c) 2015 simonmc.net. All rights reserved.
//

#ifndef __SEngineX__UIRenderer__
#define __SEngineX__UIRenderer__

#include <ft2build.h>
#include FT_FREETYPE_H
#include <map>
#include "Shader.h"
#include <glm/glm.hpp>

namespace SEngineX {
    
    struct Character {
        GLuint     TextureID;  // ID handle of the glyph texture
        glm::ivec2 Size;       // Size of glyph
        glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
        GLuint     Advance;    // Offset to advance to next glyph
    };
    
    class UIRenderer {
        FT_Library ft;
        FT_Face face;
        std::map<GLchar, Character> Characters;
        GLuint VAO;
        GLuint VBO;
        
        std::shared_ptr<Shader> textShader;
        
        void DrawText(std::string text, float x, float y, float scale, glm::vec3 color);
        
    public:
        UIRenderer();
        void Render();
        
    };
    

}





#endif /* defined(__SEngineX__UIRenderer__) */
