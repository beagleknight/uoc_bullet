#ifndef CLASS_PHYSICS_MANAGER_H
#define CLASS_PHYSICS_MANAGER_H

#include <iostream>
#include <btBulletDynamicsCommon.h>
#include "vector3.hpp"

class PhysicsManager 
{
  public:
    PhysicsManager();
    ~PhysicsManager();
    void simulate(float dt);
    btRigidBody* createSphereBody(int radius, Vector3 position);
    btRigidBody* createBoxBody(Vector3 dimension, Vector3 position);
    btRigidBody* createRigidBody(btCollisionShape* shape, Vector3 position);
    void removeRigidBody(btRigidBody* body);
  private:
    btBroadphaseInterface* broadphase;
    btDefaultCollisionConfiguration* collisionConfiguration;
    btCollisionDispatcher* dispatcher;
    btSequentialImpulseConstraintSolver* solver;
    btDiscreteDynamicsWorld* dynamicsWorld;
    // example specific objects
    btCollisionShape* groundShape;
    btDefaultMotionState* groundMotionState;
    btRigidBody* groundRigidBody;
};

#endif
