#include "Includes.h"

#include "Resource.h"

#ifndef TEXTURE
#define TEXTURE

class Texture : public Resource {
public:
  Texture(Path &p);
  ~Texture();

  virtual void load(Path &) override;
  virtual void destroy() override;
private:

};
#endif // !TEXTURE

