#include <iostream>
#include <btBulletDynamicsCommon.h>

class PhysicsManager 
{
  public:
    PhysicsManager();
    ~PhysicsManager();
    void simulate();
    float getSpherePosition();
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
