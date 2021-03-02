//
// Created by Jack Davidson on 02/05/2020.
//

#ifndef INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_RENDERPASS_H
#define INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_RENDERPASS_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "../Texture/Texture.hpp"

class GameObject;

struct TextureShaderParam
{
    GLint m_location;
    Texture m_texture;
};

struct Uniformf
{
    GLint m_location;
    std::string m_key;
    float m_value;
};

struct Uniform3fv
{
    GLint m_location;
    std::string m_key;
    glm::vec3 m_value;
};

struct Uniform4fv
{
    GLint m_location;
    std::string m_key;
    glm::vec4 m_value;
};

class RenderPass
{
public:
    GLuint m_program;
    GLenum m_cullFace;
    std::vector<TextureShaderParam> m_textures;
    std::vector<Uniformf> m_uniformf;
    std::vector<Uniform3fv> m_uniform3fv;
    std::vector<Uniform4fv> m_uniform4fv;

    RenderPass(nlohmann::json passJson);

    void Bind();

    void SetCameraPosition(glm::vec3 position);
    void SetMatrix4x4(std::string name, glm::mat4 &mat);
};

#endif //INC_3D_GRAPHICS_AND_ANIMATION_COURSEWORK_2018_RENDERPASS_H
