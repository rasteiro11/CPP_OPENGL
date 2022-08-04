#include <cstddef>
#include <cstdlib>
#include <iostream>
template <typename T> class Buffer {
private:
  T *data;
  size_t size;
  size_t len;

public:
  Buffer(size_t size) { this->data = new T[size]; }
}
