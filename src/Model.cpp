#include "Model.h"

Model::Ptr createModel(Geometry::Ptr geometry)
{
  Model::Ptr model = std::make_shared<Model>();
  model->geometry = geometry;
  model->pose = glm::mat4(1.0f);

  return model;
}
