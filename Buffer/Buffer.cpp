#include "Buffer.hpp"

template <class T> Buffer<T>::Buffer() {
  this->data = new T[10];
  this->length = 10;
  this->size = 0;
}

template <class T> Buffer<T>::Buffer(size_t length) {
  this->data = new T[length];
  this->length = length;
  this->size = 0;
}
template <class T> void Buffer<T>::push(T val) {
  if (this->size + 1 == this->length) {
    resize();
  } else {
    this->data[this->size++] = val;
  }
}

template <class T> void Buffer<T>::show() {
  for (int i = 0; i < this->size; i++) {
    std::cout << this->data[i] << std::endl;
  }
}

template <class T> void Buffer<T>::resize() {
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