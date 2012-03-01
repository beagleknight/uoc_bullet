#include "box.hpp"

Box::Box(PhysicsManager* _pm, btVector3 position, btVector3 _dimension) : Entity(_pm)
{
  dimension = _dimension;
  createPhysicsBody(position);
}

Box::~Box()
{
  delete shape;
}

void Box::createPhysicsBody(btVector3 position)
{
  shape = new btBoxShape(dimension);
  body = pm->createRigidBody(shape, position);
}

void Box::render()
{
  glColor3f(color.getX(), color.getY(), color.getZ());
  glutSolidCube(dimension.getX()*2);
}

void Box::update(float dt)
{
}

btVector3 Box::getDimension()
{
  return dimension;
}
