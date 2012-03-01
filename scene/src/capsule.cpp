#include "capsule.hpp"

Capsule::Capsule(PhysicsManager* _pm, btVector3 position, btScalar _radius, btScalar _height) : Entity(_pm)
{
  pm = _pm;
  radius = _radius;
  height = _height;
  createPhysicsBody(position);
}

Capsule::~Capsule()
{
  delete shape;
}

void Capsule::render()
{
  glColor3f(color.getX(), color.getY(), color.getZ());
  glPushMatrix();
  glTranslatef(0, height - radius, 0);
  glutSolidSphere(radius, 10, 10); 
  glPopMatrix();
  glutSolidSphere(radius, 10, 10); 
  glPushMatrix();
  glTranslatef(0,  -(height - radius), 0);
  glutSolidSphere(radius, 10, 10); 
  glPopMatrix();
}

void Capsule::update(float dt)
{

}

void Capsule::createPhysicsBody(btVector3 position)
{
  shape = new btCapsuleShape(radius, height);
  body = pm->createRigidBody(shape, position);
}
