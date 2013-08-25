#include "Geometry.h"

#include "VertexAttrib.h"

Geometry::Geometry()
{
  glGenVertexArrays(1, &glVertexArray);
  glBindVertexArray(glVertexArray);

  glGenBuffers(1, &glIndiceBuffer);
  glGenBuffers(1, &glPositionBuffer);

  glBindVertexArray(0);
}

Geometry::Ptr createGeometryFromFile(std::string fileName)
{
  Geometry::Ptr geometry = std::make_shared<Geometry>();
  std::ifstream file(fileName, std::ifstream::binary);

  char *intBuffer = new char[sizeof(int)];
  char floatBuffer[sizeof(float)];

  file.read(intBuffer, sizeof(int));
  int numIndicies = *(int *)intBuffer;

  geometry->indices.reserve(numIndicies);
  for (int i=0; i < numIndicies; ++i) {
    file.read(intBuffer, sizeof(int));
    int ind = *(int *)intBuffer;
    geometry->indices.push_back(ind);
  }

  file.read(intBuffer, sizeof(int));
  int numVerts = *(int *)intBuffer;

  geometry->positions.reserve(numVerts * 3);
  geometry->normals.reserve(numVerts * 3);
  for (int i=0; i < numVerts; ++i) {
    file.read(floatBuffer, sizeof(float));
    float posX = *(float *)floatBuffer;
    file.read(floatBuffer, sizeof(float));
    float posY = *(float *)floatBuffer;
    file.read(floatBuffer, sizeof(float));
    float posZ = *(float *)floatBuffer;

    geometry->positions.push_back(posX);
    geometry->positions.push_back(posY);
    geometry->positions.push_back(posZ);
  }

  for (int i=0; i < numVerts; ++i) {
    file.read(floatBuffer, sizeof(float));
    float normX = *(float *)floatBuffer;
    file.read(floatBuffer, sizeof(float));
    float normY = *(float *)floatBuffer;
    file.read(floatBuffer, sizeof(float));
    float normZ = *(float *)floatBuffer;

    geometry->normals.push_back(normX);
    geometry->normals.push_back(normY);
    geometry->normals.push_back(normZ);
  }
  return geometry;
}

void bindFloatBuffer(int index, GLuint glBuffer, const std::vector<float> data)
{
  glBindBuffer(GL_ARRAY_BUFFER, glBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.size(), data.data(), GL_STATIC_DRAW);

  glEnableVertexAttribArray(VertexAttrib::iPosition);
  GLenum vertexSize = 3;
  bool isNormalized = GL_FALSE;
  GLsizei stride = 0;
  GLvoid * pointer = 0;
  glVertexAttribPointer(index, vertexSize, GL_FLOAT, isNormalized, stride, pointer);
}

void Geometry::bindGlBuffers()
{
  glBindVertexArray(glVertexArray);

  glBindBuffer(GL_ARRAY_BUFFER, glIndiceBuffer);
  size_t indicesSize = sizeof(indices[0]) * indices.size();
  glBufferData(GL_ARRAY_BUFFER, indicesSize, indices.data(), GL_STATIC_DRAW);

  bindFloatBuffer(VertexAttrib::iPosition, glPositionBuffer, positions);
  bindFloatBuffer(VertexAttrib::iNormal, glNormalBuffer, normals);

  glBindVertexArray(0);
}
