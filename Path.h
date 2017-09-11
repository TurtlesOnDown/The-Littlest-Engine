#include "Includes.h"

#ifndef PATH
#define PATH

class Path {
public:
  Path(std::string , char);
  Path(const Path &);
  Path operator=(const Path &);

  bool operator==(const Path &);
  bool operator!=(const Path &);

  std::string getFile();
  std::string getFileType();
  std::string getPath();
  // not implemented yet
  void cd(const std::string &);
private:
  std::vector<std::string> path;
  std::string file;
};
#endif // !PATH
