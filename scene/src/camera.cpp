#include "camera.hpp"

Camera::Camera(float ex, float ey, float ez, 
               float cx, float cy, float cz, 
               float ux, float uy, float uz)
{
  eye.x = ex;
  eye.y = ey;
  eye.z = ez;
  center.x = cx;
  center.y = cy;
  center.z = cz;
  up.x = ux;
  up.y = uy;
  up.z = uz;
}

Camera::~Camera()
{

}

void Camera::place()
{
  gluLookAt(
    eye.x, eye.y, eye.z,
    center.x, center.y, center.z,
    up.x, up.y, up.z 
  );
}

void Camera::setEye(float x, float y, float z)
{
  eye.x = x;
  eye.y = y;
  eye.z = z;
}

Vector3 Camera::getEye()
{
  return eye;
}

void Camera::setCenter(float x, float y, float z)
{
  center.x = x;
  center.y = y;
  center.z = z;
}

Vector3 Camera::getCenter()
{
  return center;
}

void Camera::setUp(float x, float y, float z)
{
  up.x = x;
  up.y = y;
  up.z = z;
}

Vector3 Camera::getUp()
{
  return up;
}
