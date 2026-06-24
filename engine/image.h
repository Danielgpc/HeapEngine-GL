#pragma once

#include <string>

#include <stb/stb_image.h>

class ImageHandler {
public:
  unsigned int loadImage(std::string imagePath);
};
