#ifndef _SINGLETON
#define _SINGLETON
#include <cstdio>
#include <iostream>
template <typename T> class Singleton {
public:
  T *getInstance() {
    std::cout << data << std::endl;
    if (!data) {
      std::printf("INSTANTIATING THING\n");
      data = new T;
    }
    return data;
  }

private:
  static T *data;
};
template <typename T> T *Singleton<T>::data = NULL;

#endif
