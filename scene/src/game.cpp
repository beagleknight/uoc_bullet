#include "game.hpp"

Game::Game()
{
  pm = 0;
  timer = 0;
  camera = 0;
}

Game::~Game()
{
  int i;

  if(pm != 0) delete pm;
  if(timer != 0) delete timer;

  for(i = 0; i < entities.size(); i++) {
   delete entities[i]; 
  }
  entities.clear();
  for(i = 0; i < cameras.size(); i++) {
   delete cameras[i]; 
  }
  cameras.clear();
}

void Game::init()
{
  pm = new PhysicsManager();

  timer = new Timer();
  timer->init();

  //TODO: godcamera
  //cameras.push_back(new Camera(20, 50, 20, 0, 0, 0, 0, 1, 0));
  cameras.push_back(new Camera(20, 50, 20, 0, 0, 0, 0, 1, 0));
  cameras.push_back(new Camera(10, 10, 0, 0, 50, 0, 0, 1, 0));
  cameras.push_back(new Camera(-20, 30, -20, 0, 0, 0, 0, 1, 0));
  cameras.push_back(new Camera(20, 100, 0, 0, 0, 0, 0, 1, 0));

  camera = cameras[0];
}

void Game::render()
{
  std::vector<Entity*>::iterator it;

  for(it = entities.begin(); it != entities.end(); it++)
  {
    glPushMatrix();
    glTranslatef((*it)->getPosition().x, (*it)->getPosition().y, (*it)->getPosition().z);
    (*it)->render();
    glPopMatrix();
  }
}

void Game::update()
{
  std::vector<Entity*>::iterator it;
  float dt = timer->tick();
  pm->simulate(dt);
}

void Game::input(unsigned char key, int x, int y)
{
  Sphere *sphere;
  Box *box;
  int randx, randz;
  randx = rand() % 50 + 1;
  randz = rand() % 50 + 1;

  switch(key) {
    case 'z':
      sphere = new Sphere(pm, Vector3(randx, 50, randz), 5);
      entities.push_back(sphere);
      break;
    case 'x':
      box = new Box(pm, Vector3(randx, 50, randz), Vector3(5, 5, 5));
      entities.push_back(box);
      break;
    case '2':
      camera = cameras[0];
      break;
    case '3':
      camera = cameras[1];
      break;
    case '4':
      camera = cameras[2];
      break;
    case '5':
      camera = cameras[3];
      break;
  }

  //TODO: godcamera
  //float xrotrad, yrotrad;

  //switch(key)
  //{
  //  case GLUT_KEY_LEFT:
  //    yrotrad = (yrot / 180 * 3.141592654f);
  //    xpos -= float(cos(yrotrad)) * 0.2;
  //    zpos -= float(sin(yrotrad)) * 0.2;
  //    break;
  //  case GLUT_KEY_RIGHT:
  //    yrotrad = (yrot / 180 * 3.141592654f);
  //    xpos += float(cos(yrotrad)) * 0.2;
  //    zpos += float(sin(yrotrad)) * 0.2;
  //    break;
  //  case GLUT_KEY_UP:
  //    yrotrad = (yrot / 180 * 3.141592654f);
  //    xrotrad = (xrot / 180 * 3.141592654f); 
  //    xpos += float(sin(yrotrad)) ;
  //    zpos -= float(cos(yrotrad)) ;
  //    ypos -= float(sin(xrotrad)) ;
  //    break;
  //  case GLUT_KEY_DOWN:
  //    yrotrad = (yrot / 180 * 3.141592654f);
  //    xrotrad = (xrot / 180 * 3.141592654f); 
  //    xpos -= float(sin(yrotrad));
  //    zpos += float(cos(yrotrad)) ;
  //    ypos += float(sin(xrotrad));
  //    break;
  //}
}

void Game::mouse(int x, int y)
{
  int diffx = x - lastx;
  int diffy = y - lasty;
  lastx = x;
  lasty = y;

  //TODO: godcamera
  //camera->addYaw((float) diffy);
  //camera->addPitch((float) diffx);
}

Camera* Game::getCamera()
{
  return camera;
}
