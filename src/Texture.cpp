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
  GLint glColorType = getGlColorType(image);
  GLint glBitsPerChannel = getGlBitsPerChannel(image);
  GLint glFormat= getGlFormat(image);

  glTexImage2D(GL_TEXTURE_2D, 0, glColorType, image.getWidth(), image.getHeight(),
      0, glFormat, glBitsPerChannel, image.accessPixels());
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

GLint getGlColorType(fipImage image)
{
  FREE_IMAGE_COLOR_TYPE type = image.getColorType();
  GLuint glColorType = 0;
  if (type == FREE_IMAGE_COLOR_TYPE::FIC_RGBALPHA) {
    glColorType = GL_RGBA;
  } else if (type == FREE_IMAGE_COLOR_TYPE::FIC_RGB) {
    glColorType = GL_RGB;
  } else {
    std::cerr << "unsupported color type: " << type <<  std::endl;
  }
  return glColorType;
}

GLint getGlBitsPerChannel(fipImage image)
{
  GLuint glBitsPerChannel = 0;
  unsigned int bitsPerPixel= image.getBitsPerPixel();
  if ((bitsPerPixel == 32 && image.getColorType() == FREE_IMAGE_COLOR_TYPE::FIC_RGBALPHA) ||
      (bitsPerPixel == 24 && image.getColorType() == FREE_IMAGE_COLOR_TYPE::FIC_RGB)) {
    glBitsPerChannel = GL_UNSIGNED_BYTE;
  } else {
    std::cerr << image.getColorType() << " RGBA" << FREE_IMAGE_COLOR_TYPE::FIC_RGBALPHA << " " << FREE_IMAGE_COLOR_TYPE::FIC_RGB<< std::endl;
    std::cerr << "unsupported bits per channel" << std::endl;
    std::cerr << "Found bits per pixel: " << bitsPerPixel << std::endl;
  }
  glBitsPerChannel = GL_UNSIGNED_BYTE;
  return glBitsPerChannel;
}

GLint getGlFormat(fipImage image)
{
  unsigned int bitsPerPixel = image.getBitsPerPixel();
  unsigned int channels = 0;
  if (image.getColorType() == FREE_IMAGE_COLOR_TYPE::FIC_RGB) {
    channels = 3;
  } else if (image.getColorType() == FREE_IMAGE_COLOR_TYPE::FIC_RGBALPHA) {
    channels = 4;
  }
  if (bitsPerPixel == 32 && channels == 3) {
    return GL_RGBA;
  }
  return GL_RGB;
}

Texture::Ptr createTextureFromFile(std::string file)
{
  Texture::Ptr texture = std::make_shared<Texture>();
  texture->setFile(file);
  return texture;
}
