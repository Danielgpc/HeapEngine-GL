#define STB_IMAGE_IMPLEMENTATION
#include "image.h"
#include "window.h"
#include "logger.h"

unsigned int ImageHandler::loadImage(std::string imagePath, GLenum format) {
  int width, height, nrChannels;
  
  // Align textures matching OpenGL vertical UV standards
  stbi_set_flip_vertically_on_load(true); 
  
  unsigned char *data = stbi_load(imagePath.c_str(), &width, &height, &nrChannels, 0);
  unsigned int texture = 0;
  
  if (data) {
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Explicit texture parameter configurations required by graphics pipeline
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Pass data array with dynamic formatting rules (GL_RGB vs GL_RGBA)
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    Logger::log(LogLevel::WARN, "Unable to load image at path: ", imagePath);
  }
  
  stbi_image_free(data);
  return texture;
}