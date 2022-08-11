#ifndef _CIRCLE
#define _CIRCLE
#include "Buffer/Buffer.hpp"
#include "MeshPoint.hpp"
#include "RGB.hpp"
#include "Shader.hpp"
#include <cmath>
class Circle : public MeshPoint {

public:
  Circle(Point center, int r, RGB &color, Shader &shader) {
    this->shader = &shader;
    this->color = &color;
    this->r = r;
    this->center = center;
    renderCircle(center, r, vertices, indices);
    CreateMesh(shader, color, vertices.return_raw_buffer(),
               indices.return_raw_buffer(), vertices.get_size(),
               indices.get_size());
  }

  static void renderCircle(Point center, int r, Buffer<GLfloat> &vertices,
                           Buffer<unsigned int> &indexes) {
    int index = indexes.get_size();
    float step = M_PI / 128;
    int x, y;
    float angle = 0;
    while (angle < 2 * M_PI) {
      x = r * std::cos(angle);
      y = r * std::sin(angle);
      indexes.push(index);
      vertices.push_point(*new Point(x + center.x, y + center.y));
      angle += step;
      index++;
    }
  }

private:
  Buffer<unsigned int> &indices = *new Buffer<unsigned int>(500);
  Buffer<GLfloat> &vertices = *new Buffer<GLfloat>(1000);
  Shader *shader;
  RGB *color;
  Point center;
  int r;
};
#endif
