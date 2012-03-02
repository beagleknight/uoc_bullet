#include "sphere.hpp"

Sphere::Sphere(PhysicsManager* _pm, btVector3 position, int _radius) : Entity(_pm)
{
  radius = _radius;
  createPhysicsBody(position);
}

Sphere::~Sphere()
{
  delete shape;
}

void Sphere::createPhysicsBody(btVector3 position)
{
  shape = new btSphereShape(radius);
  body = pm->createRigidBody(shape, position);
}

void Sphere::render()
{
  glColor3f(color.getX(), color.getY(), color.getZ());
  glutSolidSphere(radius, 10, 10); 
}

void Sphere::update(float dt)
{
}

int Sphere::getRadius()
{
  return radius;
}
