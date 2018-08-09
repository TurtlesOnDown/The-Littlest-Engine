#include "ResourceManager.h"

#include "../Utility/Misc.h"

ResourceManager::ResourceManager(MessageBus *mainMessage, bool selfClean):System(mainMessage), autoclean(selfClean) {

}

void ResourceManager::processMessage(const Message *newMessage) {
  std::vector<std::string> arguments = tokenize(newMessage->message, ':');
  switch (stringtoUintHash(arguments[0]))
  {
  case cstringToUintHash("load"): // load file
    if (arguments.size() > 3) load(arguments[1], Path(arguments[2], '/'), stoi(arguments[3]));
    else s_MessageBus->addMessage(Message{ "RESOURCEMANAGER", "NO FILE SPECIFIED", nullptr });
    break;
  case cstringToUintHash("unload"): // unload unused files
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

// Potential bug of overriding contents of nameFileMap
// I.E. A non-unique is put loaded in, followed by a unique -> covering the non-unique in nameFileMap
// A non-unique gets loaded in after, now we have the file loaded 3 times
std::shared_ptr<Resource> ResourceManager::load(std::string name, Path &filepath, bool unique) {
  // If the resource name is already tied to a file path with a different name, fail and return null
  if (database[name] != nullptr && nameFileMap[filepath.getPath()].first != name) {
    s_MessageBus->addMessage(Message{ "RESOURCEMANAGER", "RESOURCE NAME IN USE", nullptr });
    return std::shared_ptr<Resource>(nullptr);
  }

  // If the name is in use return the file
  if (database[name] != nullptr) return database[name];
  // if the file has already been loaded, and both versions are not unique, use the loaded assets
  else if (!unique && nameFileMap.find(filepath.getPath()) != nameFileMap.end() && !nameFileMap[filepath.getPath()].second) {
    database[name] = database[nameFileMap[filepath.getPath()].first];
    return database[name];
  }
  // Asset has not been loaded, load it and return it
  else {
    switch (stringtoUintHash(filepath.getFileType())) {
    case cstringToUintHash("jpg"):
      database[name] = std::shared_ptr<Texture2D>(new Texture2D(filepath, this));
      nameFileMap[filepath.getPath()] = { name, unique };
      return database[name];
    case cstringToUintHash("png"):
      database[name] = std::shared_ptr<Texture2D>(new Texture2D(filepath, this));
      nameFileMap[filepath.getPath()] = { name, unique };
      return database[name];
    case cstringToUintHash("lshader"):
      database[name] = std::shared_ptr<Shader>(new Shader(filepath, this));
      nameFileMap[filepath.getPath()] = { name, unique };
      return database[name];
    case cstringToUintHash("obj"):
      database[name] = std::shared_ptr<Model>(new Model(filepath, this));
      nameFileMap[filepath.getPath()] = { name, unique };
      return database[name];
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