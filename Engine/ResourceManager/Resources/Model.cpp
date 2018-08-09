#include "Model.h"
#include "../ResourceManager.h"

Model::Model(Path &p, ResourceManager *r):Resource(p, r) {
  root = std::unique_ptr<ModelNode>(new ModelNode());
}

Model::~Model() {

}

int Model::init() {
  if (initialized) return 0;

  // Load Scene
  Assimp::Importer importer;
  const aiScene* scene = importer.ReadFile(path.getPath(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
  if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
  {
    rManager->s_MessageBus->addMessage(Message{ "MODEL", "ASSIMP FAILED TO LOAD MODEL", nullptr });
    return -1;
  }

  // Process model recursively
  processNode(scene->mRootNode, scene, root);


  initialized = true;
  return 0;
}

void Model::destroy() {

}

int Model::processNode(aiNode *node, const aiScene *scene, std::shared_ptr<ModelNode> mNode) {
  // Process nodes meshes
  for (unsigned int i = 0; i < scene->mRootNode->mNumMeshes; i++)
  {
    //std::shared_ptr<Mesh> newMesh = std::dynamic_pointer_cast<Mesh>(rManager->load("testModel", Path(Path::CWD() + "\\nanosuit\\nanosuit.obj", '/'), false));
  }
  // Process nodes children recursively (if any)
  for (unsigned int i = 0; i < node->mNumChildren; i++)
  {
    std::shared_ptr<ModelNode> newNode = std::shared_ptr<ModelNode>(new ModelNode());
    mNode->children.push_back(newNode);
    processNode(node->mChildren[i], scene, mNode->children[i]);
  }
  return 0;
}