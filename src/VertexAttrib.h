#pragma once

#include "Program.h"

#include <map>
#include <string>

struct VertexAttrib {
  const static int iPosition = 0;
  const static int iNormal = 1;
};

inline void setupVertexAttrib(Program::Ptr program)
{
  glBindAttribLocation(program->glProgram, VertexAttrib::iPosition, "iPosition");
  glBindAttribLocation(program->glProgram, VertexAttrib::iNormal, "iNormal");
}
