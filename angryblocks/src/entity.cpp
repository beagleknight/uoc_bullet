#include "entity.hpp"

Entity::Entity(PhysicsManager* _pm)
{
  pm = _pm;
  color = btVector3((float)rand()/(float)RAND_MAX, 
                   (float)rand()/(float)RAND_MAX, 
                   (float)rand()/(float)RAND_MAX);
}

Entity::~Entity()
{
  if(body != 0)
    pm->removeRigidBody(body);
}

btVector3 Entity::getPosition()
{
  btTransform trans;
  body->getMotionState()->getWorldTransform(trans);
  return trans.getOrigin();
}

void Entity::setPosition(btVector3 position)
{
  btTransform trans(btQuaternion(0,0,0,1), position);
  body->getMotionState()->setWorldTransform(trans);
}

btRigidBody* Entity::getBody()
{
  return body;
}
