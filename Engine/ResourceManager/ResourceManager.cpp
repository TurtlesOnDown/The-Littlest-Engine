#include "ResourceManager.h"

#include "Texture.h"
#include "Misc.h"

ResourceManager::ResourceManager(MessageBus *mainMessage, bool selfClean):System(mainMessage), autoclean(selfClean) {

}

void ResourceManager::processMessage(const Message *newMessage) {
  std::vector<std::string> arguments = tokenize(newMessage->message, ':');
  switch (stringtoUintHash(arguments[0]))
  {
  case cstringToUintHash("load"): // load file
    if (arguments.size() > 1) load(Path(arguments[1], '/'));
    else s_MessageBus->addMessage(Message{ "RESOURCEMANAGER", "NO FILE SPECIFIED", nullptr });
    break;
  case cstringToUintHash("unload"): // load file
    clearUnusedResources();
    break;
  default: // command not found
    break;
  }
}

ResourceManager::~ResourceManager() {
  for (auto it = database.begin(); it != database.end(); ++it) {
    if (it->second != nullptr) {
      it->second->destroy();
      it->second = nullptr;
    }
  }
}

// change this to return a shared ptr
std::shared_ptr<Resource> ResourceManager::load(Path &filepath) {
  if (database[filepath.getPath()] != nullptr) return database[filepath.getPath()];
  else {
    switch (stringtoUintHash(filepath.getFileType())) {
    case cstringToUintHash("txt"):
      database[filepath.getPath()] = std::shared_ptr<Texture>(new Texture(filepath));
      return database[filepath.getPath()];
    default:
      s_MessageBus->addMessage(Message{ "RESOURCEMANAGER", "INVALID FILE TYPE", nullptr });
      return std::shared_ptr<Resource>(nullptr);
    }
  }
}

void ResourceManager::clearUnusedResources() {
  for (auto it = database.begin(); it != database.end(); ++it) {
    if (it->second.use_count() == 1) {
      it->second->destroy();
      it->second = nullptr;
    }
  }
  s_MessageBus->addMessage(Message{ "RESOURCEMANAGER", "UNUSED FILES UNLOADED", nullptr });
}