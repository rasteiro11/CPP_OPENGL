#ifndef _POINT
#define _POINT
#include <GL/glew.h>
#include <cstdio>
#include <iostream>
#include <ostream>
#include <string>
class Point {
public:
  static const int WIDTH = 800;
  static const int HEIGHT = 800;
  GLfloat x, y, z;
  Point() : x(0.0f), y(0.0f), z(0.0f) {}
  Point(int x, int y) : x(x), y(y), z(0.0f) {
    this->x = 2.0 * x / WIDTH - 1.0;
    this->y = 1.0 - 2.0 * y / HEIGHT;
    //   printf("x: %f, y: %f\n", this->x, this->y);
    // this->z = 0.0f;
    // this->x = (float)x / 400 - 1;
    // this->y = (float)-y / 300 + 1;
  }

  friend std::ostream &operator<<(std::ostream &os, const Point p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
  }
  Point(GLfloat x, GLfloat y) : x(x), y(y), z(0.0f) {}
};
#endif
