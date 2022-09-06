#ifndef _POLYGON
#define _POLYGON
#include "DrawMode.hpp"
#include "Line.hpp"
#include "MeshPoint.hpp"
#include "Point.hpp"
#include "PolygonalChain.hpp"
#include "RGB.hpp"

class Polygon : public PolygonalChain {

public:
  Polygon(std::vector<Point *> polyChain, RGB &color, Shader &shader)
      : PolygonalChain(polyChain, color, shader) {
    this->type = DrawMode::POLYGON;
    generatePolygonalConnection(polyChain, color, shader);
    Line::renderNaiveLine(*polyChain[0], *polyChain[polyChain.size() - 1],
                          vertices, indices);
    CreateMesh(shader, color, vertices.return_raw_buffer(),
               indices.return_raw_buffer(), vertices.get_size(),
               indices.get_size());
  }

  void drawPolygon() { RenderMesh(); }
};

#endif
