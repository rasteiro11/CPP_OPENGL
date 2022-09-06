#ifndef _COLLIDABLE
#define _COLLIDABLE
#include "Point.hpp"

class Collidable {
  virtual bool hasCollided(Point p) = 0;
};

#endif
