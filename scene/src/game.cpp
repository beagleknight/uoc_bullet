#include "game.hpp"

void shootBody(btRigidBody* body, btVector3 origin, btVector3 velocity);

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
  Ground *ground;
  Capsule *capsule;

  pm = new PhysicsManager();

  timer = new Timer();
  timer->init();

  //TODO: godcamera
  //cameras.push_back(new Camera(20, 50, 20, 0, 0, 0, 0, 1, 0));
  cameras.push_back(new Camera(50, 30, 50, 0, 0, 0, 0, 1, 0));
  cameras.push_back(new Camera(10, 10, 0, 0, 50, 0, 0, 1, 0));
  cameras.push_back(new Camera(-20, 30, -20, 0, 0, 0, 0, 1, 0));
  cameras.push_back(new Camera(20, 100, 0, 0, 0, 0, 0, 1, 0));

  camera = cameras[0];

  // Load scene
  // Ground
  ground = new Ground(pm, btVector3(0, -1, 0), btVector3(0, 1, 0));
  entities.push_back(ground);
  // Boxes
  entities.push_back(new Box(pm, btVector3(0, 5, 0), btVector3(5, 5, 5)));
  entities.push_back(new Box(pm, btVector3(0, 5, 10), btVector3(5, 5, 5)));
  entities.push_back(new Box(pm, btVector3(0, 5, 20), btVector3(5, 5, 5)));
  entities.push_back(new Box(pm, btVector3(10, 5, 0), btVector3(5, 5, 5)));
  entities.push_back(new Box(pm, btVector3(10, 5, 10), btVector3(5, 5, 5)));
  entities.push_back(new Box(pm, btVector3(10, 5, 20), btVector3(5, 5, 5)));
  entities.push_back(new Box(pm, btVector3(20, 5, 0), btVector3(5, 5, 5)));
  entities.push_back(new Box(pm, btVector3(20, 5, 10), btVector3(5, 5, 5)));
  entities.push_back(new Box(pm, btVector3(20, 5, 20), btVector3(5, 5, 5)));
  // Spheres
  entities.push_back(new Sphere(pm, btVector3(10, 15, 10), 5));
  entities.push_back(new Sphere(pm, btVector3(20, 15, 10), 5));
  entities.push_back(new Sphere(pm, btVector3(10, 15, 20), 5));
  entities.push_back(new Sphere(pm, btVector3(20, 15, 20), 5));
  // Capsules
  capsule = new Capsule(pm, btVector3(30, 4, 30), 2, 4);
  //TODO: constraints
  //pm->createP2PConstraint(*(capsule->getBody()), btVector3(30, -1, 30));
  entities.push_back(capsule);
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

void Game::input(unsigned char key, int x, int y)
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

  switch(key) {
    case 'z':
      sphere = new Sphere(pm, btVector3(eye.getX(), eye.getY(), eye.getZ()), rand() % 5 + 1);
      shootBody(sphere->getBody(), eye, direction); 
      entities.push_back(sphere);
      break;
    case 'x':
      box = new Box(pm, btVector3(eye.getX(), eye.getY(), eye.getZ()), 
                    btVector3(boxsize, boxsize, boxsize));
      shootBody(box->getBody(), eye, direction); 
      entities.push_back(box);
      break;
    case 'c':
      capsule = new Capsule(pm, btVector3(eye.getX(), eye.getY(), eye.getZ()), 2, 4);
      shootBody(capsule->getBody(), eye, direction);
      entities.push_back(capsule);
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
