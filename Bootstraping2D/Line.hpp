#ifndef _LINE_TEST
#define _LINE_TEST
#include "Buffer/Buffer.hpp"
#include "MeshPoint.hpp"
#include "Point.hpp"
#include "RGB.hpp"
#include "Shader.hpp"

class Line : public MeshPoint {
  static constexpr float step = 0.001;

public:
  Line(Point p1, Point p2, RGB &color, Shader &shader) {
    this->p1 = p1;
    this->p2 = p2;
    this->shader = &shader;
    this->color = &color;
    renderNaiveLine();
    CreateMesh(shader, color, vertices.return_raw_buffer(),
               indices.return_raw_buffer(), vertices.get_size(),
               indices.get_size());
  }

  ~Line() { ClearMesh(); }

  void drawLine() { RenderMesh(); }

  void renderNaiveLine() {
    int i = 0;
    float m, b, x, y;
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;
    x = p1.x;
    y = p1.y;
    if (p1.x == p2.x) {
      if (p1.y > p2.y) {
        swap(&p1.y, &p2.y);
      }
      while (y < p2.y) {
        indices.push(i);
        vertices.push_point(*new Point(x, y));
        y += step;
        i++;
      }
    } else if (p1.y == p2.y) {
      if (p1.x > p2.x) {
        swap(&p1.x, &p2.x);
      }
      while (x < p2.x) {
        indices.push(i);
        vertices.push_point(*new Point(x, y));
        x += step;
        i++;
      }
    } else {
      if (p1.y > p2.y) {
        swap(&p1.y, &p2.y);
      }
      y = p1.y;
      m = (dy / dx);
      while (y < p2.y) {
        x = p1.x + (y - p1.y) / m;
        indices.push(i);
        vertices.push_point(*new Point(x, y));
        y += step;
        i++;
      }
    }
  }

private:
  template <typename P> static void swap(P *p1, P *p2) {
    P temp = *p1;
    *p1 = *p2;
    *p2 = temp;
  }
  Point p1, p2;
  Shader *shader;
  RGB *color;
  Buffer<unsigned int> &indices = *new Buffer<unsigned int>(1000);
  Buffer<GLfloat> &vertices = *new Buffer<GLfloat>(1000);
};

#endif
