#include "../../Common/Includes.h"

#include "../Resource.h"

#ifndef SHADER
#define SHADER

class Shader : public Resource {
public:
  Shader(Path &p, ResourceManager *r);
  ~Shader();

  // Make sure glad has been initialized before loading any shaders.
  void init();
  virtual void destroy() override;

  void use();
  void setBool(const std::string &name, bool value) const;
  void setInt(const std::string &name, int value) const;
  void setFloat(const std::string &name, float value) const;

private:
  unsigned int ID;
  void checkCompileErrors(unsigned int shader, std::string type);
};
#endif // !SHADER