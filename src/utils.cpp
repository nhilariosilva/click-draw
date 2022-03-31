#include <utils.hpp>

#include <iostream>
#include <time.h>

Size::Size(int width, int height){
  this->width = width;
  this->height = height;
}

Size::~Size(){

}

void Size::setWidth(int width){
  this->width = width;
}

void Size::setHeight(int height){
  this->height = height;
}

int Size::getWidth(){
  return this->width;
}

int Size::getHeight(){
  return this->height;
}

Point::Point(){

}

Point::Point(float x, float y, float z, bool gen_colors){
  this->x = x;
  this->y = y;
  this->z = z;
  if(gen_colors){
    this->r = (float) rand() / (RAND_MAX);
    this->g = (float) rand() / (RAND_MAX);
    this->b = (float) rand() / (RAND_MAX);
  }else{
    this->r = 0;
    this->g = 0;
    this->b = 0;
  }
}

Point::Point(float x, float y, float z, float r, float g, float b){
  this->x = x;
  this->y = y;
  this->z = z;
  this->r = r;
  this->g = g;
  this->b = b;
}

Point::~Point(){

}

void Point::printPoint(){
  std::cout << "(" << x << ", " << y << ", " << z << ")"<< std::endl;
}

Index::Index(){

}

Index::Index(unsigned int a, unsigned int b, unsigned int c){
  this->a = a;
  this->b = b;
  this->c = c;
}

Index::~Index(){

}
