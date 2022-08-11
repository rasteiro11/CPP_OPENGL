#include <cmath>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <vector>

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
#include "Shader.hpp"
#include "Triangle.hpp"
#include "Window.hpp"

const float toRadians = 3.14159265f / 180.0f;
static const char *glsl_version = "#version 130";

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

  Line *line_2 = new Line(Point(-800, -600), Point(0, 0),
                          *new RGB(1.0, 1.0, 0.0), mainWindow.getShader(0));

  Line *line_3 = new Line(Point(-800, 600), Point(0, 0),
                          *new RGB(1.0, 0.0, 1.0), mainWindow.getShader(0));

  Line *line_4 = new Line(Point(800, -600), Point(0, 0),
                          *new RGB(1.0, 0.0, 1.0), mainWindow.getShader(0));

  Line *line_5 = new Line(Point(700, -600), Point(680, 600),
                          *new RGB(0.0, 1.0, 0.0), mainWindow.getShader(0));

  Line *line_6 = new Line(Point(-800, 10), Point(800, 0),
                          *new RGB(0.0, 1.0, 0.0), mainWindow.getShader(0));

  Dot *dot =
      new Dot(Point(0, 300), *new RGB(1.0, 0.0, 1.0), mainWindow.getShader(0));

  Triangle *tri =
      new Triangle(Point(0, 600), Point(-800, -400), Point(800, -400),
                   *new RGB(1.0, 1.0, 0.0), mainWindow.getShader(0));

  Circle *circle = new Circle(Point(0, 0), 200, *new RGB(1.0, 1.0, 0.0),
                              mainWindow.getShader(0));

  mainWindow.addMesh(*line_1);
  mainWindow.addMesh(*line_2);
  mainWindow.addMesh(*line_3);
  mainWindow.addMesh(*line_4);
  mainWindow.addMesh(*line_5);
  mainWindow.addMesh(*line_6);
  mainWindow.addMesh(*dot);
  mainWindow.addMesh(*tri);
  mainWindow.addMesh(*circle);

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable
  // Keyboard Controls io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; //
  // Enable Gamepad Controls

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  // ImGui::StyleColorsLight();

  // Setup Platform/Renderer backends
  ImGui_ImplGlfw_InitForOpenGL(mainWindow.mainWindow, true);
  ImGui_ImplOpenGL3_Init(glsl_version);

  bool show_demo_window = true;
  bool show_another_window = false;
  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

  while (!mainWindow.getShouldClose()) {
    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // 1. Show the big demo window (Most of the sample code is in
    // ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear
    // ImGui!).
    if (show_demo_window)
      ImGui::ShowDemoWindow(&show_demo_window);

    // 2. Show a simple window that we create ourselves. We use a Begin/End pair
    // to created a named window.
    {
      static float f = 0.0f;
      static int counter = 0;

      ImGui::Begin("Hello, world!"); // Create a window called "Hello, world!"
                                     // and append into it.

      ImGui::Text("This is some useful text."); // Display some text (you can
                                                // use a format strings too)
      ImGui::Checkbox(
          "Demo Window",
          &show_demo_window); // Edit bools storing our window open/close state
      ImGui::Checkbox("Another Window", &show_another_window);

      ImGui::SliderFloat("float", &f, 0.0f,
                         1.0f); // Edit 1 float using a slider from 0.0f to 1.0f
      ImGui::ColorEdit3(
          "clear color",
          (float *)&clear_color); // Edit 3 floats representing a color

      if (ImGui::Button("Button")) // Buttons return true when clicked (most
                                   // widgets return true when edited/activated)
        counter++;
      ImGui::SameLine();
      ImGui::Text("counter = %d", counter);

      ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                  1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
      ImGui::End();
    }

    // 3. Show another simple window.
    if (show_another_window) {
      ImGui::Begin(
          "Another Window",
          &show_another_window); // Pass a pointer to our bool variable (the
                                 // window will have a closing button that will
                                 // clear the bool when clicked)
      ImGui::Text("Hello from another window!");
      if (ImGui::Button("Close Me"))
        show_another_window = false;
      ImGui::End();
    }

    ImGui::Render();
    glViewport(0, 0, 800, 600);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    mainWindow.getShader(0).UseShader();

    //    line_1->drawLine();
    //    line_2->drawLine();
    //    line_3->drawLine();
    //    tri->drawTriangle();
    //    dot->drawDot();

    // mainWindow.renderAllMeshes();

    glUseProgram(0);

    mainWindow.swapBuffers();
  }
  return 0;
}
