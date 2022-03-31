#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <vector>

#include <utils.hpp>

#include <glad/glad.h>
#include <glfw3.h>

class Window{
public:
  Window(int width, int height, char *title);
  ~Window();

  void setSize(Size size);
  void setTitle(char* title);

  Size getSize();
  char* getTitle();

  void initGLFW();
  void initGLAD();
  void processInput(GLFWwindow* window);
  static void framebufferSizeCallback(GLFWwindow* window, int width, int height);

  void fetchData();
  void joinData(std::vector<Point> points, std::vector<Index> indices);
  void genData();
  void setUpData();

  void drawCircle(Point center, float rad, const char* color_option, float r, float g, float b);

  void printVertices();
  void printIndices();

  void run();

private:
  GLFWwindow* window;

  int vertices_memory_size;
  int indices_memory_size;
  std::vector<Point> vertices_vector;
  std::vector<Index> indices_vector;
  float* vertices;
  unsigned int* indices;

  unsigned int vao;
  unsigned int vbo;
  unsigned int ebo;

  int width;
  int height;
  char* title;
};

#endif
