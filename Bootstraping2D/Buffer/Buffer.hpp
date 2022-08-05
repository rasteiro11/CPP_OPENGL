#ifndef _BUFFER
#define _BUFFER
#include "../Point.hpp"
#include <cstddef>
#include <iostream>
template <typename T> class Buffer {

private:
  size_t size;
  size_t length;
  T *data;

public:
  Buffer(size_t length) {
    this->data = new T[length];
    this->length = length;
    this->size = 0;
  }
  Buffer() {
    this->data = new T[10];
    this->length = 10;
    this->size = 0;
  }
  T *return_raw_buffer() { return this->data; }
  const size_t get_size() { return this->size; };

  void show_buff_info() {
    std::cout << "SIZE: " << this->size << "\n";
    std::cout << "LENGTH: " << this->length << "\n";
  }

  void push_point(Point &p) {
    if (this->size + 1 == this->length) {
      resize();
    }
    this->data[this->size++] = p.x;
    this->data[this->size++] = p.y;
    this->data[this->size++] = p.z;
  }
  void push(T val) {
    if ((this->size + 1) == this->length) {
      resize();
    }
    this->data[this->size++] = val;
  }
  void pop(T val);
  void show() {
    for (int i = 0; i < this->size; i++) {
      std::cout << this->data[i] << std::endl;
    }
  }
  void resize() {
    std::cout << "RESIZING BUFFER" << std::endl;
    T *temp_arr = new T[2 * this->length];
    for (int i = 0; i < this->size; i++) {
      temp_arr[i] = this->data[i];
    }
    delete this->data;
    this->length *= 2;
    this->data = temp_arr;
    std::cout << "NEW LENGTH: " << this->length << std::endl;
  }
  ~Buffer() { delete this->data; }
};
#endif