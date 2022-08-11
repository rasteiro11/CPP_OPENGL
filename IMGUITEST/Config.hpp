#ifndef _CONGFIG
#define _CONGFIG
#include <cstdio>
#include <iostream>
class Config {
public:
  static const int WIDTH = 800;
  static const int HEIGHT = 600;
  static Config *getInstance() {
    if (!config) {
      config = new Config;
    }
    return config;
  }

  //  void setValues(int WIDTH, int HEIGHT) {
  //    if (config) {
  //      this->WIDTH = WIDTH;
  //      this->HEIGHT = HEIGHT;
  //    }
  //  }
  //
  //  void printValues() {
  //    std::cout << "WIDTH: " << WIDTH << std::endl;
  //    std::cout << "HEIGHT: " << HEIGHT << std::endl;
  //  }
  //
  //  void setWidth(int WIDTH) {
  //    if (config) {
  //      this->WIDTH = WIDTH;
  //    }
  //  }
  //  void setHeight(int HEIGHT) {
  //    if (config) {
  //      this->HEIGHT = HEIGHT;
  //    }
  //  }

private:
  Config() {}
  //  Config(int WIDTH, int HEIGHT) {
  //    this->WIDTH = WIDTH;
  //    this->HEIGHT = HEIGHT;
  //  }
  // int WIDTH = 800;
  // int HEIGHT = 600;
  static Config *config;
};

Config *Config::config = 0;

#endif
