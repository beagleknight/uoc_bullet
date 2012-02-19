#include "physics_manager.hpp"

PhysicsManager::PhysicsManager()
{
  // Build the broadphase
  broadphase = new btDbvtBroadphase();

  // Set up the collision configuration and dispatcher
  collisionConfiguration = new btDefaultCollisionConfiguration();
  dispatcher = new btCollisionDispatcher(collisionConfiguration);

  // The actual physics solver
  solver = new btSequentialImpulseConstraintSolver;

  // The world.
  dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);
  dynamicsWorld->setGravity(btVector3(0,-10,0));

  // Create a ground shape at Y = 1
  groundShape = new btStaticPlaneShape(btVector3(0,1,0),1);
  groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,-1,0)));
  // Create a ground body with infinite mass
  btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0,groundMotionState,groundShape,btVector3(0,0,0));
  groundRigidBody = new btRigidBody(groundRigidBodyCI);
  // Add ground to the world
  dynamicsWorld->addRigidBody(groundRigidBody);

  // Create a sphere shape with radius = 1m at Y = 50
  fallShape = new btSphereShape(5);
  fallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,50,0)));
  // Create a sphere body with 1kg mass
  btScalar mass = 1;
  btVector3 fallInertia(0,0,0);
  fallShape->calculateLocalInertia(mass,fallInertia);
  btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass,fallMotionState,fallShape,fallInertia);
  fallRigidBody = new btRigidBody(fallRigidBodyCI);
  // Add sphere to the world
  dynamicsWorld->addRigidBody(fallRigidBody);
}

PhysicsManager::~PhysicsManager()
{
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
}

void PhysicsManager::simulate(float dt)
{
  dynamicsWorld->stepSimulation(dt,10);
}


Vector3 PhysicsManager::getSpherePosition()
{
  btTransform trans;
  fallRigidBody->getMotionState()->getWorldTransform(trans);
  return Vector3(trans.getOrigin().getX(),trans.getOrigin().getY(),trans.getOrigin().getZ());
}
