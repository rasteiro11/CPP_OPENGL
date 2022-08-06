
#ifndef _MESH_POINT
#define _MESH_POINT
#include "Mesh.hpp"
#include "Point.hpp"
#include "RGB.hpp"
#include "Shader.hpp"
#include <cstdio>
#include <glm/ext/vector_float3.hpp>
#include <glm/gtc/type_ptr.hpp>
class MeshPoint : public Mesh, private Point {
public:
  MeshPoint(){};
  MeshPoint(Shader &shader, RGB &color, GLfloat *vertices,
            unsigned int *indices, unsigned int numOfVertices,
            unsigned int numOfIndices) {
    indexCount = numOfIndices;
    uniform_color_vec[0] = color.getR();
    uniform_color_vec[1] = color.getG();
    uniform_color_vec[2] = color.getB();

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * numOfIndices,
                 indices, GL_STATIC_DRAW);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numOfVertices, vertices,
                 GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
  }
  virtual void RenderMesh() {
    // glUniform1f(shader.GetUniformColorRed(), 1.0f);
    glUniform3fv(shader.GetUniformColorVec(), 1, &uniform_color_vec[0]);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glPointSize(2);
    glDrawElements(GL_POINTS, indexCount, GL_UNSIGNED_INT, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
  }
  ~MeshPoint() { ClearMesh(); }

private:
  Shader shader;
  float uniform_color_vec[3];
};

#endif

// Mesh::Mesh() {
//  VAO = 0;
//  VBO = 0;
//  IBO = 0;
//  indexCount = 0;
//}
//
// void Mesh::CreateMesh(GLfloat *vertices, unsigned int *indices,
//                      unsigned int numOfVertices, unsigned int numOfIndices) {
//  indexCount = numOfIndices;
//
//  glGenVertexArrays(1, &VAO);
//  glBindVertexArray(VAO);
//
//  glGenBuffers(1, &IBO);
//  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
//  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * numOfIndices,
//               indices, GL_STATIC_DRAW);
//
//  glGenBuffers(1, &VBO);
//  glBindBuffer(GL_ARRAY_BUFFER, VBO);
//  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numOfVertices, vertices,
//               GL_STATIC_DRAW);
//
//  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//  glEnableVertexAttribArray(0);
//
//  glBindBuffer(GL_ARRAY_BUFFER, 0);
//  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//
//  glBindVertexArray(0);
//}
//
//// void Mesh::RenderMesh() {
////  glBindVertexArray(VAO);
////  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
////  glPointSize(5);
////  glDrawElements(GL_POINTS, indexCount, GL_UNSIGNED_INT, 0);
////  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
////  glBindVertexArray(0);
////}
//
// void Mesh::ClearMesh() {
//  if (IBO != 0) {
//    glDeleteBuffers(1, &IBO);
//    IBO = 0;
//  }
//  if (VBO != 0) {
//    glDeleteBuffers(1, &VBO);
//    VBO = 0;
//  }
//  if (VAO != 0) {
//    glDeleteVertexArrays(1, &VAO);
//    VAO = 0;
//  }
//  indexCount = 0;
//}
//
// Mesh::~Mesh() { ClearMesh(); }
