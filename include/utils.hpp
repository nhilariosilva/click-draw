#ifndef UTILS_HPP
#define UTILS_HPP

class Size{
public:
  Size(int width, int height);
  ~Size();

  void setWidth(int width);
  void setHeight(int height);
  int getWidth();
  int getHeight();

private:
  int width;
  int height;

};

class Point{
public:
  float x,y,z;
  float r, g, b;

  Point();
  Point(float x, float y, float z, bool gen_colors);
  Point(float x, float y, float z, float r, float g, float b);
  ~Point();

  void printPoint();

};

class Index{
public:
  unsigned int a,b,c;

  Index();
  Index(unsigned int a, unsigned int b, unsigned int c);
  ~Index();
};

#endif
