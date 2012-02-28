#include "sphere.hpp"

Sphere::Sphere(PhysicsManager* _pm, Vector3 position, int _radius) : Entity(_pm)
{
  radius = _radius;
  createBody(position);
}

Sphere::~Sphere()
{
}

void Sphere::createBody(Vector3 position)
{
  body = pm->createSphereBody(radius, position);
}

void Sphere::render()
{
  glColor3f(color.x, color.y, color.z);
  glutSolidSphere(radius, 10, 10); 
}

void Sphere::update(float dt)
{
}

int Sphere::getRadius()
{
  return radius;
}
