#include "Includes.h"

#include "Path.h"

#ifndef RESOURCE
#define RESOURCE

class Resource {
public:
  Resource() = delete;
  Resource(Path &p):path(p) {};
  // Load and destroy should be used for post load initialization
  virtual void load(Path &) = 0;
  virtual void destroy() = 0;

protected:
  Path path;
  byte *data;
};

#endif // !RESOURCE

