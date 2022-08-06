#include <cmath>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>

#include "Buffer/Buffer.hpp"
#include "Line.hpp"
#include "Mesh.hpp"
#include "MeshPoint.hpp"
#include "RGB.hpp"
#include "Shader.hpp"
#include "Window.hpp"

const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;
std::vector<Mesh *> meshList;
std::vector<Shader> shaderList;
// Buffer<unsigned int> *indices;
// Buffer<GLfloat> *vertices;

Shader *shader1;

// Vertex Shader code
static const char *vShader = "Shaders/shader.vert";

// Fragment Shader
static const char *fShader = "Shaders/shader.frag";

void CreateObjects() {

  Buffer<unsigned int> *indices = new Buffer<unsigned int>(1000);
  Buffer<GLfloat> *vertices = new Buffer<GLfloat>(1000);
  Line<unsigned int, GLfloat>::renderNaiveLine(
      *indices, *vertices, Point(0.0, 0.0), Point(0.90, 0.90));

  MeshPoint *points = new MeshPoint(
      *shader1, *new RGB(1.0, 0.0, 1.0), vertices->return_raw_buffer(),
      indices->return_raw_buffer(), vertices->get_size(), indices->get_size());
  meshList.push_back(points);

  Buffer<unsigned int> *indices_2 = new Buffer<unsigned int>(1000);
  Buffer<GLfloat> *vertices_2 = new Buffer<GLfloat>(1000);
  Line<unsigned int, GLfloat>::renderNaiveLine(
      *indices_2, *vertices_2, Point(0.0, 0.0), Point(0.0, 0.90));

  MeshPoint *points_2 = new MeshPoint(
      *shader1, *new RGB(1.0, 1.0, 0.0), vertices_2->return_raw_buffer(),
      indices_2->return_raw_buffer(), vertices_2->get_size(),
      indices_2->get_size());
  meshList.push_back(points_2);

  Buffer<unsigned int> *indices_3 = new Buffer<unsigned int>(1000);
  Buffer<GLfloat> *vertices_3 = new Buffer<GLfloat>(1000);
  Line<unsigned int, GLfloat>::renderNaiveLine(
      *indices_3, *vertices_3, Point(0.0, 0.90), Point(0.90, 0.90));

  MeshPoint *points_3 = new MeshPoint(
      *shader1, *new RGB(0.0, 1.0, 1.0), vertices_3->return_raw_buffer(),
      indices_3->return_raw_buffer(), vertices_3->get_size(),
      indices_3->get_size());
  meshList.push_back(points_3);
  //
  //  Buffer<unsigned int> *indices_3 = new Buffer<unsigned int>(1000);
  //  Buffer<GLfloat> *vertices_3 = new Buffer<GLfloat>(1000);
  //  vertices_3->push_point(*new Point(-0.5, -0.5));
  //  indices_3->push(0);
  //  MeshPoint *points_3 = new MeshPoint(
  //      vertices_3->return_raw_buffer(), indices_3->return_raw_buffer(),
  //      vertices_3->get_size(), indices_3->get_size());
  //  meshList.push_back(points_3);

  // MeshPoint *obj1 = new MeshPoint();
  // obj1->CreateMesh(vertices->return_raw_buffer(),
  // indices->return_raw_buffer(),
  //                 vertices->get_size(), indices->get_size());
  // meshList.push_back(obj1);

  //  Mesh *obj1 = new Mesh();
  //  obj1->CreateMesh(vertices, indices, 6, 2);
  //  meshList.push_back(obj1);
  //
  //  Mesh *obj2 = new Mesh();
  //  obj2->CreateMesh(vertices, indices, 6, 2);
  //  meshList.push_back(obj2);

  //  Mesh *obj1 = new Mesh();
  //  obj1->CreateMesh(vertices, indices, 12, 12);
  //  meshList.push_back(obj1);
  //
  //  Mesh *obj2 = new Mesh();
  //  obj2->CreateMesh(vertices, indices, 12, 12);
  //  meshList.push_back(obj2);
}

void CreateShaders() {
  shader1 = new Shader();
  shader1->CreateFromFiles(vShader, fShader);
  shaderList.push_back(*shader1);
}

int main() {

  mainWindow = Window(400, 400);
  mainWindow.Initialize();

  CreateObjects();
  CreateShaders();

  // GLuint uniformProjection = 0, uniformModel = 0;

  // glm::mat4 projection = glm::perspective(
  //    glm::radians(45.0f),
  //    mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f,
  //    100.0f);

  while (!mainWindow.getShouldClose()) {
    glfwPollEvents();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shaderList[0].UseShader();
    //    uniformModel = shaderList[0].GetModelLocation();
    //    uniformProjection = shaderList[0].GetProjectionLocation();

    //  glm::mat4 model(1.0f);

    //  model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
    //  model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));

    //  glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    //  glUniformMatrix4fv(uniformProjection, 1, GL_FALSE,
    //                     glm::value_ptr(projection));
    meshList[0]->RenderMesh();
    meshList[1]->RenderMesh();
    meshList[2]->RenderMesh();
    //    meshList[2]->RenderMesh();

    //  model = glm::mat4(1.0f);
    //  model = glm::translate(model, glm::vec3(0.0f, 1.0f, -2.5f));
    //  model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
    // glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    // meshList[1]->RenderMesh();

    // meshList[1]->RenderMesh();

    glUseProgram(0);

    mainWindow.swapBuffers();
  }
  // printf("ALL THE POINTS\n");
  // for (int i = 0; i < vertices->get_size(); i += 3) {
  //  printf("(x: %f, y: %f)\n", vertices->return_raw_buffer()[i],
  //         vertices->return_raw_buffer()[i + 1]);
  //}
  // printf("FINAL SIZE: %zu\n", vertices->get_size());

  return 0;
}
