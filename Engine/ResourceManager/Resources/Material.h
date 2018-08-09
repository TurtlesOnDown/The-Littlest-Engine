#include "../../Common/Includes.h"

#include "../Resource.h"
#include "Texture2D.h"

#ifndef MATERIAL
#define MATERIAL

class Material : public Resource {
public:
  Material(Path &p, ResourceManager *r);
  ~Material();

  void init();
  virtual void destroy() override;

private:

};

#endif // !MATERIAL
