#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
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
void godCamera();

#define GAME_WIDTH 640
#define GAME_HEIGHT 480

Game game;

static float g_lightPos[4] = { 0, 100, 0, 1 };  // Position of light
int old_x = -1;
int old_y = -1;

Camera camera2(20, 50, 20, 
               0, 0, 0, 
               0, 1, 0);
Camera camera3(10, 10, 0, 
               0, 50, 0, 
               0, 1, 0);
Camera camera4(-20, 30, -20, 
               0, 0, 0, 
               0, 1, 0);
Camera camera5(20, 100, 0, 
               0, 0, 0, 
               0, 1, 0);

Camera *camera = &camera2;

//angle of rotation
float xpos = 0, ypos = 0, zpos = 0, xrot = 0, yrot = 0;
float lastx, lasty;
bool usingGodCamera = false;

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
    case '1':
      usingGodCamera = true;
      break;
    case '2':
      camera = &camera2;
      usingGodCamera = false;
      break;
    case '3':
      camera = &camera3;
      usingGodCamera = false;
      break;
    case '4':
      camera = &camera4;
      usingGodCamera = false;
      break;
    case '5':
      camera = &camera5;
      usingGodCamera = false;
      break;
    default:
      game.input(key, x, y);
  }
  glutPostRedisplay();
}

void readUpKeyboard(unsigned char key, int x, int y)
{
  glutPostRedisplay();
}

void readSpecialKeyboard(int key, int x, int y)
{
  float xrotrad, yrotrad;

  switch(key)
  {
    case GLUT_KEY_LEFT:
      yrotrad = (yrot / 180 * 3.141592654f);
      xpos -= float(cos(yrotrad)) * 0.2;
      zpos -= float(sin(yrotrad)) * 0.2;
      break;
    case GLUT_KEY_RIGHT:
      yrotrad = (yrot / 180 * 3.141592654f);
      xpos += float(cos(yrotrad)) * 0.2;
      zpos += float(sin(yrotrad)) * 0.2;
      break;
    case GLUT_KEY_UP:
      yrotrad = (yrot / 180 * 3.141592654f);
      xrotrad = (xrot / 180 * 3.141592654f); 
      xpos += float(sin(yrotrad)) ;
      zpos -= float(cos(yrotrad)) ;
      ypos -= float(sin(xrotrad)) ;
      break;
    case GLUT_KEY_DOWN:
      yrotrad = (yrot / 180 * 3.141592654f);
      xrotrad = (xrot / 180 * 3.141592654f); 
      xpos -= float(sin(yrotrad));
      zpos += float(cos(yrotrad)) ;
      ypos += float(sin(xrotrad));
      break;
  }

  glutPostRedisplay();
}

void readSpecialUpKeyboard(int key, int x, int y)
{
  glutPostRedisplay();
}

void mouseMotion(int x, int y) 
{
  int diffx=x-lastx;
  int diffy=y-lasty;
  lastx=x;
  lasty=y;
  xrot += (float) diffy;
  yrot += (float) diffx;

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
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();

  if(usingGodCamera)
    godCamera();
  else
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

  game.render();

  glutSwapBuffers();
}

void godCamera () {
  glRotatef(xrot,1.0,0.0,0.0);  //rotate our camera on the x-axis (left and right)
  glRotatef(yrot,0.0,1.0,0.0);  //rotate our camera on the y-axis (up and down)
  glTranslated(-xpos,-ypos,-zpos); //translate the screen to the position of our camera
}
