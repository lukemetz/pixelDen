#pragma once

#include <GL/glew.h>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Program.h"
#include "Light.h"
#include "Texture.h"

void setUniform(Program::Ptr program, std::string uniformName, glm::mat4 value)
{
  GLint uniformLocation = glGetUniformLocation(program->glProgram, uniformName.c_str());
  glProgramUniformMatrix4fv(program->glProgram, uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
}

void setUniform(Program::Ptr program, std::string uniformName, glm::vec3 value)
{
  GLint uniformLocation = glGetUniformLocation(program->glProgram, uniformName.c_str());
  glProgramUniform3fv(program->glProgram, uniformLocation, 1, glm::value_ptr(value));
}

void setUniform(Program::Ptr program, std::string uniformName, float value)
{
  GLint uniformLocation = glGetUniformLocation(program->glProgram, uniformName.c_str());
  glProgramUniform1f(program->glProgram, uniformLocation, value);
}

void setLightUniform(Program::Ptr program, Light::Ptr light)
{
  setUniform(program, "light.color", light->color);
  setUniform(program, "light.position", light->position);
  setUniform(program, "light.intensity", light->intensity);
}

void setUniformTexture(Program::Ptr program, std::string uniformName, Texture::Ptr texture, int textureUnit)
{
  GLint imageLoc = glGetUniformLocation(program->glProgram, uniformName.c_str());
  glProgramUniform1i(program->glProgram, imageLoc, textureUnit);
  glActiveTexture(GL_TEXTURE0 + textureUnit);
  glBindTexture(GL_TEXTURE_2D, texture->glTexture);
}
