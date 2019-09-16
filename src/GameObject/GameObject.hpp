//
//  GameObject.hpp
//  3D Graphics and Animation Coursework
//
//  Created by Jack Davidson on 06/04/2019.
//  Copyright © 2019 Jack Davidson. All rights reserved.
//

#ifndef GameObject_hpp
#define GameObject_hpp

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdio.h>

using namespace std;

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <gli/gli.hpp>
#include <GLM/gtx/transform.hpp>

#include "../Mesh/Mesh.hpp"
#include "../Material/Material.hpp"
#include "../Texture/Texture.hpp"
#include "../Shaders/ShaderPipeline.hpp"
#include "../Shaders/VertexShader.hpp"
#include "../Shaders/FragShader.hpp"

#include "../ModelObjects/modelObject.h"
#include "../Utils/profile.h"
#include "../ResourceManager/ResourceService.hpp"

class GameObject {
public:
    glm::vec3 m_position  = glm::vec3(0.f,0.f,0.f);
    glm::vec3 m_rotation  = glm::vec3(0.f,0.f,0.f);
    glm::vec3 m_scale     = glm::vec3(1.f,1.f,1.f);
    
    GameObject(Mesh*, Material*, Texture*, ShaderPipeline*);
    GameObject(string mesh, string mat, string tex, ShaderPipeline*);
    
    Mesh* m_mesh;
    Texture* m_texture;
    Material* m_material;
    ShaderPipeline* m_shaderPipeline;
    VertexShader* m_vs;
    FragShader* m_fs;
    
    void Render(glm::mat4&,glm::mat4&,lightStruct[],glm::vec3&);
};

#endif /* GameObject_hpp */
