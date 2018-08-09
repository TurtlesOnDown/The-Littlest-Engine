#include "../../Common/Includes.h"

#include "../Resource.h"

#ifndef TEXTURE2D
#define TEXTURE2D

class Texture2D : public Resource {
public:
  Texture2D(Path &p, ResourceManager *r);
  ~Texture2D();

  void init(int s = GL_MIRRORED_REPEAT, int t = GL_MIRRORED_REPEAT, int min = GL_NEAREST, int mag = GL_LINEAR);
  virtual void destroy() override;

  void bind();
  void unbind();
  void setWrappingParam(int s = GL_MIRRORED_REPEAT, int t = GL_MIRRORED_REPEAT);
  void setFilteringParam(int min = GL_NEAREST, int mag = GL_LINEAR);
  void genMipMaps();

  void activateTexure(unsigned int num);

private:
  int width, height, nrChannels;
  unsigned int texture;
};
#endif // !TEXTURE2D

