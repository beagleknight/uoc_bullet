#include "god_camera.hpp"

GodCamera::GodCamera(float ex, float ey, float ez, 
                     float cx, float cy, float cz, 
                     float ux, float uy, float uz) : Camera(ex, ey, ez,
                                                            cx, cy, cz,
                                                            ux, uy, uz)
{

}

GodCamera::~GodCamera()
{

}

void GodCamera::place()
{
  glRotatef(pitch, 1.0f,0.0f,0.0f);
  glRotatef(yaw, 0.0f,1.0f,0.0f);
  glTranslatef(-eye.getX(), -eye.getY(), -eye.getZ());
}

void GodCamera::input(unsigned char key, int x, int y)
{
  float xrotrad, yrotrad, xpos, ypos, zpos; 
  
  xpos = eye.getX();
  ypos = eye.getY();
  zpos = eye.getZ();

  switch(key)
  {
    case GLUT_KEY_LEFT:
      yrotrad = (yaw / 180 * 3.141592654f);
      xpos -= float(cos(yrotrad)) * 1.2;
      zpos -= float(sin(yrotrad)) * 1.2;
      break;
    case GLUT_KEY_RIGHT:
      yrotrad = (yaw / 180 * 3.141592654f);
      xpos += float(cos(yrotrad)) * 1.2;
      zpos += float(sin(yrotrad)) * 1.2;
      break;
    case GLUT_KEY_UP:
      yrotrad = (yaw / 180 * 3.141592654f);
      xrotrad = (pitch / 180 * 3.141592654f); 
      xpos += float(sin(yrotrad)) ;
      zpos -= float(cos(yrotrad)) ;
      ypos -= float(sin(xrotrad)) ;
      break;
    case GLUT_KEY_DOWN:
      yrotrad = (yaw / 180 * 3.141592654f);
      xrotrad = (pitch / 180 * 3.141592654f); 
      xpos -= float(sin(yrotrad));
      zpos += float(cos(yrotrad)) ;
      ypos += float(sin(xrotrad));
      break;
  }

  eye.setX(xpos);
  eye.setY(ypos);
  eye.setZ(zpos);
}
