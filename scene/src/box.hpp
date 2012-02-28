#ifndef CLASS_BOX_H
#define CLASS_BOX_H

#include "physics_manager.hpp"
#include "vector3.hpp"

class Box
{
  public:
    Box(PhysicsManager* _pm, Vector3 _dimension, Vector3 position);
    ~Box();
    Vector3 getPosition();
    Vector3 getDimension();
  private:
    PhysicsManager* pm;
    btRigidBody* body;
    Vector3 dimension;
};

#endif
