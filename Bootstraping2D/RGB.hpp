#ifndef _RGB
#define _RGB

class RGB {
public:
  RGB();
  RGB(float r, float g, float b) : r(r), g(g), b(b) {}
  inline float getR() { return r; }
  inline float getG() { return g; }
  inline float getB() { return b; }

private:
  float r, g, b;
};

#endif
