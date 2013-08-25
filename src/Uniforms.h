#pragma once

#include <GL/glew.h>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Program.h"

void setUniform(Program::Ptr program, std::string uniformName, glm::mat4 value)
{
  GLint uniformLocation = glGetUniformLocation(program->glProgram, uniformName.c_str());
  glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
}

void setUniform(Program::Ptr program, std::string uniformName, glm::vec3 value)
{
  GLint uniformLocation = glGetUniformLocation(program->glProgram, uniformName.c_str());
  glUniform3fv(uniformLocation, 1, glm::value_ptr(value));
}
