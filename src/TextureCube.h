#pragma once
#include <GL/glew.h>
#include <memory>
#include <array>

#include <FreeImagePlus.h>

struct TextureCube
{
  typedef std::shared_ptr<TextureCube> Ptr;
  enum class CubeLocation
  {
    Top = 0,
    Bottom = 1,
    Right = 2,
    Left = 3,
    Front = 4,
    Back = 5
  };

  TextureCube();
  void setFile(CubeLocation location, std::string file);

  std::array<fipImage, 6> images;
  GLuint glTexture;
};

TextureCube::Ptr createTextureCubeWithPrefix(std::string prefix, std::string extension);
