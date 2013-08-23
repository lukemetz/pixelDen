#pragma once

#include <GL/glew.h>
#include <vector>
#include <memory>
#include "Shader.h"

struct Program
{
  typedef std::shared_ptr<Program> Ptr;

  GLuint glProgram = 0;

};

Program::Ptr createProgramWithShaders(std::vector<Shader::Ptr> shaders);
