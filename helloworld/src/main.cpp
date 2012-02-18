#include <btBulletDynamicsCommon.h>
#include <iostream>

int main () {
  std::cout << "Hello World!" << std::endl;

  // Build the broadphase
  btBroadphaseInterface* broadphase = new btDbvtBroadphase();

  // Set up the collision configuration and dispatcher
  btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
  btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);

  // The actual physics solver
  btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

  // The world.
  btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);
  dynamicsWorld->setGravity(btVector3(0,-10,0));

  // Create a ground shape at Y = 1
  btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0,1,0),1);
  btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,-1,0)));
  // Create a ground body with infinite mass
  btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0,groundMotionState,groundShape,btVector3(0,0,0));
  btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
  // Add ground to the world
  dynamicsWorld->addRigidBody(groundRigidBody);

  // Create a sphere shape with radius = 1m at Y = 50
  btCollisionShape* fallShape = new btSphereShape(1);
  btDefaultMotionState* fallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,50,0)));
  // Create a sphere body with 1kg mass
  btScalar mass = 1;
  btVector3 fallInertia(0,0,0);
  fallShape->calculateLocalInertia(mass,fallInertia);
  btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass,fallMotionState,fallShape,fallInertia);
  btRigidBody* fallRigidBody = new btRigidBody(fallRigidBodyCI);
  // Add sphere to the world
  dynamicsWorld->addRigidBody(fallRigidBody);

  // Simulation 300 times at 60hz
  for (int i=0 ; i<300 ; i++) {
    dynamicsWorld->stepSimulation(1/60.f,10);

    btTransform trans;
    fallRigidBody->getMotionState()->getWorldTransform(trans);

    std::cout << "sphere height: " << trans.getOrigin().getY() << std::endl;
  }

  // Delete sphere
  dynamicsWorld->removeRigidBody(fallRigidBody);
  delete fallRigidBody->getMotionState();
  delete fallRigidBody;
  delete fallShape;

  // Delete ground
  dynamicsWorld->removeRigidBody(groundRigidBody);
  delete groundRigidBody->getMotionState();
  delete groundRigidBody;
  delete groundShape;

  // Delete world
  delete dynamicsWorld;
  delete solver;
  delete collisionConfiguration;
  delete dispatcher;
  delete broadphase;

  return 0;
}
