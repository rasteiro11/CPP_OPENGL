#ifndef _SHADER
#define _SHADER
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string.h>

#include <GL/glew.h>

class Shader {
public:
  Shader() {
    shaderID = 0;
    uniformModel = 0;
    uniformProjection = 0;
    uniformColorVec = 0;
    // uniformColorRed = 0;
    // uniformColorGreen = 0;
    // uniformColorBlue = 0;
  }
  Shader(const char *vertexLocation, const char *fragmentLocation) {
    shaderID = 0;
    uniformModel = 0;
    uniformProjection = 0;
    uniformColorVec = 0;
    CreateFromFiles(vertexLocation, fragmentLocation);
  }
  void CreateFromString(const char *vertexCode, const char *fragmentCode) {
    CompileShader(vertexCode, fragmentCode);
  }
  void CreateFromFiles(const char *vertexLocation,
                       const char *fragmentLocation) {
    std::string vertexString = ReadFile(vertexLocation);
    std::string fragmentString = ReadFile(fragmentLocation);
    const char *vertexCode = vertexString.c_str();
    const char *fragmentCode = fragmentString.c_str();

    CompileShader(vertexCode, fragmentCode);
  }
  std::string ReadFile(const char *fileLocation) {
    std::string content;
    std::ifstream fileStream(fileLocation, std::ios::in);
    if (!fileStream.is_open()) {
      printf("Failed to read %s! File doesn't exist", fileLocation);
      return "";
    }
    std::string line = "";
    while (!fileStream.eof()) {
      std::getline(fileStream, line);
      content.append(line + "\n");
    }

    fileStream.close();
    return content;
  }

  GLuint GetProjectionLocation() { return uniformProjection; }
  GLuint GetModelLocation() { return uniformProjection; }
  GLuint GetUniformColorVec() { return uniformColorVec; }
  // GLuint GetUniformColorRed() { return uniformColorRed; }
  // GLuint GetUniformColorGreen() { return uniformColorGreen; }
  // GLuint GetUniformColorBlue() { return uniformColorBlue; }
  void UseShader() { glUseProgram(shaderID); }
  void ClearShader() {
    if (shaderID != 0) {
      glDeleteProgram(shaderID);
      shaderID = 0;
    }
    uniformColorVec = 0;
    uniformModel = 0;
    uniformProjection = 0;
  }
  ~Shader() { ClearShader(); }

private:
  GLuint shaderID, uniformProjection, uniformModel, uniformColorVec;

  void CompileShader(const char *vertexCode, const char *fragmentCode) {
    shaderID = glCreateProgram();

    if (!shaderID) {
      printf("Failed to create shaderID\n");
      return;
    }

    AddShader(shaderID, vertexCode, GL_VERTEX_SHADER);
    AddShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar eLog[1024] = {0};

    glLinkProgram(shaderID);
    glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
    if (!result) {
      glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
      printf("Error linking program: '%s'\n", eLog);
      return;
    }

    glValidateProgram(shaderID);
    glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
    if (!result) {
      glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
      printf("Error validating program: '%s'\n", eLog);
      return;
    }
    uniformColorVec = glGetUniformLocation(shaderID, "uniform_color_vec");
    // uniformColorRed = glGetUniformLocation(shaderID, "uniform_red");
    // uniformColorGreen = glGetUniformLocation(shaderID, "uniform_green");
    // uniformColorBlue = glGetUniformLocation(shaderID, "uniform_blue");
    uniformModel = glGetUniformLocation(shaderID, "model");
    uniformProjection = glGetUniformLocation(shaderID, "projection");
  }
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
      glGetShaderInfoLog(theShader, 1024, NULL, eLog);
      fprintf(stderr, "Error compiling the %d shader: '%s'\n", shaderType,
              eLog);
      return;
    }

    glAttachShader(theProgram, theShader);
  }
};
#endif
