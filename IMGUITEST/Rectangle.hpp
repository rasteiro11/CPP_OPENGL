#ifndef _RECTANGLE
#define _RECTANGLE
#include "Collidable.hpp"
#include "DrawMode.hpp"
#include "Line.hpp"
#include "MeshPoint.hpp"
#include "Point.hpp"
#include "RGB.hpp"

class Rectangle : public MeshPoint, public Collidable {
private:
  Buffer<unsigned int> &indices = *new Buffer<unsigned int>(500);
  Buffer<GLfloat> &vertices = *new Buffer<GLfloat>(1000);
  Point p1, p2, p3, p4;

public:
  bool hasCollided(Point p) override {
    if ((p.x > p1.x) && (p.y < p1.y)) {
      if ((p.x < p2.x) && (p.y > p2.y)) {
        std::cout << "WE ARE INSIDE RECTANGLE" << std::endl;
        return true;
      }
    }
    return false;
  }

  Rectangle(Point p1, Point p2, RGB &color, Shader &shader) {
    this->type = DrawMode::RECTANGLE;
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = Point(p1.x, p2.y);
    this->p4 = Point(p2.x, p1.y);
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
