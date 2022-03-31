#include <shader.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <glad/glad.h>

Shader::Shader(const GLchar* vertex_path, const GLchar* fragment_path){
  std::ifstream vertex_file, fragment_file;
  std::stringstream vertex_stream, fragment_stream;

  try{
    vertex_file.open(vertex_path);
    fragment_file.open(fragment_path);

    vertex_stream << vertex_file.rdbuf();
    fragment_stream << fragment_file.rdbuf();

    vertex_file.close();
    fragment_file.close();
  }catch(std::ifstream::failure e){
    std::cout << "ERROR: It was not possible to read shaders files" << std::endl;
  }

  std::string vertex_code_str = vertex_stream.str();
  std::string fragment_code_str = fragment_stream.str();

  const char* vertex_code = vertex_code_str.c_str();
  const char* fragment_code = fragment_code_str.c_str();

  unsigned int vertex, fragment;
  int success;
  char infoLog[512];

  vertex = glCreateShader(GL_VERTEX_SHADER);
  fragment = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSource(vertex, 1, &vertex_code, NULL);
  glCompileShader(vertex);
  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if(success != 1){
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

  glShaderSource(fragment, 1, &fragment_code, NULL);
  glCompileShader(fragment);
  this->id = glCreateProgram();
  glAttachShader(id, vertex);
  glAttachShader(id, fragment);
  glLinkProgram(id);
  glGetShaderiv(id, GL_LINK_STATUS, &success);
	if(success != 1){
		glGetShaderInfoLog(id, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

  glDeleteShader(vertex);
	glDeleteShader(fragment);
}

Shader::~Shader(){

}

unsigned int Shader::getId(){
  return this->id;
}

void Shader::use(){
  glUseProgram(this->id);
}

void Shader::setInt(const std::string &name, int value){
  glUniform1i(glGetUniformLocation(this->id, name.c_str()), (int)value);
}

void Shader::setBool(const std::string &name, bool value){
  glUniform1i(glGetUniformLocation(this->id, name.c_str()), (int)value);
}

void Shader::setFloat(const std::string &name, float value){
  glUniform1f(glGetUniformLocation(this->id, name.c_str()), value);
}
