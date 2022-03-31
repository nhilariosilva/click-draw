#include <window.hpp>

#include <iostream>
#include <cmath>
#include <vector>

#include <glad/glad.h>
#include <glfw3.h>

#include <utils.hpp>
#include <shader.hpp>

bool mouse_button_left_pressed = false;
bool mouse_button_right_pressed = false;

const char* circle_parameter = "RANDOM";

Window::Window(int width, int height, char* title){
  this->width = width;
  this->height = height;
  this->title = title;

  this->initGLFW();

  this->window = glfwCreateWindow(width, height, title, NULL, NULL);
  if(window == NULL){
    std::cout << "Failed to create GLFW Window." << std::endl;
    glfwTerminate();

    this->~Window();
  }
}

Window::~Window(){

}

void Window::framebufferSizeCallback(GLFWwindow* window, int width, int height){
	glViewport(0, 0, width, height);
}

void Window::processInput(GLFWwindow* window){
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
		glfwSetWindowShouldClose(window, true);
  }
  if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
    mouse_button_left_pressed = true;
  }
  if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS){
    mouse_button_right_pressed = true;
  }
  if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE){
    if(mouse_button_left_pressed){

      double xpos, ypos;
      float rad = (float) rand() / (RAND_MAX) * 0.3;
      glfwGetCursorPos(window, &xpos, &ypos);
      // 1 SEMESTRE DE G.A. PRA FICAR BUGADO NESSA MERDA POR TODO ESSE TEMPO??? TNC
      xpos /= this->width;
      ypos /= -this->height;
      xpos = 2*xpos - 1;
      ypos = 2*ypos + 1;
      std::cout << "(" << xpos << ", " << ypos << ")" << std::endl;
      this->drawCircle( Point(xpos, ypos, 0.0, false), rad, circle_parameter, 0.0, 0.0, 0.0 );
      this->fetchData();

      glBufferData(GL_ARRAY_BUFFER, this->vertices_memory_size, vertices, GL_STATIC_DRAW);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices_memory_size, indices, GL_STATIC_DRAW);

      mouse_button_left_pressed = false;
    }
  }

  if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE){
    if(mouse_button_right_pressed){

      if(circle_parameter == "RANDOM"){
        circle_parameter = "MULTICOLORED";
      }else if(circle_parameter == "MULTICOLORED"){
        circle_parameter = "RANDOM";
      }

      mouse_button_right_pressed = false;
    }
  }

}

void Window::setSize(Size size){
  this->width = size.getWidth();
  this->height = size.getHeight();

  framebufferSizeCallback(window, width, height);
}

void Window::setTitle(char* title){
  this->title = title;

  glfwSetWindowTitle(window, title);
}

void Window::initGLFW(){
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Window::initGLAD(){
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
 		std::cout << "Failed to initialize GLAD" << std::endl;
		this->~Window();
	}
}

void Window::printVertices(){
  for (int i = 0; i < this->vertices_memory_size/sizeof(float); i++){
    if(i % 6 == 0 && i != 0){
      std::cout << std::endl;
    }
    std::cout << vertices[i] << " ";
  }
  std::cout << std::endl;
}

void Window::printIndices(){
  for (int i = 0; i < this->indices_memory_size/sizeof(unsigned int); i++){
    if(i % 3 == 0 && i != 0){
      std::cout << std::endl;
    }
    std::cout << indices[i] << " ";
  }
  std::cout << std::endl;
}

void Window::joinData(std::vector<Point> points, std::vector<Index> indices){
  // Joins specific parts of data to the whole group of vertices
  // and indices to be drawn (vectors)

  // The data sent to this function have to be previosly syncronized
  // so the vertices will keep their related indices
  for (int i = 0; i < points.size(); i++){
    this->vertices_vector.push_back(points[i]);
  }
  for (int i = 0; i < indices.size(); i++){
    this->indices_vector.push_back(indices[i]);
  }

  //std::cout << "Joined everything" << std::endl;
}

void Window::fetchData(){
  // Passes all the vertices and indices data from vector to the OpenGL usable arrays
  vertices_memory_size = this->vertices_vector.size() * 6 * sizeof(float);
  indices_memory_size = this->indices_vector.size() * 3 * sizeof(unsigned int);

  this->vertices = (float*) malloc(vertices_memory_size);
  this->indices = (unsigned int*) malloc(indices_memory_size);

  int i = 0;
  int j = 0;
  Point point;
  for (int i = 0; i < vertices_vector.size(); i++){
    point = vertices_vector[i];
    vertices[j] = point.x;
    vertices[j+1] = point.y;
    vertices[j+2] = point.z;
    vertices[j+3] = point.r;
    vertices[j+4] = point.g;
    vertices[j+5] = point.b;
    j += 6;
  }

  Index index;
  j = 0;
  for (int i = 0; i < indices_vector.size(); i++){
    index = indices_vector[i];
    indices[j] = index.a;
    indices[j+1] = index.b;
    indices[j+2] = index.c;
    j += 3;
  }

  //std::cout << "All the data has been fetched." << std::endl;
  //std::cout << "Total of: " << vertices_vector.size() << " vertices (points)" << std::endl;
}

void Window::drawCircle(Point center, float rad, const char* color_option, float r, float g, float b){
  int num_points = 0;
  float t = 0, inc = 0.1;
  Point point;
  std::vector<Point> points;
  std::vector<Index> indices;

  // We take the number of vertices because they are the ones that are named in the indices
  unsigned int last_index_pos = this->vertices_vector.size();

  if(color_option == "RANDOM"){
    r = (float) rand() / (RAND_MAX);
    g = (float) rand() / (RAND_MAX);
    b = (float) rand() / (RAND_MAX);
    center.r = r;
    center.g = g;
    center.b = b;
  }

  points.push_back(center);
  while(t <= 2 * M_PI){
    if(color_option == "MULTICOLORED"){
      point = Point(rad*cos(t) + center.x, rad*sin(t) + center.y, 0 + center.z, true);
    }else{
      // The code for Solid color would be "SOLID" but there is no need for it here
      point = Point(rad*cos(t) + center.x, rad*sin(t) + center.y, 0 + center.z, r, g, b);
    }

    points.push_back( point );
    t += inc;
  }
  num_points = points.size();

  Index index;
  for (int i = last_index_pos+1; i < last_index_pos + num_points; i++){
    index.a = last_index_pos;
    index.b = i;
    index.c = i+1;
    if(index.c == last_index_pos + num_points)
      index.c = last_index_pos+1;

    indices.push_back(index);
  }

  joinData(points, indices);
}

void Window::genData(){
  //drawCircle(Point(-0.25, 0.75, 0.0, false), 0.15, "MULTICOLORED", 0.0, 0.0, 0.0);
  //drawCircle(Point(0.0, -0.3, 0.0, false), 0.45, "RANDOM", 0.0, 0.0, 0.0);
  //drawCircle(Point(0.8, 0.7, 0.0, 0.65, 0.1, 0.1), 0.5, "SOLID", 0.65, 0.1, 0.1);

  fetchData();
}

void Window::setUpData(){
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);

  glBindVertexArray(vao);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, this->vertices_memory_size, vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices_memory_size, indices, GL_STATIC_DRAW);

  // Position
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(0);
  // Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void Window::run(){
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

  initGLAD();

  Shader shader = Shader("shaders/vertex_shader", "shaders/fragment_shader");

  srand ( time(NULL) );

  genData();
  setUpData();

  while(!glfwWindowShouldClose(window)){
    processInput(window);

    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shader.use();

    //glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, this->indices_memory_size/sizeof(unsigned int), GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

}
