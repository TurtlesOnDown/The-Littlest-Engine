#include "Path.h"

#if defined(_WIN32)
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

#include <stdio.h>  /* defines FILENAME_MAX */

#include <numeric>
#include "../Utility/Misc.h"

std::string Path::CWD() {
  char buff[FILENAME_MAX];
  GetCurrentDir(buff, FILENAME_MAX);
  std::string current_working_dir(buff);
  return current_working_dir;
}

Path::Path(std::string p, char delim) {
    // parse input into tokens
    while (p.size()) {
      if (p.find(delim) == std::string::npos) {
        file = p;
        p.clear();
      }
      else {
        path.push_back(p.substr(0, p.find(delim)));
        p = p.substr(p.find(delim) + 1);
      }
    }
}

Path::Path(const Path &other) {
  file = other.file;
  path = other.path;
}

Path Path::operator=(const Path &other) {
  file = other.file;
  path = other.path;
  return *this;
}

bool Path::operator==(const Path &other) {
  if (path.size() != other.path.size()) return false;
  if (file != other.file) return false;
  for (auto i = 0; i < path.size(); ++i) {
    if (path[i] != other.path[i]) return false;
  }
  return true;
}

bool Path::operator!=(const Path &other) {
  return !(*this == other);
}

std::string Path::getFile() {
  return file;
}

std::string Path::getFileType() {
  return file.substr(file.find(".")+1);
}

std::string Path::getPath() {
  if (!path.size()) return file;
  std::string result = std::accumulate(path.begin() + 1, path.end(), path[0], [](std::string a, std::string b) {return a + "/" + b; });
  result += ("/" + file);
  return result;
}

std::string Path::getDirectory() {
  std::string result = std::accumulate(path.begin() + 1, path.end(), path[0], [](std::string a, std::string b) {return a + "/" + b; });
  return result;
}