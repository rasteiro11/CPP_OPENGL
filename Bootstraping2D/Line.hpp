#ifndef _LINE
#define _LINE
#include "Buffer/Buffer.hpp"
#include "Point.hpp"
#include <cstdio>
template <class T, class E> class Line {
public:
  constexpr static const float step = 0.001;
  static void renderNaiveLine(Buffer<T> &indices, Buffer<E> &vertices, Point p1,
                              Point p2) {
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
};
#endif
