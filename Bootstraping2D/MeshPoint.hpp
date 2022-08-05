
#ifndef _MESH_POINT
#define _MESH_POINT
#include "Mesh.hpp"
#include "Point.hpp"
class MeshPoint : public Mesh, private Point {
public:
  MeshPoint(){};
  MeshPoint(GLfloat *vertices, unsigned int *indices,
            unsigned int numOfVertices, unsigned int numOfIndices) {
    indexCount = numOfIndices;

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
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glPointSize(2);
    glDrawElements(GL_POINTS, indexCount, GL_UNSIGNED_INT, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
  }
  ~MeshPoint() { ClearMesh(); }
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
