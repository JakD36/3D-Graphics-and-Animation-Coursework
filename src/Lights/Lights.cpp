//
// Created by Jack Davidson on 11/03/2020.
//

#include "Lights.hpp"
#include <GL/glew.h>

LightUniformBuffer::LightUniformBuffer() noexcept
{
    glGenBuffers(1, &m_uniformBufferObject);
    glBindBuffer(GL_UNIFORM_BUFFER, m_uniformBufferObject);
    glBufferData(GL_UNIFORM_BUFFER, k_lightStructByteSize * k_lightCount, NULL, GL_STATIC_DRAW); // allocate 96 bytes of memory
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

LightUniformBuffer::~LightUniformBuffer() noexcept
{
    glDeleteBuffers(1,&m_uniformBufferObject);
}

void LightUniformBuffer::UpdateData(const LightData* lights) noexcept
{
    glBindBufferRange(GL_UNIFORM_BUFFER, 0, m_uniformBufferObject, 0, k_lightStructByteSize * k_lightCount);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, k_lightStructByteSize * k_lightCount, lights);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}