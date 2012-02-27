#include <iostream>
#include <btBulletDynamicsCommon.h>
#include "vector3.hpp"

class PhysicsManager 
{
  public:
    PhysicsManager();
    ~PhysicsManager();
    void simulate(float dt);
    Vector3 getSpherePosition();
    void restart();
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
    btCollisionShape* fallShape;
    btDefaultMotionState* fallMotionState;
    btRigidBody* fallRigidBody;
};
