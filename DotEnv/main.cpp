#include "DotEnv.hpp"
#include <iostream>
int main() {
  DotEnv *env = new DotEnv(".env");
  std::cout << *env << std::endl;
  std::string width = env->getValue("WIDTH");
  std::string height = env->getValue("HEIGHT");
  std::cout << "WIDTH: " << width << std::endl;
  std::cout << "HEIGHT: " << height << std::endl;
}
