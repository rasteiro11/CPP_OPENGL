#ifndef _POLYGONAL_CHAIN
#define _POLYGONAL_CHAIN
#include "Line.hpp"
#include "MeshPoint.hpp"
#include "Point.hpp"
#include "RGB.hpp"
#include <vector>

class PolygonalChain : public MeshPoint {
protected:
  Buffer<unsigned int> &indices = *new Buffer<unsigned int>(500);
  Buffer<GLfloat> &vertices = *new Buffer<GLfloat>(1000);

public:
  PolygonalChain(std::vector<Point *> polyChain, RGB &color, Shader &shader) {
    generatePolygonalConnection(polyChain, color, shader);
    CreateMesh(shader, color, vertices.return_raw_buffer(),
               indices.return_raw_buffer(), vertices.get_size(),
               indices.get_size());
  }

  void generatePolygonalConnection(std::vector<Point *> polyChain, RGB &color,
                                   Shader &shader) {
    for (int i = 0; i < polyChain.size() - 1; i++) {
      Line::renderNaiveLine(*polyChain[i], *polyChain[i + 1], vertices,
                            indices);
    }
  }

  void drawPolygonalChain() { RenderMesh(); }
};

#endif
