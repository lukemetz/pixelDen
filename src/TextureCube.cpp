#include "TextureCube.h"
#include "Texture.h"
#include <iostream>

TextureCube::TextureCube()
{
  glGenTextures(1, &glTexture);
  glBindTexture(GL_TEXTURE_CUBE_MAP, glTexture);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}


void TextureCube::setFile(TextureCube::CubeLocation location, std::string file)
{
  fipImage & image = images[static_cast<int>(location)];
  glBindTexture(GL_TEXTURE_CUBE_MAP, glTexture);
  std::array<GLint, 6> toGl = {{
    GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
    GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
    GL_TEXTURE_CUBE_MAP_POSITIVE_X,
    GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
    GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
    GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
  }};

  if (!image.load(file.c_str())) {
    std::cerr << "could not load" << file.c_str();
  }

  GLint glColorType = getGlColorType(image);
  GLint glBitsPerChannel = getGlBitsPerChannel(image);
  GLint glFormat = getGlFormat(image);

  GLint type = toGl[static_cast<int>(location)];
  glTexImage2D(type, 0, glColorType, image.getWidth(), image.getHeight(),
      0, glFormat, glBitsPerChannel, image.accessPixels());
}

TextureCube::Ptr createTextureCubeWithPrefix(std::string prefix, std::string extension)
{
  TextureCube::Ptr textureCube = std::make_shared<TextureCube>();
  textureCube->setFile(TextureCube::CubeLocation::Top, prefix+"+y."+extension);
  textureCube->setFile(TextureCube::CubeLocation::Bottom, prefix+"-y."+extension);
  textureCube->setFile(TextureCube::CubeLocation::Right, prefix+"+x."+extension);
  textureCube->setFile(TextureCube::CubeLocation::Left, prefix+"-x."+extension);
  textureCube->setFile(TextureCube::CubeLocation::Front, prefix+"-z."+extension);
  textureCube->setFile(TextureCube::CubeLocation::Back, prefix+"+z."+extension);
  return textureCube;
}
