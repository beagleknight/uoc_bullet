#ifndef CLASS_SPHERE_H
#define CLASS_SPHERE_H

#include "physics_manager.hpp"
#include "vector3.hpp"

class Sphere
{
  public:
    Sphere(PhysicsManager* _pm, int _radius, Vector3 position);
    ~Sphere();
    Vector3 getPosition();
    int getRadius();
  private:
    PhysicsManager* pm;
    btRigidBody* body;
    int radius;
};

#endif
