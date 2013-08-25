#pragma once

#include <GL/glew.h>
#include <vector>
#include <memory>
#include <fstream>

struct Geometry
{
  typedef std::shared_ptr<Geometry> Ptr;
  std::vector<int> indices;
  std::vector<float> normals;
  std::vector<float> positions;
  GLuint glVertexArray = 0;
  GLuint glIndiceBuffer = 0;
  GLuint glNormalBuffer = 0;
  GLuint glPositionBuffer = 0;
  Geometry();

  void bindGlBuffers();
};

Geometry::Ptr createGeometryFromFile(std::string fileName);

