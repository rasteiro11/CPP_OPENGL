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
#include "Point.hpp"
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

  // Buffer<unsigned int> *indices = new Buffer<unsigned int>(1000);
  // Buffer<GLfloat> *vertices = new Buffer<GLfloat>(5000);
  // vertices->push_point(*new Point(800, 600));
  // indices->push(0);
  // vertices->push_point(*new Point(800, 0));
  // indices->push(1);
  // vertices->push_point(*new Point(0, 600));
  // indices->push(2);
  // vertices->push_point(*new Point(0, 0));
  // indices->push(3);
  // vertices->push_point(*new Point(400, 300));
  // indices->push(4);

  // MeshPoint *points = new MeshPoint(
  //     *shader1, *new RGB(1.0, 0.0, 1.0), vertices->return_raw_buffer(),
  //     indices->return_raw_buffer(), vertices->get_size(),
  //     indices->get_size());
  // meshList.push_back(points);

  // Line<unsigned int, GLfloat>::renderNaiveLine(
  //    *indices, *vertices, *new Point(0, 0), *new Point(800, 600));

  // Buffer<unsigned int> *indices = new Buffer<unsigned int>(1000);
  // Buffer<GLfloat> *vertices = new Buffer<GLfloat>(5000);
  // Line<unsigned int, GLfloat>::renderNaiveLine(
  //     *indices, *vertices, *new Point(-1, 0), *new Point(1, 0));

  // MeshPoint *points = new MeshPoint(
  //     *shader1, *new RGB(1.0, 0.0, 1.0), vertices->return_raw_buffer(),
  //     indices->return_raw_buffer(), vertices->get_size(),
  //     indices->get_size());
  // meshList.push_back(points);

  // Buffer<unsigned int> *indices_2 = new Buffer<unsigned int>(1000);
  // Buffer<GLfloat> *vertices_2 = new Buffer<GLfloat>(5000);
  // Line<unsigned int, GLfloat>::renderNaiveLine(
  //     *indices_2, *vertices_2, *new Point(-0.5f, 0.0f), *new Point(0.5f,
  //     0.0f));

  // MeshPoint *points_2 = new MeshPoint(
  //     *shader1, *new RGB(0.0, 1.0, 1.0), vertices_2->return_raw_buffer(),
  //     indices_2->return_raw_buffer(), vertices_2->get_size(),
  //     indices_2->get_size());
  // meshList.push_back(points_2);

  // Buffer<unsigned int> *indices = new Buffer<unsigned int>(1000);
  // Buffer<GLfloat> *vertices = new Buffer<GLfloat>(5000);
  // Line<unsigned int, GLfloat>::renderNaiveLine(
  //    *indices, *vertices, *new Point(10, 100), *new Point(20, 400));
  //
  // MeshPoint *points = new MeshPoint(
  //    *shader1, *new RGB(1.0, 0.0, 1.0), vertices->return_raw_buffer(),
  //    indices->return_raw_buffer(), vertices->get_size(),
  //    indices->get_size());
  // meshList.push_back(points);

  //
  //  Buffer<unsigned int> *indices_3 = new Buffer<unsigned int>(1000);
  //  Buffer<GLfloat> *vertices_3 = new Buffer<GLfloat>(5000);
  //  Line<unsigned int, GLfloat>::renderNaiveLine(
  //      *indices_3, *vertices_3, *new Point(0, 300), *new Point(800, 300));
  //
  //  MeshPoint *points_3 = new MeshPoint(
  //      *shader1, *new RGB(0.0, 1.0, 1.0), vertices_3->return_raw_buffer(),
  //      indices_3->return_raw_buffer(), vertices_3->get_size(),
  //      indices_3->get_size());
  //  meshList.push_back(points_3);
  //
  //

  // INIT OF TESTING

  // Buffer<unsigned int> *indices_2 = new Buffer<unsigned int>(1000);
  // Buffer<GLfloat> *vertices_2 = new Buffer<GLfloat>(5000);
  // Line<unsigned int, GLfloat>::renderNaiveLine(
  //     *indices_2, *vertices_2, *new Point(400, 600), *new Point(400, 0));

  // MeshPoint *points_2 = new MeshPoint(
  //     *shader1, *new RGB(1.0, 0.0, 1.0), vertices_2->return_raw_buffer(),
  //     indices_2->return_raw_buffer(), vertices_2->get_size(),
  //     indices_2->get_size());
  // meshList.push_back(points_2);

  // Buffer<unsigned int> *indices_3 = new Buffer<unsigned int>(1000);
  // Buffer<GLfloat> *vertices_3 = new Buffer<GLfloat>(5000);
  // Line<unsigned int, GLfloat>::renderNaiveLine(
  //     *indices_3, *vertices_3, *new Point(0, 300), *new Point(800, 300));

  // MeshPoint *points_3 = new MeshPoint(
  //     *shader1, *new RGB(0.0, 1.0, 1.0), vertices_3->return_raw_buffer(),
  //     indices_3->return_raw_buffer(), vertices_3->get_size(),
  //     indices_3->get_size());
  // meshList.push_back(points_3);

  // Buffer<unsigned int> *indices_4 = new Buffer<unsigned int>(1000);
  // Buffer<GLfloat> *vertices_4 = new Buffer<GLfloat>(5000);
  // Line<unsigned int, GLfloat>::renderNaiveLine(
  //     *indices_4, *vertices_4, *new Point(0, 600), *new Point(400, 300));

  // MeshPoint *points_4 = new MeshPoint(
  //     *shader1, *new RGB(0.0, 1.0, 0.0), vertices_4->return_raw_buffer(),
  //     indices_4->return_raw_buffer(), vertices_4->get_size(),
  //     indices_4->get_size());
  // meshList.push_back(points_4);

  // Buffer<unsigned int> *indices_5 = new Buffer<unsigned int>(1000);
  // Buffer<GLfloat> *vertices_5 = new Buffer<GLfloat>(5000);
  // Line<unsigned int, GLfloat>::renderNaiveLine(
  //     *indices_5, *vertices_5, *new Point(795, 0), *new Point(800, 600));

  // MeshPoint *points_5 = new MeshPoint(
  //     *shader1, *new RGB(1.0, 1.0, 0.0), vertices_5->return_raw_buffer(),
  //     indices_5->return_raw_buffer(), vertices_5->get_size(),
  //     indices_5->get_size());
  // meshList.push_back(points_5);

  // vertices_5->show();

  // END OF TESTING

  // MeshPoint *points_4 = new MeshPoint(
  //    *shader1, *new RGB(0.0, 1.0, 1.0), vertices_4->return_raw_buffer(),
  //    indices_4->return_raw_buffer(), vertices_4->get_size(),
  //    indices_4->get_size());
  // meshList.push_back(points_4);

  // Buffer<unsigned int> *indices_5 = new Buffer<unsigned int>(1000);
  // Buffer<GLfloat> *vertices_5 = new Buffer<GLfloat>(1000);
  // Line<unsigned int, GLfloat>::renderNaiveLine(
  //    *indices_5, *vertices_5, *new Point(0, 0), *new Point(800, 600));

  // MeshPoint *points_5 = new MeshPoint(
  //    *shader1, *new RGB(1.0, 1.0, 0.0), vertices_5->return_raw_buffer(),
  //    indices_5->return_raw_buffer(), vertices_5->get_size(),
  //    indices_5->get_size());
  // meshList.push_back(points_5);

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

  // TESTING COORDINATES CONVERSION
  //

  //  LineTest line = new LineTest(*new Point(0, 0), *new Point(800, 600),
  //                               *new RGB(0.0, 1.0, 1.0), &shader1);

  Point *p1 = new Point(800, 600);
  Point *p2 = new Point(0, 0);

  Point *p3 = new Point(800, 0);
  Point *p4 = new Point(0, 600);
  std::cout << "(800, 600):" << *p1 << std::endl;
  std::cout << "(0, 0):" << *p2 << std::endl;
  std::cout << "(800, 0):" << *p3 << std::endl;
  std::cout << "(0, 600):" << *p4 << std::endl;
}

void CreateShaders() {
  shader1 = new Shader();
  shader1->CreateFromFiles(vShader, fShader);
  shaderList.push_back(*shader1);
}

int main() {

  mainWindow = Window();
  mainWindow.Initialize();

  CreateObjects();
  CreateShaders();

  Line *line_1 = new Line(Point(800, 600), Point(0, 0), *new RGB(0.0, 1.0, 1.0),
                          shaderList[0]);
  Line *line_2 = new Line(Point(0, 600), Point(800, 0), *new RGB(1.0, 1.0, 0.0),
                          shaderList[0]);
  Line *line_3 = new Line(Point(795, 0), Point(800, 600),
                          *new RGB(1.0, 0.0, 1.0), shaderList[0]);
  while (!mainWindow.getShouldClose()) {
    glfwPollEvents();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shaderList[0].UseShader();
    line_1->drawLine();
    line_2->drawLine();
    line_3->drawLine();

    for (auto mesh : meshList) {
      mesh->RenderMesh();
    }

    glUseProgram(0);

    mainWindow.swapBuffers();
  }
  return 0;
}
