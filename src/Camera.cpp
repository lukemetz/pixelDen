#include "Camera.h"
#include "Program.h"
#include "Uniforms.h"

Camera::Ptr createCamera()
{
  Camera::Ptr camera = std::make_shared<Camera>();
  return camera;
}

void renderModelFromCamera(Camera::Ptr camera, Model::Ptr model, Program::Ptr program)
{
  glUseProgram(program->glProgram);
  glm::mat4 modelViewProjection = camera->projection * camera->view * model->pose;
  setUniform(program, "uModelView", modelViewProjection);

  drawGeometry(model->geometry);

  glUseProgram(0);
}
