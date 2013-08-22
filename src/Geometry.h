#include <GL/glew.h>
#include <vector>
#include <memory>
#include <fstream>

struct Geometry
{
  typedef std::shared_ptr<Geometry> Ptr;
  std::vector<int> indicies;
  std::vector<float> normals;
  std::vector<float> positions;
  GLuint glBuffer = 0;
};

Geometry::Ptr createGeometryFromFile(std::string fileName);
