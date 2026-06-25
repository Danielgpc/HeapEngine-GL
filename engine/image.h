#pragma once

#include <string>
#include "window.h"
#include <stb/stb_image.h>

class ImageHandler {
public:
  unsigned int loadImage(std::string imagePath, GLenum format);
};
