#include "CameraControls.h"
#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
void CameraControls::panHorizontal(Camera::Ptr camera, float amount)
{
  camera->view = glm::translate(glm::mat4(1.0f), glm::vec3(1, 0, 0) * amount) * camera->view;
}
void CameraControls::panInto(Camera::Ptr camera, float amount)
{
  camera->view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 1) * amount) * camera->view;
}

void CameraControls::rotateHorizontal(Camera::Ptr camera, float amount)
{
  camera->view = glm::rotate(glm::mat4(1.0f), amount, glm::vec3(0, 1, 0)) * camera->view ;
}

void CameraControls::rotateVertical(Camera::Ptr camera, float amount)
{
  camera->view = glm::rotate(glm::mat4(1.0f), amount , glm::vec3(1, 0, 0)) * camera->view ;
}
