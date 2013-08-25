#pragma once

#include <GL/glew.h>
#include <vector>
#include <memory>
#include <glm/glm.hpp>

#include "Model.h"
#include "Program.h"

struct Camera
{
  typedef std::shared_ptr<Camera> Ptr;
  glm::mat4 projection = glm::mat4(1.0f);
  glm::mat4 view = glm::mat4(1.0f);
};

Camera::Ptr createCamera();
void renderModelFromCamera(Camera::Ptr camera, Model::Ptr model, Program::Ptr program);
