#include "camera.hpp"

Camera::Camera(float ex, float ey, float ez, 
               float cx, float cy, float cz, 
               float ux, float uy, float uz)
{
  eye.setX(ex);
  eye.setY(ey);
  eye.setZ(ez);
  center.setX(cx);
  center.setY(cy);
  center.setZ(cz);
  up.setX(ux);
  up.setY(uy);
  up.setZ(uz);
}

Camera::~Camera()
{

}

void Camera::place()
{
  gluLookAt(
    eye.getX(), eye.getY(), eye.getZ(),
    center.getX(), center.getY(), center.getZ(),
    up.getX(), up.getY(), up.getZ() 
  );
}

void Camera::setEye(float x, float y, float z)
{
  eye.setX(x);
  eye.setY(y);
  eye.setZ(z);
}

btVector3 Camera::getEye()
{
  return eye;
}

void Camera::setCenter(float x, float y, float z)
{
  center.setX(x);
  center.setY(y);
  center.setZ(z);
}

btVector3 Camera::getCenter()
{
  return center;
}

void Camera::setUp(float x, float y, float z)
{
  up.setX(x);
  up.setY(y);
  up.setZ(z);
}

btVector3 Camera::getUp()
{
  return up;
}
