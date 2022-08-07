#ifndef _LINE
#define _LINE
#include "Buffer/Buffer.hpp"
#include "Point.hpp"
#include <cstdio>
template <class T, class E> class Line {
public:
  constexpr static const float step = 0.001;
  // static void renderNaiveLine(Buffer<T> &indices, Buffer<E> &vertices, Point
  // p1,
  //                            Point p2) {
  //  int i = 0;
  //  float dx = p2.x - p1.x;
  //  float dy = p2.y - p1.y;
  //  float m, b, x, y;
  //  x = p1.x;
  //  y = p1.y;
  //  if (p1.x == p2.x) {
  //    if (p1.y > p2.y) {
  //      float temp = p1.y;
  //      p1.y = p2.y;
  //      p2.y = temp;
  //    }
  //    y = p1.y;
  //    while (y < p2.y) {
  //      y += step;
  //      indices.push(i);
  //      vertices.push_point(*new Point(x, y));
  //      i++;
  //    }
  //  } else {
  //    if (p1.x < p2.x) {
  //      Point temp = p1;
  //      p1 = temp;
  //      temp = p2;
  //    }
  //    while (x < p2.x) {
  //      y = p1.y + (dy / dx) * (x - p1.x);
  //      x += step;
  //      indices.push(i);
  //      vertices.push_point(*new Point(x, y));
  //      i++;
  //    }
  //  }
  //}
  static void renderNaiveLine(Buffer<T> &indices, Buffer<E> &vertices, Point p1,
                              Point p2) {
    int i = 0;
    float m, b, x, y;
    if (p1.x > p2.x) {
      swap(&p1.x, &p2.x);
    }
    if (p1.y > p2.y) {
      swap(&p1.y, &p2.y);
    }
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;
    m = dy / dx;
    b = p1.y - m * p1.x;
    x = p1.x;
    y = p1.y;
    if (p1.x == p2.x) {
      while (y < p2.y) {
        indices.push(i);
        vertices.push_point(*new Point(x, y));
        y += step;
        i++;
      }
    } else if (p1.y == p2.y) {
      while (x < p2.x) {
        indices.push(i);
        vertices.push_point(*new Point(x, y));
        x += step;
        i++;
      }
    } else {
      while (y < p2.y) {
        x = (y - b) / m;
        indices.push(i);
        vertices.push_point(*new Point(x, y));
        y += step;
        i++;
      }
    }
  }

private:
  static void swap(float *x1, float *x2) {
    float temp = *x1;
    *x1 = *x2;
    *x2 = temp;
  }
};
#endif
