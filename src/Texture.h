#pragma once

#include <GL/glew.h>
#include <memory>

#include <FreeImagePlus.h>

struct Texture
{
  Texture();
  void setFile(std::string file);

  typedef std::shared_ptr<Texture> Ptr;
  fipImage image;
  GLuint glTexture;
};

Texture::Ptr createTextureFromFile(std::string file);
