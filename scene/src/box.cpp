#include "box.hpp"

Box::Box(PhysicsManager* _pm, Vector3 position, Vector3 _dimension) : Entity(_pm)
{
  dimension = _dimension;
  createBody(position);
}

Box::~Box()
{
}

void Box::createBody(Vector3 position)
{
  body = pm->createBoxBody(dimension, position);
}

void Box::render()
{
  glutSolidCube(dimension.x);
}

void Box::update(float dt)
{
}

Vector3 Box::getDimension()
{
  return dimension;
}
