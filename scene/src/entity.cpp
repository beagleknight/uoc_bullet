#include "entity.hpp"

Entity::Entity(PhysicsManager* _pm)
{
  pm = _pm;
  color = Vector3((float)rand()/(float)RAND_MAX, 
                  (float)rand()/(float)RAND_MAX, 
                  (float)rand()/(float)RAND_MAX);
}

Entity::~Entity()
{
  if(body != 0)
    pm->removeRigidBody(body);
}

Vector3 Entity::getPosition()
{
  btTransform trans;
  body->getMotionState()->getWorldTransform(trans);
  return Vector3(trans.getOrigin().getX(),trans.getOrigin().getY(),trans.getOrigin().getZ());
}
