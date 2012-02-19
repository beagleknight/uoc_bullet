#include <stdlib.h>
#include <GL/glut.h>
#include "physics_manager.hpp"

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

int main (int argc, char** argv) {
  //PhysicsManager *pm = new PhysicsManager();

  //// Simulation 300 times at 60hz
  //for (int i=0 ; i<300 ; i++) {
  //  pm->simulate();
  //}

  //delete pm;
  //return 0;

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
  if(key == 27)
    exit(0);
}

void readUpKeyboard(unsigned char key, int x, int y)
{

}

void readSpecialKeyboard(int key, int x, int y)
{

}

void readSpecialUpKeyboard(int key, int x, int y)
{

}

void reshape(int w, int h)
{
  if(h == 0) h = 1;

  glViewport(0, 0, w, h);

}

void init(int argc, char** argv)
{
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glAlphaFunc(GL_GREATER, 0.05f);
  glEnable(GL_ALPHA_TEST);
}

void update()
{
  glutPostRedisplay();
}

void render()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();


  glutSwapBuffers();
}
