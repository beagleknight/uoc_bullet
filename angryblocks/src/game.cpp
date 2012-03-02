#include "game.hpp"

void shootBody(btRigidBody* body, btVector3 origin, btVector3 velocity);

Game::Game()
{
  pm = 0;
  collision_filter = 0;
  timer = 0;
  camera = 0;
}

Game::~Game()
{
  int i;

  if(pm != 0) delete pm;
  if(collision_filter != 0) delete pm;
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
  Box *box;
  Ground *ground;
  Capsule *capsule;

  pm = new PhysicsManager();
  collision_filter = new CollisionFilter(pm, &logic);

  timer = new Timer();
  timer->init();

  cameras.push_back(new GodCamera(50, 5, 50, 0, 0, 0, 0, 1, 0));

  cameras.push_back(new Camera(0, 70, 60, 0, 0, 0, 0, 1, 0));
  cameras.push_back(new Camera(50, 100, 0, 0, 0, 0, 0, 1, 0));
  cameras.push_back(new Camera(1, 100, 0, 0, 0, 0, 0, 1, 0));
  cameras.push_back(new Camera(50, 100, 50, 0, 0, 0, 0, 1, 0));

  camera = cameras[1];

  // Load scene
  // Ground
  ground = new Ground(pm, btVector3(0, -1, 0), btVector3(0, 1, 0));
  logic.setGround(ground->getBody());
  entities.push_back(ground);
  // Objective
  box = new Box(pm, btVector3(0, 1, 0), btVector3(10, 2, 10), btVector3(0,1,0));
  logic.setObjective(box->getBody());
  entities.push_back(box);
  // Target
  box = new Box(pm, btVector3(2, 60, 0), btVector3(5, 10, 5), btVector3(1,0,0));
  logic.setTarget(box->getBody());
  entities.push_back(box);
  // Boxes
  entities.push_back(new Box(pm, btVector3(2, 6, 0), btVector3(10, 10, 10)));
  entities.push_back(new Box(pm, btVector3(2, 16, 0), btVector3(5, 10, 5)));
  entities.push_back(new Box(pm, btVector3(2, 26, 0), btVector3(10, 10, 10)));
  entities.push_back(new Box(pm, btVector3(2, 36, 0), btVector3(15, 3, 10)));
  entities.push_back(new Box(pm, btVector3(2, 39, 0), btVector3(5, 3, 5)));
}

void Game::render()
{
  std::vector<Entity*>::iterator it;

  for(it = entities.begin(); it != entities.end(); it++)
  {
    glPushMatrix();
    glTranslatef((*it)->getPosition().getX(), 
                 (*it)->getPosition().getY(), 
                 (*it)->getPosition().getZ());
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

void Game::input(unsigned char key, int x, int y, bool pressed)
{
  Sphere *sphere;
  Box *box;
  Capsule *capsule;
  int randx, randz;
  int boxsize = rand() % 10 + 1 ;
  randx = rand() % 50 + 1;
  randz = rand() % 50 + 1;
  btRigidBody* body;
  btVector3 eye = camera->getEye();
  btVector3 direction = camera->getCenter() - camera->getEye();
  direction.normalize();
  direction*=30;
  btRigidBody* control = logic.getControl();
  btTransform trans;

  if(pressed) {
    switch(key) {
      case 'l':
        if(control != 0)
        {
          control->getMotionState()->getWorldTransform(trans);
          control->setLinearFactor(btVector3(1,1,1));
          control->getWorldTransform().setOrigin(trans.getOrigin());
          control->getWorldTransform().setRotation(btQuaternion(0,0,0,1));
          control->setLinearVelocity(btVector3(1,0,0)*15);
          control->setAngularVelocity(btVector3(0,0,0));
          control->setCcdMotionThreshold(0.5);
          control->setCcdSweptSphereRadius(0.9f);
        }
        break;
      case 'h':
        if(control != 0)
        {
          control->getMotionState()->getWorldTransform(trans);
          control->setLinearFactor(btVector3(1,1,1));
          control->getWorldTransform().setOrigin(trans.getOrigin());
          control->getWorldTransform().setRotation(btQuaternion(0,0,0,1));
          control->setLinearVelocity(btVector3(-1,0,0)*15);
          control->setAngularVelocity(btVector3(0,0,0));
          control->setCcdMotionThreshold(0.5);
          control->setCcdSweptSphereRadius(0.9f);
        }
        break;
      case 'j':
        if(control != 0)
        {
          control->getMotionState()->getWorldTransform(trans);
          control->setLinearFactor(btVector3(1,1,1));
          control->getWorldTransform().setOrigin(trans.getOrigin());
          control->getWorldTransform().setRotation(btQuaternion(0,0,0,1));
          control->setLinearVelocity(btVector3(0,0,1)*15);
          control->setAngularVelocity(btVector3(0,0,0));
          control->setCcdMotionThreshold(0.5);
          control->setCcdSweptSphereRadius(0.9f);
        }
        break;
      case 'k':
        if(control != 0)
        {
          control->getMotionState()->getWorldTransform(trans);
          control->setLinearFactor(btVector3(1,1,1));
          control->getWorldTransform().setOrigin(trans.getOrigin());
          control->getWorldTransform().setRotation(btQuaternion(0,0,0,1));
          control->setLinearVelocity(btVector3(0,0,-1)*15);
          control->setAngularVelocity(btVector3(0,0,0));
          control->setCcdMotionThreshold(0.5);
          control->setCcdSweptSphereRadius(0.9f);
        }
        break;
      case '1':
        camera = cameras[0];
        break;
      case '2':
        camera = cameras[1];
        break;
      case '3':
        camera = cameras[2];
        break;
      case '4':
        camera = cameras[3];
        break;
      case '5':
        camera = cameras[4];
        break;
    }
  }
  else 
  {
    if(control != 0)
    {
      control->getMotionState()->getWorldTransform(trans);
      control->setLinearFactor(btVector3(1,1,1));
      control->getWorldTransform().setOrigin(trans.getOrigin());
      control->getWorldTransform().setRotation(btQuaternion(0,0,0,1));
      control->setLinearVelocity(btVector3(0,0,0));
      control->setAngularVelocity(btVector3(0,0,0));
      control->setCcdMotionThreshold(0.5);
      control->setCcdSweptSphereRadius(0.9f);
    }
  }
  camera->input(key, x, y);
}

void Game::mouse(int x, int y)
{
  int diffx = x - lastx;
  int diffy = y - lasty;
  lastx = x;
  lasty = y;

  camera->addPitch((float) diffy);
  camera->addYaw((float) diffx);
}

Camera* Game::getCamera()
{
  return camera;
}

void shootBody(btRigidBody* body, btVector3 origin, btVector3 velocity)
{
  body->setLinearFactor(btVector3(1,1,1));
  body->getWorldTransform().setOrigin(origin);
  body->getWorldTransform().setRotation(btQuaternion(0,0,0,1));
  body->setLinearVelocity(velocity);
  body->setAngularVelocity(btVector3(0,0,0));
  body->setCcdMotionThreshold(0.5);
  body->setCcdSweptSphereRadius(0.9f);
}

