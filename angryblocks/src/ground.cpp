#include "ground.hpp"

Ground::Ground(PhysicsManager* _pm, btVector3 position, btVector3 _normal) : Entity(_pm)
{
  pm = _pm;
  normal = _normal;
  createPhysicsBody(position);
}

Ground::~Ground()
{
  delete pm;
}

void Ground::render()
{
  float size = 300;

  //glColor3f(color.getX(), color.getY(), color.getZ());
  glColor3f(0.3f, 0.3f, 0.3f);
  glBegin(GL_QUADS);
  glNormal3f(0, 1, 0);
  glVertex3f(-size, 0, size);
  glNormal3f(0, 1, 0);
  glVertex3f(size, 0, size);
  glNormal3f(0, 1, 0);
  glVertex3f(size, 0, -size);
  glNormal3f(0, 1, 0);
  glVertex3f(-size, 0, -size);
  glEnd();
}

void Ground::update(float dt)
{

}

void Ground::createPhysicsBody(btVector3 position)
{
  shape = new btStaticPlaneShape(normal, 1);
  body = pm->createRigidBody(shape, position, 0); // 0 mass for static object
}
