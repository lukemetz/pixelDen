#include "Program.h"

#include <iostream>

bool programDidLink(GLint program, std::string * message) {
  GLint programStatus;
  glGetProgramiv(program, GL_LINK_STATUS, &programStatus);
  if (!programStatus) {
    GLint logSize;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logSize);
    char *logMsg = new char[logSize];
    glGetProgramInfoLog(program, logSize, NULL, logMsg);
    message->assign(logMsg, logSize);
    delete[] logMsg;
    return false;
  }
  return true;
};


Program::Ptr createProgramWithShaders(std::vector<Shader::Ptr> shaders)
{
  Program::Ptr program = std::make_shared<Program>();
  program->glProgram = glCreateProgram();
  for (Shader::Ptr shader : shaders) {
    glAttachShader(program->glProgram, shader->glShader);
  }

  glLinkProgram(program->glProgram);
  std::string message;
  if (!programDidLink(program->glProgram, &message)) {
    std::cerr << "Program failed to link" << std::endl;
    std::cerr << message << std::endl;
  }

  return program;
}
