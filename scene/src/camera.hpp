#ifndef CLASS_CAMERA_H
#define CLASS_CAMERA_H

#include <GL/glut.h>
#include "physics_manager.hpp"

class Camera
{
  public:
    Camera(float ex, float ey, float ez, 
           float cx, float cy, float cz, 
           float ux, float uy, float uz);
    ~Camera();
    virtual void place();
    virtual void input(unsigned char key, int x, int y);
    void setEye(float x, float y, float z);
    btVector3 getEye();
    void setCenter(float x, float y, float z);
    btVector3 getCenter();
    void setUp(float x, float y, float z);
    btVector3 getUp();
    void addYaw(float _yaw);
    void addPitch(float _pitch);
  protected:
    btVector3 eye;    
    btVector3 center;    
    btVector3 up;    
    float yaw;
    float pitch;
};

#endif
