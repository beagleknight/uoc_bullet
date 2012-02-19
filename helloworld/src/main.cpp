#include <stdlib.h>
#include <GL/glut.h>
#include "physics_manager.hpp"
#include "timer.hpp"
#include "camera.hpp"

void readKeyboard(unsigned char key, int x, int y);
void readUpKeyboard(unsigned char key, int x, int y);
void readSpecialKeyboard(int key, int x, int y);
void readSpecialUpKeyboard(int key, int x, int y);
void reshape(int w, int h);
void init(int argc, char** argv);
void update();
void render();

#define GAME_WIDTH 640
#define GAME_HEIGHT 480

PhysicsManager *pm = new PhysicsManager();
Timer *timer = new Timer();
static float g_lightPos[4] = { 0, 100, 0, 1 };  // Position of light

Camera camera1(20, 50, 20, 
               0, 0, 0, 
               0, 1, 0);
Camera camera2(10, 10, 0, 
               0, 50, 0, 
               0, 1, 0);
Camera camera3(-20, 30, -20, 
               0, 0, 0, 
               0, 1, 0);
Camera camera4(20, 100, 0, 
               0, 0, 0, 
               0, 1, 0);

Camera *camera = &camera1;

int main (int argc, char** argv) {
  int res_x, res_y, pos_x, pos_y;

  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE); 

  res_x = glutGet(GLUT_SCREEN_WIDTH);
  res_y = glutGet(GLUT_SCREEN_HEIGHT);
  pos_x = (res_x>>1)-(GAME_WIDTH>>1);
  pos_y = (res_y>>1)-(GAME_HEIGHT>>1);

  glutInitWindowPosition(pos_x,pos_y);
  glutInitWindowSize(GAME_WIDTH, GAME_HEIGHT);
  glutCreateWindow("Bullet: HelloWorld");

  glutKeyboardFunc(readKeyboard);
  glutKeyboardUpFunc(readUpKeyboard);
  glutSpecialFunc(readSpecialKeyboard);
  glutSpecialUpFunc(readSpecialUpKeyboard);
  glutReshapeFunc(reshape);
  glutDisplayFunc(render);
  glutIdleFunc(update);

  init(argc, argv);

  glutMainLoop();
}

void readKeyboard(unsigned char key, int x, int y)
{
  switch(key) {
    case 27:
      delete pm;
      delete timer;
      exit(0);
      break;
    case 's':
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      break;
    case 'w':
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      break;
    case '1':
      camera = &camera1;
      break;
    case '2':
      camera = &camera2;
      break;
    case '3':
      camera = &camera3;
      break;
    case '4':
      camera = &camera4;
      break;
  }

  glutPostRedisplay();
}

void readUpKeyboard(unsigned char key, int x, int y)
{
  glutPostRedisplay();
}

void readSpecialKeyboard(int key, int x, int y)
{
  glutPostRedisplay();
}

void readSpecialUpKeyboard(int key, int x, int y)
{
  glutPostRedisplay();
}

void init(int argc, char** argv)
{
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  glAlphaFunc(GL_GREATER, 0.05f);
  glEnable(GL_ALPHA_TEST);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_COLOR_MATERIAL);

  glCullFace(GL_BACK);
  glEnable(GL_CULL_FACE);

  timer->init();
}

void reshape(int w, int h)
{
  if(h == 0) h = 1;

  glViewport(0, 0, w, h);

  GLfloat aspectRatio;
  aspectRatio = (GLfloat) w / (GLfloat) h;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(90,aspectRatio,1,1000);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  camera->place();

  glutPostRedisplay();
}

void update()
{
  float dt = timer->tick();
  pm->simulate(dt);

  camera3.setCenter(pm->getSpherePosition().x, pm->getSpherePosition().y, pm->getSpherePosition().z);

  glutPostRedisplay();
}

void render()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();

  camera->place();

  glLightfv(GL_LIGHT0, GL_POSITION, g_lightPos);

  // DrawAxis
  glBegin(GL_LINES);
  glColor3f(1.0f, 0.0f, 0.0f);
  glVertex3f(0.0f, 0.0f, 0.0f);
  glVertex3f(100.0f, 0.0f, 0.0f);
  glColor3f(0.0f, 1.0f, 0.0f);
  glVertex3f(0.0f, 0.0f, 0.0f);
  glVertex3f(0.0f, 100.0f, 0.0f);
  glColor3f(0.0f, 0.0f, 1.0f);
  glVertex3f(0.0f, 0.0f, 0.0f);
  glVertex3f(0.0f, 0.0f, 100.0f);
  glEnd();

  // Draw ground
  glColor3f(0.3f, 1.0f, 0.3f);
  glBegin(GL_QUADS);
  glVertex3f(-50, 0, 50);
  glVertex3f(50, 0, 50);
  glVertex3f(50, 0, -50);
  glVertex3f(-50, 0, -50);
  glEnd();

  // Draw sphere
  glColor3f(1.0f, 0.3f, 0.3f);
  glPushMatrix();
  glTranslatef(0.0f, pm->getSpherePosition().y, 0.0f);
  glutSolidSphere(5.0f, 10, 10); 
  glPopMatrix();

  // Draw cameras
  glColor3f(0.0f, 0.0f, 1.0f);

  glPushMatrix();
  glTranslatef(camera1.getEye().x, camera1.getEye().y, camera1.getEye().z);
  glutSolidCube(5.0f);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(camera2.getEye().x, camera2.getEye().y, camera2.getEye().z);
  glutSolidCube(5.0f);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(camera3.getEye().x, camera3.getEye().y, camera3.getEye().z);
  glutSolidCube(5.0f);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(camera4.getEye().x, camera4.getEye().y, camera4.getEye().z);
  glutSolidCube(5.0f);
  glPopMatrix();

  glutSwapBuffers();
}
