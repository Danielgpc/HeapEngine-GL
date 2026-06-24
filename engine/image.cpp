#define STB_IMAGE_IMPLEMENTATION
#include "image.h"
#include "window.h"
#include "logger.h"

unsigned int ImageHandler::loadImage(std::string imagePath) {
  int width, height, nrChannels;
  unsigned char *data =
      stbi_load(imagePath.c_str(), &width, &height, &nrChannels, 0);
  unsigned int texture = 0;
  if (data) {
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    Logger::log(LogLevel::WARN, "Unable to load image at path: ", imagePath);
  }
  stbi_image_free(data);
  return texture;
}
