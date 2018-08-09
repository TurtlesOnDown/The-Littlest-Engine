#include "../Common/Includes.h"

#include <utility>

#include "../System/System.h"
#include "Resource.h"
#include "Resources/Texture2D.h"
#include "Resources/Shader.h"
#include "Resources\Model.h"
#include "Path.h"

#ifndef RESOURCEMANAGER
#define RESOURCEMANAGER

class ResourceManager : public System {
public:
  // requires a main message bus to talk to other systems, selfclean is a feature used to auto clean the database at a set interval(Feature to be implemented)
  ResourceManager(MessageBus *mainMessage, bool selfclean = false);
  virtual void processMessage(const Message *) override;

  ~ResourceManager();

  // name: unique name of resource
  // filepath: filepath to load resource from
  // unique: if true, a unique copy of the resource will be loaded in, otherwise uses already loaded assets (if it can find them)
  // Returns a resource if it has been loaded, otherwises loads the resource. Determines based on file type.
  std::shared_ptr<Resource> load(std::string name, Path &filepath, bool unique);

  // Clears all resources that aren't tagged by something else at the time
  void clearUnusedResources();

private:
  std::unordered_map<std::string, std::shared_ptr<Resource>> database;
  std::unordered_map<std::string, std::pair<std::string, bool>> nameFileMap;
  bool autoclean;
};
#endif // !RESOURCEMANAGER
