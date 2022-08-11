#ifndef _TRIANGLE
#define _TRIANGLE
#include "Line.hpp"

#include "MeshPoint.hpp"
#include "Point.hpp"
#include "RGB.hpp"

class Triangle : public MeshPoint {
private:
  Buffer<unsigned int> &indices = *new Buffer<unsigned int>(500);
  Buffer<GLfloat> &vertices = *new Buffer<GLfloat>(1000);

public:
  Triangle(Point p1, Point p2, Point p3, RGB &color, Shader &shader) {
    Line::renderNaiveLine(p1, p2, vertices, indices);
    Line::renderNaiveLine(p2, p3, vertices, indices);
    Line::renderNaiveLine(p3, p1, vertices, indices);
    CreateMesh(shader, color, vertices.return_raw_buffer(),
               indices.return_raw_buffer(), vertices.get_size(),
               indices.get_size());
  }

  void drawTriangle() { RenderMesh(); }
};

#endif
