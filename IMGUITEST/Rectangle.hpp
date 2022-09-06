#ifndef _RECTANGLE
#define _RECTANGLE
#include "DrawMode.hpp"
#include "Line.hpp"
#include "MeshPoint.hpp"
#include "Point.hpp"
#include "RGB.hpp"

class Rectangle : public MeshPoint {
private:
  Buffer<unsigned int> &indices = *new Buffer<unsigned int>(500);
  Buffer<GLfloat> &vertices = *new Buffer<GLfloat>(1000);

public:
  Rectangle(Point p1, Point p2, RGB &color, Shader &shader) {
    this->type = DrawMode::RECTANGLE;
    Point p3 = Point(p1.x, p2.y);
    Point p4 = Point(p2.x, p1.y);
    Line::renderNaiveLine(p1, p3, vertices, indices);
    Line::renderNaiveLine(p3, p2, vertices, indices);
    Line::renderNaiveLine(p2, p4, vertices, indices);
    Line::renderNaiveLine(p4, p1, vertices, indices);
    CreateMesh(shader, color, vertices.return_raw_buffer(),
               indices.return_raw_buffer(), vertices.get_size(),
               indices.get_size());
  }

  void drawRect() { RenderMesh(); }
};

#endif
