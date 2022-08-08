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

Shader *shader1;

// Vertex Shader code
static const char *vShader = "Shaders/shader.vert";

// Fragment Shader
static const char *fShader = "Shaders/shader.frag";

void CreateObjects() {

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

  float *test = new float[5000];

  while (!mainWindow.getShouldClose()) {
    glfwPollEvents();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shaderList[0].UseShader();

    line_1->drawLine();
    line_2->drawLine();
    line_3->drawLine();

    //    for (auto mesh : meshList) {
    //      mesh->RenderMesh();
    // }

    glUseProgram(0);

    mainWindow.swapBuffers();
  }
  return 0;
}
