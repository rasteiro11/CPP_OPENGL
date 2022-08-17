#ifndef _CONGFIG
#define _CONGFIG

#include <cstdio>
#include <iostream>

class Config {
public:
  static const int WIDTH = 679;
  static const int HEIGHT = 729;
  static int width;
  static int height;
  static Config *getInstance() {
    if (!config) {
      config = new Config;
    }
    return config;
  }

private:
  Config() {}
  static Config *config;
};

Config *Config::config = NULL;
int Config::width = Config::WIDTH;
int Config::height = Config::HEIGHT;

#endif
