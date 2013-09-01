#include "Light.h"

Light::Ptr createLight(glm::vec3 position, glm::vec3 color, float intensity)
{
  Light::Ptr light = std::make_shared<Light>();
  light->position = position;
  light->color = color;
  light->intensity = intensity;
  return light;
};
