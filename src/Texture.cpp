#include "Texture.h"
#include <iostream>

Texture::Texture()
{
  glGenTextures(1, &glTexture);
}

void Texture::setFile(std::string file)
{
  glBindTexture(GL_TEXTURE_2D, glTexture);
  bool loaded = image.load(file.c_str());
  if (!loaded || !image.isValid()) {
    std::cerr << "could not load " << file << std::endl;
  }
  FREE_IMAGE_COLOR_TYPE type = image.getColorType();
  GLuint glColorType = 0;
  if (type == FREE_IMAGE_COLOR_TYPE::FIC_RGBALPHA) {
    glColorType = GL_RGBA;
  } else if (type == FREE_IMAGE_COLOR_TYPE::FIC_RGB) {
    glColorType = GL_RGB;
  } else {
    std::cerr << "unsupported color type: " << type <<  std::endl;
  }

  GLuint glBitsPerChannel = 0;
  unsigned int bitsPerPixel= image.getBitsPerPixel();
  if ((bitsPerPixel == 32 && glColorType == GL_RGBA) ||
      (bitsPerPixel == 24 && glColorType == GL_RGB)) {
    glBitsPerChannel = GL_UNSIGNED_BYTE;
  } else {
    std::cerr << "unsupported bits per channel" << std::endl;
    std::cerr << "Found bits per pixel: " << bitsPerPixel << std::endl;
  }

  glTexImage2D(GL_TEXTURE_2D, 0, glColorType, image.getWidth(), image.getHeight(),
      0, glColorType, glBitsPerChannel, image.accessPixels());
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Texture::Ptr createTextureFromFile(std::string file)
{
  Texture::Ptr texture = std::make_shared<Texture>();
  texture->setFile(file);
  return texture;
}
