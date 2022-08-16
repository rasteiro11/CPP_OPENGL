#ifndef _WINDOW
#define _WINDOW

#include "Config.hpp"
#include "Dot.hpp"
#include "DrawMode.hpp"
#include "Line.hpp"
#include "Mesh.hpp"
#include "RGB.hpp"
#include "Shader.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <vector>

class Window {
  const char *glsl_version = "#version 330";

public:
  // Window() {
  //  width = 800;
  //  height = 600;

  //  for (size_t i = 0; i < 1024; i++) {
  //    keys[i] = 0;
  //  }
  //}
  Window(GLint windowWidth, GLint windowHeight) {
    width = windowWidth;
    height = windowHeight;
    drawMode = DrawMode::POINT;
    for (size_t i = 0; i < 1024; i++) {
      keys[i] = 0;
    }
  }
  int Initialize() {
    if (!glfwInit()) {
      printf("GLFW initialisation failed!");
      glfwTerminate();
      return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    mainWindow = glfwCreateWindow(width, height, "Test Window", NULL, NULL);
    if (!mainWindow) {
      printf("GLFW window creation failed!");
      glfwTerminate();
      return 1;
    }

    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

    glfwMakeContextCurrent(mainWindow);
    glfwSwapInterval(1);

    // IMGUI_CHECKVERSION();
    // ImGuiIO &io = ImGui::GetIO();
    //(void)io;

    // ImGui::StyleColorsDark();

    // ImGui_ImplGlfw_InitForOpenGL(mainWindow, true);
    // ImGui_ImplOpenGL3_Init(glsl_version);

    createCallbacks();
    //  glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK) {
      printf("GLEW initialisation failed!");
      glfwDestroyWindow(mainWindow);
      glfwTerminate();
      return 1;
    }

    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(mainWindow, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    glEnable(GL_DEPTH_TEST);

    glViewport(0, 0, bufferWidth, bufferHeight);

    glfwSetWindowUserPointer(mainWindow, this);

    return 0;
  }

  void loop() {
    bool show_demo_window = true;
    while (!getShouldClose()) {
      glUseProgram(0);

      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();

      // ImGui::Text("Hello, world %d", 123);
      // int curr_item;
      // const char *const items[] = {"TEST1", "TEST2", "TEST3"};
      // ImGui::ListBox("TESTING", &curr_item, items, 3, -1);
      selectDrawMode();
      // ImGui::InputText("string", buf, IM_ARRAYSIZE(buf));

      glfwPollEvents();

      glViewport(0, 0, bufferWidth, bufferHeight);
      glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      getShader(0).UseShader();

      //    line_1->drawLine();
      //    line_2->drawLine();
      //    line_3->drawLine();
      //    tri->drawTriangle();
      //    dot->drawDot();
      //

      ImGui::Render();

      checkForCompleteLine();
      renderAllMeshes();

      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

      swapBuffers();
    }
  }

  void pushShader(Shader &shader) { shaderList.push_back(shader); }
  void addMesh(Mesh &mesh) { meshList.push_back(&mesh); }
  void renderAllMeshes() {
    for (auto mesh : meshList) {
      mesh->RenderMesh();
    }
  }

  Shader &getShader(size_t index) { return shaderList[index]; }

  GLfloat getBufferWidth() { return bufferWidth; }
  GLfloat getBufferHeight() { return bufferHeight; }
  bool getShouldClose() { return glfwWindowShouldClose(mainWindow); }
  bool *getKeys() { return keys; }
  GLfloat getXChange() {
    GLfloat theChange = xChange;
    xChange = 0.0f;
    return theChange;
  }
  GLfloat getYChange() {
    GLfloat theChange = yChange;
    yChange = 0.0f;
    return theChange;
  }
  void swapBuffers() { glfwSwapBuffers(mainWindow); }
  ~Window() {

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(mainWindow);
    glfwTerminate();
  }

  GLFWwindow *mainWindow;

private:
  GLint width, height;
  GLint bufferWidth, bufferHeight;

  bool keys[1024];

  std::vector<Point *> tempPoints;

  GLfloat lastX;
  GLfloat lastY;
  GLfloat xChange;
  GLfloat yChange;
  bool mouseFirstMoved;

  DrawMode drawMode;

  std::vector<Mesh *> meshList;
  std::vector<Shader> shaderList;

  void createCallbacks() {
    glfwSetKeyCallback(mainWindow, handleKeys);
    glfwSetMouseButtonCallback(mainWindow, mouse_button_callback);
    glfwSetWindowSizeCallback(mainWindow, windowSizeChange);
    //   glfwSetCursorPosCallback(mainWindow, handleMouse);
  }

  void checkForCompleteLine() {

    if (tempPoints.size() >= 2) {
      std::cout << "SIZE ???" << tempPoints.size() << std::endl;
      std::cout << "FINALLY SHOULD RENDER" << std::endl;
      for (auto item : tempPoints) {
        std::cout << *item << std::endl;
      }
      addMesh(*new Line(*tempPoints[0], *tempPoints[1], *new RGB(1.0, 1.0, 0.0),
                        getShader(0)));
      tempPoints.clear();
    }
  }

  void selectDrawMode() {
    if (ImGui::Button("Point")) {
      drawMode = DrawMode::POINT;
      std::cout << "POINT MODE" << std::endl;
    }
    if (ImGui::Button("Line")) {
      drawMode = DrawMode::LINE;
      std::cout << "LINE MODE" << std::endl;
    }
  }

  static void windowSizeChange(GLFWwindow *window, int width, int height) {
    std::cout << "RESIZED" << std::endl;
    Window *theWindow = static_cast<Window *>(glfwGetWindowUserPointer(window));
    theWindow->bufferWidth = width;
    theWindow->bufferHeight = height;
    std::cout << "WIDTH: " << width << std::endl;
    std::cout << "HEIGHT: " << height << std::endl;
  }

  static void handleKeys(GLFWwindow *window, int key, int code, int action,
                         int mode) {
    Window *theWindow = static_cast<Window *>(glfwGetWindowUserPointer(window));
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
      glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if (key >= 0 && key < 1024) {
      if (action == GLFW_PRESS) {
        theWindow->keys[key] = true;
        printf("Pressed: %d\n", key);
      } else if (action == GLFW_RELEASE) {
        theWindow->keys[key] = false;
        printf("Released: %d\n", key);
      }
    }
  }
  static void mouse_button_callback(GLFWwindow *window, int button, int action,
                                    int mods) {
    Window *theWindow = static_cast<Window *>(glfwGetWindowUserPointer(window));
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
      double xPos, yPos;
      glfwGetCursorPos(window, &xPos, &yPos);
      switch (theWindow->drawMode) {
      case DrawMode::LINE:
        theWindow->tempPoints.push_back(new Point((float)xPos, (float)yPos));
      case DrawMode::POINT:;
        theWindow->addMesh(*new Dot(Point((float)xPos, (float)yPos),
                                    *new RGB(1.0, 1.0, 0.0),
                                    theWindow->getShader(0)));
      }
    }
  }

  // static void handleMouse(GLFWwindow *window, double xPos, double yPos) {
  //  Window *theWindow = static_cast<Window
  //  *>(glfwGetWindowUserPointer(window)); std::cout << "xPos: " << xPos <<
  //  std::endl; std::cout << "yPos: " << yPos << std::endl;
  //  // if (theWindow->mouseFirstMoved) {
  //  //  theWindow->lastX = xPos;
  //  //  theWindow->lastY = yPos;
  //  //  theWindow->mouseFirstMoved = false;
  //  //}
  //  // theWindow->xChange = xPos - theWindow->lastX;
  //  // theWindow->yChange = theWindow->lastY - yPos;

  //  // theWindow->lastX = xPos;
  //  // theWindow->lastY = yPos;
  //}
};
#endif
