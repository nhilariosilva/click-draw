#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>

#include <glad/glad.h>

class Shader{
public:
  Shader(const GLchar* vertex_path, const GLchar* fragment_path);
  ~Shader();

  unsigned int getId();

  void use();
  void setInt(const std::string &name, int value);
  void setBool(const std::string &name, bool value);
  void setFloat(const std::string &name, float value);

private:
  unsigned int id;
};

#endif
