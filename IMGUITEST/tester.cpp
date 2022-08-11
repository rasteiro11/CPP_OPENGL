#include "Config.hpp"
#include <cstdio>
int main() {
  Config *conf = Config::getInstance();
  std::cout << conf << std::endl;
  // conf->setValues(420, 69);
  conf->printValues();
}
