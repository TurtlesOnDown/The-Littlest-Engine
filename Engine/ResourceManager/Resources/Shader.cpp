#include "Shader.h"
#include "../ResourceManager.h"

#include <fstream>
#include <sstream>

Shader::Shader(Path &p, ResourceManager *r) :Resource(p, r) {

}

Shader::~Shader() {

}

void Shader::init() {
  if (initialized) return;
  std::string lshader;
  std::ifstream lshaderFile;

  std::string vertexPath;
  std::string fragmentPath;
  
  lshaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  // Retrieve file locations for vertex and fragment shaders
  try {
    // open file
    lshaderFile.open(path.getPath());
    // get vertex path
    std::getline(lshaderFile, vertexPath);
    // get fragment path
    std::getline(lshaderFile, fragmentPath);
    // close file
    lshaderFile.close();
  }
  catch (std::ifstream::failure e)
  {
    rManager->s_MessageBus->addMessage(Message{ "SHADER", "UNABLE TO READ LSHADER", nullptr });
    return;
  }

  std::ifstream vShaderFile;
  std::ifstream fShaderFile;

  std::string vertexCode;
  std::string fragmentCode;

  vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  
  try
  {
    // open files
    vShaderFile.open(vertexPath);
    fShaderFile.open(fragmentPath);
    std::stringstream vShaderStream, fShaderStream;
    // read file's buffer contents into streams
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();
    // close file handlers
    vShaderFile.close();
    fShaderFile.close();
    // convert stream into string
    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();
  }
  catch (std::ifstream::failure e)
  {
    rManager->s_MessageBus->addMessage(Message{ "SHADER", "UNABLE TO READ VSHADER/FSHADER", nullptr });
  }

  const char* vShaderCode = vertexCode.c_str();
  const char * fShaderCode = fragmentCode.c_str();
  // 2. compile shaders
  unsigned int vertex, fragment;
  int success;
  char infoLog[512];
  // vertex shader
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vShaderCode, NULL);
  glCompileShader(vertex);
  checkCompileErrors(vertex, "VERTEX");
  // fragment Shader
  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fShaderCode, NULL);
  glCompileShader(fragment);
  checkCompileErrors(fragment, "FRAGMENT");
  // shader Program
  ID = glCreateProgram();
  glAttachShader(ID, vertex);
  glAttachShader(ID, fragment);
  glLinkProgram(ID);
  checkCompileErrors(ID, "PROGRAM");
  // delete the shaders as they're linked into our program now and no longer necessary
  glDeleteShader(vertex);
  glDeleteShader(fragment);

  initialized = true;
}

void Shader::destroy() {

}

void Shader::use() {
  glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const {
  glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const {
  glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const {
  glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}


// Private Functions

void Shader::checkCompileErrors(unsigned int shader, std::string type)
{
  int success;
  char infoLog[1024];
  if (type != "PROGRAM")
  {
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
      glGetShaderInfoLog(shader, 1024, NULL, infoLog);
      rManager->s_MessageBus->addMessage(Message{ "SHADER", "COMPILATION ERROR " + type + " : " + infoLog + "\n", nullptr });
    }
  }
  else
  {
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success)
    {
      glGetProgramInfoLog(shader, 1024, NULL, infoLog);
      rManager->s_MessageBus->addMessage(Message{ "SHADER", "LINKING ERROR " + type + " : " + infoLog + "\n", nullptr });
    }
  }
}