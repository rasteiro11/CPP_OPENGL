#ifndef _LINE
#define _LINE
#include "Buffer/Buffer.hpp"
#include "Point.hpp"
template <class T, class E> class Line {
public:
  static void renderNaiveLine(Buffer<T> &indices, Buffer<E> &vertices, Point p1,
                              Point p2) {
    int i = 0;
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;
    float m, b, x, y;
    x = p1.x;
    y = p1.y;
    if (p1.x == p2.x) {
      if (p1.y < p2.y) {
        Point temp = p1;
        p1 = temp;
        temp = p2;
      }
      while (y < p2.y) {
        indices.push(i);
        vertices.push_point(*new Point(x, y));
        x = p1.x + (dx / dy) * (y - p1.y);
        y += 0.0001;
        i++;
      }
    } else {
      if (p1.x < p2.x) {
        Point temp = p1;
        p1 = temp;
        temp = p2;
      }
      while (x < p2.x) {
        indices.push(i);
        vertices.push_point(*new Point(x, y));
        y = p1.y + (dy / dx) * (x - p1.x);
        x += 0.0001;
        i++;
      }
    }
  }
};
#endif
