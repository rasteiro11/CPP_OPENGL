#include "Buffer.hpp"

int main() {
  Buffer<int> *b = new Buffer<int>(3);
  b->show_buff_info();
  b->push(4);
  b->show_buff_info();
  b->push(2);
  b->show_buff_info();
  b->push(0);
  b->show_buff_info();
  b->show();
}
