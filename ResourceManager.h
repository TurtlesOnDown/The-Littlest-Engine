#include "Includes.h"

#include <memory>
#include "System.h"
#include "Resource.h"
#include "Path.h"

#ifndef RESOURCEMANAGER
#define RESOURCEMANAGER

class ResourceManager : public System {
public:
  // requires a main message bus to talk to other systems, selfclean is a feature used to auto clean the database at a set interval(Feature to be implemented)
  ResourceManager(MessageBus *mainMessage, bool selfclean = false);
  virtual void processMessage(const Message *) override;

  ~ResourceManager();

  // Returns a resource if it has been loaded, otherwises loads the resource. Determines based on file type.
  std::shared_ptr<Resource> load(Path &);

  // Clears all resources that aren't tagged by something else at the time
  void clearUnusedResources();

private:
  std::unordered_map<std::string, std::shared_ptr<Resource>> database;
  bool autoclean;
};
#endif // !RESOURCEMANAGER
