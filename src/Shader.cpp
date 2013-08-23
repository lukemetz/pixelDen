#include "Shader.h"

#include <iostream>

bool shaderDidCompile(GLint shader, std::string * message) {
  GLint shaderStatus;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderStatus);
  if (!shaderStatus) {
    GLint logSize;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
    char *logMsg = new char[logSize];
    glGetShaderInfoLog(shader, logSize, NULL, logMsg);
    message->assign(logMsg, logSize);
    delete[] logMsg;
    return false;
  }
  return true;
};

Shader::Ptr createShaderFromFile(Shader::Type type, std::string fileName)
{
  std::ifstream stream(fileName);
  std::string source((std::istreambuf_iterator<char>(stream)),
      std::istreambuf_iterator<char>());
  return createShaderFromSource(type, source);
}

Shader::Ptr createShaderFromSource(Shader::Type type, std::string source)
{
  Shader::Ptr shader = std::make_shared<Shader>();
  shader->type = type;
  if (type == Shader::Type::Vertex) {
    shader->glShader = glCreateShader(GL_VERTEX_SHADER);
  } else if(type == Shader::Type::Fragment) {
    shader->glShader = glCreateShader(GL_FRAGMENT_SHADER);
  }

  GLchar* rawSource = (GLchar *) source.c_str();
  GLsizei sourceSize = source.size();

  glShaderSource(shader->glShader, 1, (const GLchar **)&rawSource, &sourceSize);
  glCompileShader(shader->glShader);

  std::string message;
  if (!shaderDidCompile(shader->glShader, &message)) {
    std::cerr << "Failed to compile shader" << std::endl;
    std::cerr << message << std::endl;
  }
  return shader;
}
