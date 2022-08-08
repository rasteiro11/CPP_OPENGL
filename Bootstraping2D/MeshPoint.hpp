#ifndef _MESH_POINT
#define _MESH_POINT
#include "Mesh.hpp"
#include "Point.hpp"
#include "RGB.hpp"
#include "Shader.hpp"
#include <cstdio>
#include <glm/ext/vector_float3.hpp>
#include <glm/gtc/type_ptr.hpp>
class MeshPoint : public Mesh {
public:
  MeshPoint(){};
  MeshPoint(Shader &shader, RGB &color, GLfloat *vertices,
            unsigned int *indices, unsigned int numOfVertices,
            unsigned int numOfIndices) {
    CreateMesh(shader, color, vertices, indices, numOfVertices, numOfIndices);
  }
  void drawPoints() { RenderMesh(); }
  virtual void RenderMesh() {
    glUniform3fv(shader.GetUniformColorVec(), 1, &uniform_color_vec[0]);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glPointSize(5);
    glDrawElements(GL_POINTS, indexCount, GL_UNSIGNED_INT, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
  }
  ~MeshPoint() { ClearMesh(); }
};

#endif
