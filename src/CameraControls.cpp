#include "CameraControls.h"
#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
void CameraControls::panHorizontal(Camera::Ptr camera, float delta, float scale)
{
  glm::vec4 leftUnit = camera->view * glm::vec4(1, 0, 0, 0);

  camera->view = glm::translate(camera->view, leftUnit.xyz() * scale * delta);
}
void CameraControls::panInto(Camera::Ptr camera, float delta, float scale)
{
  glm::vec4 leftUnit = camera->view * glm::vec4(0, 0, 1, 0);

  camera->view = glm::translate(camera->view, leftUnit.xyz() * scale * delta);
}
