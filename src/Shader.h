#pragma once

#include <GL/glew.h>
#include <vector>
#include <memory>
#include <fstream>

struct Shader
{
  enum class Type {Fragment, Vertex};
  typedef std::shared_ptr<Shader> Ptr;
  Type type;
  GLuint glShader = 0;
};

Shader::Ptr createShaderFromFile(Shader::Type type, std::string fileName);
Shader::Ptr createShaderFromSource(Shader::Type type, std::string source);
