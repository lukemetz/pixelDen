#include "Geometry.h"

Geometry::Ptr createGeometryFromFile(std::string fileName)
{
  Geometry::Ptr geometry = std::make_shared<Geometry>();
  std::ifstream file(fileName, std::ifstream::binary);

  char *intBuffer = new char[sizeof(int)];
  char floatBuffer[sizeof(float)];

  file.read(intBuffer, sizeof(int));
  int numIndicies = *(int *)intBuffer;

  geometry->indicies.reserve(numIndicies);
  for (int i=0; i < numIndicies; ++i) {
    file.read(intBuffer, sizeof(int));
    int ind = *(int *)intBuffer;
    geometry->indicies.push_back(ind);
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
