#include "../Common/Includes.h"

#include "Path.h"

class ResourceManager;

#ifndef RESOURCE
#define RESOURCE

class Resource {
public:
  Resource() = delete;
  Resource(Path &p, ResourceManager *r):path(p), rManager(r) {};
  // Load and destroy should be used for post load initialization
  // void init() - All Resources have a resource specific init
  // This is intentional so the user has a full understanding of what they are loading
  virtual void destroy() = 0;

protected:
  Path path;
  byte *data;
  ResourceManager *rManager;
  bool initialized = false;
};

#endif // !RESOURCE

