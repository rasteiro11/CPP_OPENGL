#ifndef _CIRCLE
#define _CIRCLE
#include "Buffer/Buffer.hpp"
#include "Collidable.hpp"
#include "DrawMode.hpp"
#include "MeshPoint.hpp"
#include "Point.hpp"
#include "RGB.hpp"
#include "Shader.hpp"
#include <cmath>
class Circle : public MeshPoint, public Collidable {

public:
  Circle(Point center, int r, RGB &color, Shader &shader) {
    this->type = DrawMode::CIRCLE;
    this->shader = &shader;
    this->color = &color;
    this->r = r;
    this->center = center;
    renderCircle(center, r, vertices, indices);
    CreateMesh(shader, color, vertices.return_raw_buffer(),
               indices.return_raw_buffer(), vertices.get_size(),
               indices.get_size());
  }

  bool hasCollided(Point p) override {
    Point p2 = Point(this->center.x + r, this->center.y + r);
    Point p1 = Point(this->center.x - r, this->center.y - r);
    std::cout << this->center << std::endl;
    std::cout << "P2" << p2 << std::endl;
    std::cout << "P1" << p1 << std::endl;
    if ((p.x > p1.x) && (p.y > p1.y)) {
      if ((p.x < p2.x) && (p.y < p2.y)) {
        std::cout << "WE ARE INSIDE CIRCLE" << std::endl;
        return true;
      }
    }
    return false;
  }
  // static void renderCircle(Point center, int r, Buffer<GLfloat> &vertices,
  //                         Buffer<unsigned int> &indexes) {
  //  int index = indexes.get_size();
  //  float step = M_PI / 128;
  //  int x, y;
  //  float angle = 0;
  //  while (angle < 2 * M_PI) {
  //    x = r * std::cos(angle);
  //    y = r * std::sin(angle);
  //    indexes.push(index);
  //    vertices.push_point(*new Point(x + center.x, y + center.y));
  //    angle += step;
  //    index++;
  //  }
  //}

  void renderCircle(Point center, int r, Buffer<GLfloat> &vertices,
                    Buffer<unsigned int> &indexes) {
    int x = 0;
    int y = r;
    int p = 1 - r;
    reflectPoints(center, x, y, vertices, indexes);
    while (x < y) {
      x++;
      if (p < 0) {
        p += 2 * x + 1;
      } else {
        y--;
        p += 2 * (x - y) + 1;
      }
      reflectPoints(center, x, y, vertices, indexes);
    }
  }

private:
  Buffer<unsigned int> &indices = *new Buffer<unsigned int>(500);
  Buffer<GLfloat> &vertices = *new Buffer<GLfloat>(1000);
  Shader *shader;
  RGB *color;
  Point center;
  int r;
  void reflectPoints(Point center, int x, int y, Buffer<GLfloat> &vertices,
                     Buffer<unsigned int> &indexes) {
    int index = indexes.get_size();
    indexes.push(index);
    vertices.push_point(*new Point(center.x + x, center.y + y));
    index++;
    indexes.push(index);
    vertices.push_point(*new Point(center.x - x, center.y + y));
    index++;
    indexes.push(index);
    vertices.push_point(*new Point(center.x + x, center.y - y));
    index++;
    indexes.push(index);
    vertices.push_point(*new Point(center.x - x, center.y - y));
    index++;
    indexes.push(index);
    vertices.push_point(*new Point(center.x + y, center.y + x));
    index++;
    indexes.push(index);
    vertices.push_point(*new Point(center.x - y, center.y + x));
    index++;
    indexes.push(index);
    vertices.push_point(*new Point(center.x + y, center.y - x));
    index++;
    indexes.push(index);
    vertices.push_point(*new Point(center.x - y, center.y - x));
    index++;
  }
};
#endif
