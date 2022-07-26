#ifndef _WINDOW
#define _WINDOW
#include "Config.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <vector>

class Window {
public:
  Window() {
    width = 800;
    height = 600;

    for (size_t i = 0; i < 1024; i++) {
      keys[i] = 0;
    }
  }
  Window(GLint windowWidth, GLint windowHeight) {
    width = windowWidth;
    height = windowHeight;
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

    createCallbacks();
    //  glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK) {
      printf("GLEW initialisation failed!");
      glfwDestroyWindow(mainWindow);
      glfwTerminate();
      return 1;
    }

    glEnable(GL_DEPTH_TEST);

    glViewport(0, 0, bufferWidth, bufferHeight);

    glfwSetWindowUserPointer(mainWindow, this);

    return 0;
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
    glfwDestroyWindow(mainWindow);
    glfwTerminate();
  }

private:
  GLFWwindow *mainWindow;
  GLint width, height;
  GLint bufferWidth, bufferHeight;

  bool keys[1024];

  GLfloat lastX;
  GLfloat lastY;
  GLfloat xChange;
  GLfloat yChange;
  bool mouseFirstMoved;

  std::vector<Mesh *> meshList;
  std::vector<Shader> shaderList;

  void createCallbacks() {
    glfwSetKeyCallback(mainWindow, handleKeys);
    glfwSetCursorPosCallback(mainWindow, handleMouse);
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
  static void handleMouse(GLFWwindow *window, double xPos, double yPos) {
    Window *theWindow = static_cast<Window *>(glfwGetWindowUserPointer(window));
    if (theWindow->mouseFirstMoved) {
      theWindow->lastX = xPos;
      theWindow->lastY = yPos;
      theWindow->mouseFirstMoved = false;
    }
    theWindow->xChange = xPos - theWindow->lastX;
    theWindow->yChange = theWindow->lastY - yPos;

    theWindow->lastX = xPos;
    theWindow->lastY = yPos;
  }
};
#endif
