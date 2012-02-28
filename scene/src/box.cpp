#include "box.hpp"

Box::Box(PhysicsManager* _pm, Vector3 _dimension, Vector3 position)
{
  pm = _pm;
  dimension = _dimension;
  body = pm->createBoxBody(dimension, position);
}

Box::~Box()
{
  if(body != 0)
    pm->removeRigidBody(body);
}

Vector3 Box::getPosition()
{
  btTransform trans;
  body->getMotionState()->getWorldTransform(trans);
  return Vector3(trans.getOrigin().getX(),trans.getOrigin().getY(),trans.getOrigin().getZ());
}

Vector3 Box::getDimension()
{
  return dimension;
}
