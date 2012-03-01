#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GL/glut.h>

#include "game.hpp"

void readKeyboard(unsigned char key, int x, int y);
void readUpKeyboard(unsigned char key, int x, int y);
void readSpecialKeyboard(int key, int x, int y);
void readSpecialUpKeyboard(int key, int x, int y);
void mouseMotion(int x, int y);
void reshape(int w, int h);
void init(int argc, char** argv);
void update();
void render();
void renderAxis();
void godCamera();

#define GAME_WIDTH 1024
#define GAME_HEIGHT 768

Game game;
bool drawAxis = false;

static float g_lightPos[4] = { 0, 100, 0, 1 };

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
  glutCreateWindow("Bullet: Scene");

  glutKeyboardFunc(readKeyboard);
  glutKeyboardUpFunc(readUpKeyboard);
  glutSpecialFunc(readSpecialKeyboard);
  glutSpecialUpFunc(readSpecialUpKeyboard);
  glutPassiveMotionFunc(mouseMotion);
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
      exit(0);
      break;
    case 's':
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      break;
    case 'w':
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      break;
    case 'a':
      drawAxis = !drawAxis;
      break;
    default:
      game.input(key, x, y);
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
  game.input(key, x, y);
  glutPostRedisplay();
}

void readSpecialUpKeyboard(int key, int x, int y)
{
  glutPostRedisplay();
}

void mouseMotion(int x, int y) 
{
  game.mouse(x,y);
  glutPostRedisplay(); 
}

void init(int argc, char** argv)
{
  srand(time(NULL));

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  glAlphaFunc(GL_GREATER, 0.05f);
  glEnable(GL_ALPHA_TEST);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_COLOR_MATERIAL);

  glEnable(GL_DEPTH_TEST);

  glCullFace(GL_BACK);
  glEnable(GL_CULL_FACE);

  glutSetCursor(GLUT_CURSOR_NONE);

  game.init();
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

  glMatrixMode (GL_MODELVIEW);

  glutPostRedisplay();
}

void update()
{
  game.update();
  glutPostRedisplay();
}

void render()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glLightfv(GL_LIGHT0, GL_POSITION, g_lightPos);

  game.getCamera()->place();

  if(drawAxis)
    renderAxis();

  game.render();

  glutSwapBuffers();
}

void renderAxis() {
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
}
