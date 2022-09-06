#ifndef _DOT
#define _DOT
#include "Buffer/Buffer.hpp"
#include "DrawMode.hpp"
#include "MeshPoint.hpp"
#include "Point.hpp"
class Dot : public MeshPoint {
public:
  Dot(Point p, RGB &color, Shader &shader) {
    this->p = p;
    this->type = DrawMode::POINT;
    this->shader = &shader;
    this->color = &color;
    vertices.push_point(p);
    indices.push(0);
    CreateMesh(shader, color, vertices.return_raw_buffer(),
               indices.return_raw_buffer(), vertices.get_size(),
               indices.get_size());
  }

  void drawDot() { RenderMesh(); }

private:
  Point p;
  Shader *shader;
  RGB *color;
  Buffer<unsigned int> &indices = *new Buffer<unsigned int>(1);
  Buffer<GLfloat> &vertices = *new Buffer<GLfloat>(1);
};

#endif
