#include "sphere.hpp"

Sphere::Sphere(PhysicsManager* _pm, int _radius, Vector3 position)
{
  pm = _pm;
  radius = _radius;
  body = pm->createSphereBody(radius, position);
}

Sphere::~Sphere()
{
  if(body != 0)
    pm->removeRigidBody(body);
}

Vector3 Sphere::getPosition()
{
  btTransform trans;
  body->getMotionState()->getWorldTransform(trans);
  return Vector3(trans.getOrigin().getX(),trans.getOrigin().getY(),trans.getOrigin().getZ());
}

int Sphere::getRadius()
{
  return radius;
}
