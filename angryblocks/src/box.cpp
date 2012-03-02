#include "box.hpp"

Box::Box(PhysicsManager* _pm, btVector3 position, btVector3 _dimension, btVector3 color) : Entity(_pm)
{
  dimension = _dimension;
  createPhysicsBody(position);
  
  if(color != btVector3(0,0,0))
    this->color = color;
}

Box::~Box()
{
  delete shape;
}

void Box::createPhysicsBody(btVector3 position)
{
  shape = new btBoxShape(dimension / 2);
  body = pm->createRigidBody(shape, position);
}

void Box::render()
{
  glColor3f(color.getX(), color.getY(), color.getZ());

  glBegin(GL_QUADS);
  // Bottom face
  glNormal3f(0, -1, 0);
  glVertex3f(-dimension.getX() / 2, -dimension.getY() / 2, dimension.getZ() / 2);
  glVertex3f(-dimension.getX() / 2, -dimension.getY() / 2, -dimension.getZ() / 2);
  glVertex3f(dimension.getX() / 2, -dimension.getY() / 2, -dimension.getZ() / 2);
  glVertex3f(dimension.getX() / 2, -dimension.getY() / 2, dimension.getZ() / 2);
  // Top face
  glNormal3f(0, 1, 0);
  glVertex3f(-dimension.getX() / 2, dimension.getY() / 2, dimension.getZ() / 2);
  glVertex3f(-dimension.getX() / 2, dimension.getY() / 2, -dimension.getZ() / 2);
  glVertex3f(dimension.getX() / 2, dimension.getY() / 2, -dimension.getZ() / 2);
  glVertex3f(dimension.getX() / 2, dimension.getY() / 2, dimension.getZ() / 2);
  // Front face
  glNormal3f(0, 0, 1);
  glVertex3f(-dimension.getX() / 2, dimension.getY() / 2, dimension.getZ() / 2);
  glVertex3f(dimension.getX() / 2, dimension.getY() / 2, dimension.getZ() / 2);
  glVertex3f(dimension.getX() / 2, -dimension.getY() / 2, dimension.getZ() / 2);
  glVertex3f(-dimension.getX() / 2, -dimension.getY() / 2, dimension.getZ() / 2);
  // Back face
  glNormal3f(0, 0, -1);
  glVertex3f(-dimension.getX() / 2, dimension.getY() / 2, -dimension.getZ() / 2);
  glVertex3f(dimension.getX() / 2, dimension.getY() / 2, -dimension.getZ() / 2);
  glVertex3f(dimension.getX() / 2, -dimension.getY() / 2, -dimension.getZ() / 2);
  glVertex3f(-dimension.getX() / 2, -dimension.getY() / 2, -dimension.getZ() / 2);
  // Right face
  glNormal3f(1, 0, 0);
  glVertex3f(dimension.getX() / 2, dimension.getY() / 2, dimension.getZ() / 2);
  glVertex3f(dimension.getX() / 2, dimension.getY() / 2, -dimension.getZ() / 2);
  glVertex3f(dimension.getX() / 2, -dimension.getY() / 2, -dimension.getZ() / 2);
  glVertex3f(dimension.getX() / 2, -dimension.getY() / 2, dimension.getZ() / 2);
  // Left face
  glNormal3f(-1, 0, 0);
  glVertex3f(-dimension.getX() / 2, dimension.getY() / 2, dimension.getZ() / 2);
  glVertex3f(-dimension.getX() / 2, dimension.getY() / 2, -dimension.getZ() / 2);
  glVertex3f(-dimension.getX() / 2, -dimension.getY() / 2, -dimension.getZ() / 2);
  glVertex3f(-dimension.getX() / 2, -dimension.getY() / 2, dimension.getZ() / 2);
  glEnd();
}

void Box::update(float dt)
{
}

btVector3 Box::getDimension()
{
  return dimension;
}
