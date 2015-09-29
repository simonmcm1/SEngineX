#include <cmath>


#include "SEngineX/Engine.h"

#include "SEngineX/Shader.h"
#include "SEngineX/Texture.h"
#include "SEngineX/Transform.h"
#include "SEngineX/Camera.h"
#include "SEngineX/PointLight.h"
#include "SEngineX/DirectionalLight.h"
#include "SEngineX/Mesh.h"
#include "SEngineX/Material.h"
#include "SEngineX/RenderInstruction.h"
#include "SEngineX/Object.h"
#include "SEngineX/util.h"
#include "SEngineX/Serializer.h"
#include "SEngineX/Model.h"

using namespace std;

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

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

// Positions of the point lights
glm::vec3 pointLightPositions[] = {
    glm::vec3( 0.0f,  0.0f,  1.0f),
    glm::vec3( 2.3f, -3.3f, -4.0f),
    glm::vec3(-4.0f,  2.0f, -12.0f),
    glm::vec3( 0.0f,  0.0f, -3.0f)
};


class Box : public SEngineX::GameObject {
public:
    shared_ptr<SEngineX::Transform> transform;
    shared_ptr<SEngineX::Mesh> mesh;
    shared_ptr<SEngineX::Material> material;
    
    static int counter;
    int count;
    
    Box() {
        transform = make_shared<SEngineX::Transform>();
        count = counter++;
    }
    
    virtual void  Update() {
        transform->eulerRotation = glm::vec3(0.0f, -(GLfloat)glfwGetTime() * 7.0f * count, 0.0f);
    }
};

int Box::counter = 1;

int main()
{
    SEngineX::Engine &engine = SEngineX::Engine::Instance();
    engine.Init("SEngineX", 800, 600);
     
    auto mat = SEngineX::Serializer::LoadMaterial("woodfloor");
    auto cubemat = SEngineX::Serializer::LoadMaterial("cubemat");
    
    auto cube = GetCube();
    auto plane = GetPlane();
    
    auto camera = make_shared<SEngineX::Camera>(45.0f, 800.0f/600.0f, 0.1f, 100.0f);
    engine.renderer->camera = camera;
    
    camera->transform->eulerRotation = glm::vec3(25.0f, -180.0f, 0.0f);
    camera->transform->position = glm::vec3(0.0f, 2.5f, 5.0f);
    
    engine.renderer->Ambient = glm::vec3(0.1f, 0.1f, 0.1f);
    camera->clearColor = glm::vec4(0.0f, 0.3f, 0.4f, 1.0f);
    
    SEngineX::DirectionalLight dirLight(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.0f, 180.0f, 90.0f));
    //SEngineX::PointLight pLight0(pointLightPositions[0], glm::vec3(0.8f, 0.8f, 0.8f));
    //SEngineX::PointLight pLight1(pointLightPositions[1], glm::vec3(0.8f, 0.8f, 0.8f));
    //SEngineX::PointLight pLight2(pointLightPositions[2], glm::vec3(0.8f, 0.8f, 0.8f));
    //SEngineX::PointLight pLight3(pointLightPositions[3], glm::vec3(0.8f, 0.9f, 0.8f));
    
    //SEngineX::PointLight pLight(glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec3(0.8f, 0.8f, 0.8f));
    
    vector<SEngineX::RenderInstruction> renderInstructions;

    shared_ptr<Box> box = SEngineX::GameObjectFactory::Create<Box>();
    
    auto tf = std::make_shared<SEngineX::Transform>();
    auto ri = SEngineX::RenderInstruction::Create(plane, mat, tf);
    auto cub = SEngineX::RenderInstruction::Create(cube, cubemat, box->transform);
    
    //SEngineX::Model model(resourcePath() + "only_quad_sphere.obj");
    //model.meshes[0]->material = mat;
    //model.meshes[1]->material = mat;
   // for(int i = 0; i < 10; i++) {
   //     shared_ptr<Box> box = SEngineX::GameObjectFactory::Create<Box>();
   //     box->transform->position = cubePositions[i];
   //     renderInstructions.push_back(SEngineX::RenderInstruction(mesh, mat, box->transform));
   // }
    
    engine.StartGameLoop();
    
    return 0;
    
}




