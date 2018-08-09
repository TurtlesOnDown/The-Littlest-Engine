#include "../../Common/Includes.h"

#include <glm/glm.hpp>

#include "../Resource.h"
#include "Material.h"

#ifndef MESH
#define MESH

struct Vertex {
  glm::vec3 position;
  glm::vec3 Normal;
  glm::vec2 uvCoords;
  glm::vec3 tangent;
  glm::vec3 bitangent;
};

class Mesh : public Resource {
public:
  Mesh(Path &p, ResourceManager *r);
  ~Mesh();

  void init();
  virtual void destroy() override;

private:

};

#endif // !MESH