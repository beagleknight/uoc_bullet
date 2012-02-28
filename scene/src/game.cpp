#include "game.hpp"

Game::Game()
{
  pm = 0;
  timer = 0;
}

Game::~Game()
{
  if(pm != 0) delete pm;
  if(timer != 0) delete timer;
}

void Game::init()
{
  pm = new PhysicsManager();

  timer = new Timer();
  timer->init();
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
  }
}
