#ifndef CLASS_SPHERE_H
#define CLASS_SPHERE_H

#include "physics_manager.hpp"
#include "vector3.hpp"

class Sphere
{
  public:
    Sphere(PhysicsManager* _pm, int radius, Vector3 position);
    ~Sphere();
    Vector3 getPosition();
  private:
    PhysicsManager* pm;
    btRigidBody* body;
};

#endif
