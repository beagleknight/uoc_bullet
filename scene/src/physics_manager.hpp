#ifndef CLASS_PHYSICS_MANAGER_H
#define CLASS_PHYSICS_MANAGER_H

#include <iostream>
#include <btBulletDynamicsCommon.h>

class PhysicsManager 
{
  public:
    PhysicsManager();
    ~PhysicsManager();
    void simulate(float dt);
    btRigidBody* createRigidBody(btCollisionShape* shape, btVector3 position, btScalar mass = 1);
    void removeRigidBody(btRigidBody* body);
    btTypedConstraint* createP2PConstraint(btRigidBody ba, btVector3 pa);
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
