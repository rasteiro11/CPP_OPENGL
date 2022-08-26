#ifndef _LINE_TEST
#define _LINE_TEST
#include "Buffer/Buffer.hpp"
#include "MeshPoint.hpp"
#include "Point.hpp"
#include "RGB.hpp"
#include "Shader.hpp"

class Line : public MeshPoint {
  // static constexpr float step = 0.001;

public:
  Line() {}
  Line(Point p1, Point p2, RGB &color, Shader &shader) {
    this->p1 = p1;
    this->p2 = p2;
    this->shader = &shader;
    this->color = &color;
    renderNaiveLine(p1, p2, this->vertices, this->indices);
    CreateMesh(shader, color, vertices.return_raw_buffer(),
               indices.return_raw_buffer(), vertices.get_size(),
               indices.get_size());
  }

  ~Line() { ClearMesh(); }

  void drawLine() { RenderMesh(); }

  static void renderNaiveLine(Point point1, Point point2,
                              Buffer<GLfloat> &vertices,
                              Buffer<unsigned int> &indexes) {
    float dy = (point2.y - point1.y);
    float dx = (point2.x - point1.x);
    float step = (std::abs(dx) >= std::abs(dy)) ? std::abs(dx) : std::abs(dy);
    dx /= step;
    dy /= step;
    int index = indexes.get_size();
    int i = 1;
    float x = point1.x;
    float y = point1.y;
    while (i <= step) {
      indexes.push(index);
      vertices.push_point(*new Point(x, y));
      x += dx;
      y += dy;
      index++;
      i++;
    }
  }

  //  static void renderNaiveLine(Point point1, Point point2,
  //                              Buffer<GLfloat> &vertices,
  //                              Buffer<unsigned int> &indexes) {
  //    std::cout << point1 << std::endl;
  //    std::cout << point2 << std::endl;
  //    float dy = (point2.y - point1.y) * 600;
  //    float dx = (point2.x - point1.x) * 800;
  //    float m = dy / dx;
  //    float step = (std::abs(dx) >= std::abs(dy)) ? std::abs(dx) :
  //    std::abs(dy); dx /= step; dy /= step; int index = indexes.get_size();
  //    int i = 1;
  //    float x = point1.x * 800;
  //    float y = point1.y * 600;
  //    while (i <= step) {
  //      indexes.push(index);
  //      vertices.push_point(*new Point((int)x, (int)y));
  //      x += dx;
  //      y += dy;
  //      index++;
  //      i++;
  //    }
  //  }

  // static void renderNaiveLine(Point point1, Point point2,
  //                            Buffer<GLfloat> &vertices,
  //                            Buffer<unsigned int> &indexes) {
  //  float m = (point2.y - point1.y) / (point2.x - point1.x);
  //  float c = point1.y - m * point1.x;
  //  float x, y;
  //  x = point1.x;
  //  y = point1.y;
  //  int index = indexes.get_size();
  //  if (std::abs(m) < 1) {
  //    while (x <= point2.x) {
  //      x += step;
  //      y = m * x + c;
  //      indexes.push(index);
  //      vertices.push_point(*new Point(x, y));
  //      index++;
  //    }
  //  } else {
  //    while (y <= point2.y) {
  //      y += step;
  //      x = (y - c) / m;
  //      indexes.push(index);
  //      vertices.push_point(*new Point(x, y));
  //      index++;
  //    }
  //  }
  //}

  // static void renderNaiveLine_2(Point p1, Point p2, Buffer<GLfloat>
  // &vertices,
  //                              Buffer<unsigned int> &indexes) {
  //  int i = indexes.get_size();
  //  float m, b, x, y;
  //  float dx = p2.x - p1.x;
  //  float dy = p2.y - p1.y;
  //  x = p1.x;
  //  y = p1.y;
  //  if (p1.x == p2.x) {
  //    if (p1.y > p2.y) {
  //      swap(&p1.y, &p2.y);
  //    }
  //    while (y < p2.y) {
  //      indexes.push(i);
  //      vertices.push_point(*new Point(x, y));
  //      y += step;
  //      i++;
  //    }
  //  } else if (p1.y == p2.y) {
  //    if (p1.x > p2.x) {
  //      swap(&p1.x, &p2.x);
  //    }
  //    while (x < p2.x) {
  //      indexes.push(i);
  //      vertices.push_point(*new Point(x, y));
  //      x += step;
  //      i++;
  //    }
  //  } else {
  //    if (p1.y > p2.y) {
  //      swap(&p1.y, &p2.y);
  //    }
  //    y = p1.y;
  //    m = (dy / dx);
  //    while (y < p2.y) {
  //      x = p1.x + (y - p1.y) / m;
  //      indexes.push(i);
  //      vertices.push_point(*new Point(x, y));
  //      y += step;
  //      i++;
  //    }
  //  }
  //}

private:
  template <typename P> static void swap(P *p1, P *p2) {
    P temp = *p1;
    *p1 = *p2;
    *p2 = temp;
  }
  Point p1, p2;
  Shader *shader;
  RGB *color;
  Buffer<unsigned int> &indices = *new Buffer<unsigned int>(500);
  Buffer<GLfloat> &vertices = *new Buffer<GLfloat>(1000);
};

#endif
