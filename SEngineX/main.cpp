#include <cmath>

#include "Engine.h"
#include "util.h"
#include "ResourcePath.hpp"
#include "Shader.h"
#include "Texture.h"
#include "Transform.h"
#include "Camera.h"

using namespace std;

int main()
{
    auto engine = SEngineX::Engine::Init("SEngineX", 800, 600);

    GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    
    GLuint elements[] = {
        0, 1, 2,
        3,4, 5,
        6,7, 8,
        9,10, 11,
        12,13,14,
        15,16,17,
        18,19,20,
        21,22,23,
        24,25,26,
        27,28,29,
        30,31,32,
        33,34,35,
        
    };
    
    GLuint vbo;
    glGenBuffers(1, &vbo); // Generate 1 buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements,
                 GL_STATIC_DRAW);

    vector<SEngineX::ShaderAttribute> attributes {
        SEngineX::ShaderAttribute("position", SEngineX::ShaderAttributeType::FLOAT3),
        SEngineX::ShaderAttribute("texCoord", SEngineX::ShaderAttributeType::FLOAT2)
    };
    
    vector<SEngineX::ShaderAttribute> uniforms {
        SEngineX::ShaderAttribute("_Color", SEngineX::ShaderAttributeType::FLOAT3),
        SEngineX::ShaderAttribute("_MainTex", SEngineX::ShaderAttributeType::TEXTURE2D),
        SEngineX::ShaderAttribute("_AltTex", SEngineX::ShaderAttributeType::TEXTURE2D),
        SEngineX::ShaderAttribute("_MVP", SEngineX::ShaderAttributeType::MATRIX)
    };
    
    SEngineX::Shader basicShader("basic", attributes, uniforms);
    basicShader.Use();
    basicShader.EnableAttributes();
    
    SEngineX::Texture2D texture("container.jpg");
    
    SEngineX::Texture2D faceTex("awesomeface.png");

    basicShader.SetUniformTexture("_MainTex", 0);
    basicShader.SetUniformTexture("_AltTex", 1);
    
    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)  
    };
    
    vector<SEngineX::Transform> boxes;
    
    for(int i = 0; i < 10; i++) {
        SEngineX::Transform box;
        box.position = cubePositions[i];
        boxes.push_back(box);
    }
    
    glm::mat4 view;
    glm::mat4 projection;
    
    glEnable(GL_DEPTH_TEST);
    
    SEngineX::Camera camera(45.0f, 800.0f/600.0f, 0.1f, 100.0f);
    projection = camera.GetProjectionMatrix();
    
    camera.transform->eulerRotation = glm::vec3(0.0f, 180.0f, 0.0f);
    camera.transform->position = glm::vec3(0.0f, 0.0f, 3.0f);
    auto t_start = std::chrono::high_resolution_clock::now();
    
    while(!glfwWindowShouldClose(engine->window))
    {
        // Clear the screen to black
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        auto t_now = std::chrono::high_resolution_clock::now();
        float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();

        
        GLfloat radius = 10.0f;
        GLfloat camX = sin(glfwGetTime()) * radius;
        GLfloat camZ = cos(glfwGetTime()) * radius;
        glm::mat4 view;
        view = camera.GetViewMatrix();
        
        texture.Bind(0);
        faceTex.Bind(1);
        glBindVertexArray(vao);
        int i = 0;
        for(auto& box : boxes) {
            i++;
            box.eulerRotation = glm::vec3(-55.0f, (GLfloat)glfwGetTime() * 7.0f * i, 0.0f);
            glm::mat4 mvp = projection * view * *box.GetMatrix();
            basicShader.SetUniformMatrix("_MVP", mvp);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        }
        
        glBindVertexArray(0);
        // Swap buffers and poll window events
        glfwSwapBuffers(engine->window);
        glfwPollEvents();
    }
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    
    return 0;

}
