#pragma once

#include <GL/glew.h>
#include <vector>
#include <memory>
#include <glm/glm.hpp>

#include "Geometry.h"

struct Model
{
  typedef std::shared_ptr<Model> Ptr;
  glm::mat4 pose;
  Geometry::Ptr geometry;
};

Model::Ptr createModel(Geometry::Ptr geometry);
