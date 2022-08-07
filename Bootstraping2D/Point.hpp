#ifndef _POINT
#define _POINT
#include <GL/glew.h>
class Point {
public:
  GLfloat x, y, z;
  Point() : x(0.0f), y(0.0f), z(0.0f) {}
  Point(int x, int y) {
    this->x = (float)x / 400 - 1;
    this->y = (float)-y / 300 + 1;
    this->z = 0.0f;
  }
  Point(GLfloat x, GLfloat y) : x(x), y(y), z(0.0f) {}
};
#endif
