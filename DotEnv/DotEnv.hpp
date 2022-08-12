#ifndef _DOTENV
#define _DOTENV
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

class DotEnv {
public:
  DotEnv() {}
  DotEnv(const char *fileName) {
    this->fileName = fileName;
    std::ifstream fileStream(fileName);
    std::string line = "";
    while (!fileStream.eof()) {
      std::getline(fileStream, line);
      std::string var_name = line.substr(0, line.find("="));
      std::string var_value = line.substr(line.find("=") + 1, line.size());
      if (!(var_name.size() == 0)) {
        vars.insert({var_name, var_value});
      }
    }
    fileStream.close();
  }

  std::string getValue(std::string var_name) {
    std::string data;
    std::cout << "WE NEED TO GET: " << var_name << std::endl;
    try {
      data = vars.at(var_name);
    } catch (std::exception &oor) {
      std::cout << "ERROR: " << oor.what() << std::endl;
      std::exit(1);
    }
    return data;
  }

  friend std::ostream &operator<<(std::ostream &os, const DotEnv &s) {
    for (const auto &key_value : s.vars) {
      os << "[Key: " << key_value.first << " => "
         << "Value: " << key_value.second << "]\n";
    }
    return os;
  }

private:
  std::string fileName;
  std::unordered_map<std::string, std::string> vars;
};

#endif
