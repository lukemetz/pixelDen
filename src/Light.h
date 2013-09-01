#pragma once

#include <GL/glew.h>
#include <vector>
#include <memory>
#define GL_SWIZZLE
#include <glm/glm.hpp>

struct Light
{
  typedef std::shared_ptr<Light> Ptr;
  glm::vec3 color;
  glm::vec3 position;
  float intensity;
};

Light::Ptr createLight(glm::vec3 position, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f), float intensity = 1.0f);
