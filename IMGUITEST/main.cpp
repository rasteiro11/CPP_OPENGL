#include <cmath>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <vector>

#include "Config.hpp"
#include "DrawMode.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>

#include "Buffer/Buffer.hpp"
#include "Circle.hpp"
#include "Dot.hpp"
#include "Line.hpp"
#include "Mesh.hpp"
#include "MeshPoint.hpp"
#include "Point.hpp"
#include "RGB.hpp"
#include "Rectangle.hpp"
#include "Shader.hpp"
#include "Triangle.hpp"
#include "Window.hpp"

const float toRadians = 3.14159265f / 180.0f;

// Vertex Shader code
static const char *vShader = "Shaders/shader.vert";

// Fragment Shader
static const char *fShader = "Shaders/shader.frag";

int main() {

  Window mainWindow = Window(Config::WIDTH, Config::HEIGHT);
  mainWindow.Initialize();

  mainWindow.pushShader(*new Shader(vShader, fShader));

  int width, height;
  glfwGetWindowSize(mainWindow.mainWindow, &width, &height);

  // Line *line_1 = new Line(Point(width, height), Point(0, 0),
  //                        *new RGB(0.0, 1.0, 1.0), mainWindow.getShader(0));

  // Line *line_2 = new Line(Point(width / 2, 0), Point(width / 2, height),
  //                        *new RGB(1.0, 1.0, 0.0), mainWindow.getShader(0));

  // Triangle *tri = new Triangle(Point(width / 2, 0), Point(width, height / 2),
  //                             Point(0, height / 2), *new RGB(1.0, 1.0, 0.0),
  //                             mainWindow.getShader(0));

  // Rectangle *rect =
  //    new Rectangle(Point(50, height / 2 - 50), Point(width / 2 - 50, 50),
  //                  *new RGB(1.0, 0.0, 1.0), mainWindow.getShader(0));

  // imgui slider to change circle drawing size

  //  mainWindow.addMesh(*line_1);
  //  mainWindow.addMesh(*line_2);
  //  mainWindow.addMesh(*tri);
  //  mainWindow.addMesh(*rect);
  mainWindow.loop();

  return 0;
}
