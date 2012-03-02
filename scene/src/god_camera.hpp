#ifndef CLASS_GOD_CAMERA_H
#define CLASS_GOD_CAMERA_H

#include "camera.hpp"

class GodCamera : public Camera
{
  public:
    GodCamera(float ex, float ey, float ez, 
              float cx, float cy, float cz, 
              float ux, float uy, float uz);
    ~GodCamera();
    void place();
    void input(unsigned char key, int x, int y);
};

#endif
