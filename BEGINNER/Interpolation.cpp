#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <string.h>

const GLint WIDTH = 800, HEIGHT = 600;
const float toRadians = 3.141592651 / 180;

GLuint VAO, VBO, IBO, shader, uniformModel;

bool direction = true;
float triOffset = 0.0f;
float triMaxOffset = 0.7f;
float triIncrement = 0.005f;

float curAngle = 0.0f;

bool sizeDirection = true;
float curSize = 0.4f;
float maxSize = 0.8f;
float minSize = 0.1f;

// Vertex Shader
static const char *vShader = "#version 330\n"
                             "layout (location = 0) in vec3 pos;\n"
                             "out vec4 vCol;\n"
                             "uniform mat4 model;\n"
                             "void main() \n"
                             "{\n"
                             "gl_Position = model*vec4(pos, 1.0);\n"
                             "vCol = vec4(clamp(pos, 0.0f, 1.0f), 1.0f);\n"
                             "}\n";

// Fragment Shader
static const char *fShader = "#version 330\n"
                             "in vec4 vCol;\n"
                             "out vec4 color; \n"
                             "void main() \n"
                             "{\n"
                             "color = vCol;\n"
                             "}\n";

void AddShader(GLuint theProgram, const char *shaderCode, GLenum shaderType) {
  GLuint theShader = glCreateShader(shaderType);

  const GLchar *theCode[1];
  theCode[0] = shaderCode;

  GLint codeLength[1];
  codeLength[0] = strlen(shaderCode);

  glShaderSource(theShader, 1, theCode, codeLength);
  glCompileShader(theShader);

  GLint result = 0;
  GLchar eLog[1024] = {0};

  glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
  if (!result) {
    glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
    std::cout << "Error compiling the " << shaderType << " shader: " << eLog
              << std::endl;
    return;
  }

  glAttachShader(theProgram, theShader);
}

void CompileShaders() {
  shader = glCreateProgram();
  if (!shader) {
    std::cout << "Error Creating Shader Program" << std::endl;
    return;
  }
  AddShader(shader, vShader, GL_VERTEX_SHADER);
  AddShader(shader, fShader, GL_FRAGMENT_SHADER);

  GLint result = 0;
  GLchar eLog[1024] = {0};

  glLinkProgram(shader);
  glGetProgramiv(shader, GL_LINK_STATUS, &result);
  if (!result) {
    glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
    std::cout << "Error linking programm" << std::endl;
    return;
  }

  glValidateProgram(shader);
  glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
  if (!result) {
    glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
    std::cout << "Error validating programm" << std::endl;
    return;
  }

  uniformModel = glGetUniformLocation(shader, "model");
}

void CreateTriangle() {

  unsigned int indices[] = {
      0, 3, 1, 1, 3, 2, 2, 3, 0, 0, 1, 2,
  };

  GLfloat vertices[] = {-1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f,
                        1.0f,  -1.0f, 0.0f, 0.0f, 1.0f,  0.0f};

  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  glGenBuffers(1, &IBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

int main() {
  if (!glfwInit()) {
    printf("GLFW initialisation failed!");
    glfwTerminate();
    return 1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  GLFWwindow *mainWindow =
      glfwCreateWindow(WIDTH, HEIGHT, "Test Window", NULL, NULL);
  if (!mainWindow) {
    printf("GLFW window creation failed!");
    glfwTerminate();
    return 1;
  }

  int bufferWidth, bufferHeight;
  glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

  glfwMakeContextCurrent(mainWindow);

  glewExperimental = GL_TRUE;

  if (glewInit() != GLEW_OK) {
    printf("GLEW initialisation failed!");
    glfwDestroyWindow(mainWindow);
    glfwTerminate();
    return 1;
  }

  glViewport(0, 0, bufferWidth, bufferHeight);

  CreateTriangle();
  CompileShaders();

  while (!glfwWindowShouldClose(mainWindow)) {
    glfwPollEvents();

    if (direction) {
      triOffset += triIncrement;
    } else {
      triOffset -= triIncrement;
    }

    if (std::abs(triOffset) >= triMaxOffset) {
      direction = !direction;
    }

    curAngle += 0.1f;
    if (curAngle >= 360) {
      curAngle -= 360;
    }

    if (sizeDirection) {
      curSize += 0.01f;
    } else {
      curSize -= 0.01f;
    }

    if (curSize >= maxSize || curSize <= minSize) {
      sizeDirection = !sizeDirection;
    }

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shader);

    glm::mat4 model = glm::mat4(1.0f);
    model =
        glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
    // model = glm::translate(model, glm::vec3(triOffset, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));

    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glUseProgram(0);

    glfwSwapBuffers(mainWindow);
  }

  return 0;
}
