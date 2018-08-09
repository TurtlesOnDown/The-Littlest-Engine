#include "../../Common/Includes.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../Resource.h"
#include "Mesh.h"
#include "Material.h"

#ifndef MODEL
#define MODEL

struct ModelNode {
  std::vector<unsigned int> meshIndexes;
  std::vector<std::shared_ptr<ModelNode>> children;
};

class Model : public Resource {
public:
  Model(Path &p, ResourceManager *r);
  ~Model();

  int init();
  virtual void destroy() override;

private:
  std::vector<std::shared_ptr<Mesh>> meshes;
  std::shared_ptr<ModelNode> root;

  // Returns 0 if completed successfully
  int processNode(aiNode *node, const aiScene *scene, std::shared_ptr<ModelNode> mNode);

};

#endif // !MODEL