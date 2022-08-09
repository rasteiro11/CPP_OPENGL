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
#include "Dot.hpp"
#include "Line.hpp"
#include "Mesh.hpp"
#include "MeshPoint.hpp"
#include "Point.hpp"
#include "RGB.hpp"
#include "Shader.hpp"
#include "Window.hpp"

const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;

// Vertex Shader code
static const char *vShader = "Shaders/shader.vert";

// Fragment Shader
static const char *fShader = "Shaders/shader.frag";

int main() {

  mainWindow = Window();
  mainWindow.Initialize();

  mainWindow.pushShader(*new Shader(vShader, fShader));

  Line *line_1 = new Line(Point(800, 600), Point(0, 0), *new RGB(0.0, 1.0, 1.0),
                          mainWindow.getShader(0));
  Line *line_2 = new Line(Point(0, 600), Point(800, 0), *new RGB(1.0, 1.0, 0.0),
                          mainWindow.getShader(0));
  Line *line_3 = new Line(Point(795, 0), Point(800, 600),
                          *new RGB(1.0, 0.0, 1.0), mainWindow.getShader(0));
  Dot *dot = new Dot(Point(400, 200), *new RGB(1.0, 0.0, 1.0),
                     mainWindow.getShader(0));

  mainWindow.addMesh(*line_1);
  mainWindow.addMesh(*line_2);
  mainWindow.addMesh(*line_3);
  mainWindow.addMesh(*dot);

  while (!mainWindow.getShouldClose()) {
    glfwPollEvents();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    mainWindow.getShader(0).UseShader();

    //    line_1->drawLine();
    //    line_2->drawLine();
    //    line_3->drawLine();
    //    dot->drawDot();

    mainWindow.renderAllMeshes();

    glUseProgram(0);

    mainWindow.swapBuffers();
  }
  return 0;
}
