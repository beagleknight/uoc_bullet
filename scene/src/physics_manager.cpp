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

}

PhysicsManager::~PhysicsManager()
{
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

btRigidBody* PhysicsManager::createSphereBody(int radius, Vector3 position)
{
  btCollisionShape* fallShape;
  btDefaultMotionState* fallMotionState;
  btRigidBody* fallRigidBody;

  // Create a sphere shape
  fallShape = new btSphereShape(radius);
  fallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),
                                             btVector3(position.x,position.y,position.z)));

  // Create a sphere body with 1kg mass
  btScalar mass = 1;
  btVector3 fallInertia(0,0,0);
  fallShape->calculateLocalInertia(mass,fallInertia);
  btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass,fallMotionState,fallShape,fallInertia);
  fallRigidBody = new btRigidBody(fallRigidBodyCI);
  // Add sphere to the world
  dynamicsWorld->addRigidBody(fallRigidBody);

  return fallRigidBody;
}

btRigidBody* PhysicsManager::createBoxBody(Vector3 dimension, Vector3 position)
{
  btCollisionShape* fallShape;
  btDefaultMotionState* fallMotionState;
  btRigidBody* fallRigidBody;

  // Create a box shape
  fallShape = new btBoxShape(btVector3(dimension.x, dimension.y, dimension.z));
  fallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),
                                             btVector3(position.x,position.y,position.z)));

  // Create a sphere body with 1kg mass
  btScalar mass = 1;
  btVector3 fallInertia(0,0,0);
  fallShape->calculateLocalInertia(mass,fallInertia);
  btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass,fallMotionState,fallShape,fallInertia);
  fallRigidBody = new btRigidBody(fallRigidBodyCI);
  // Add sphere to the world
  dynamicsWorld->addRigidBody(fallRigidBody);

  return fallRigidBody;
}

void PhysicsManager::removeRigidBody(btRigidBody* body)
{
  // Delete sphere
  dynamicsWorld->removeRigidBody(body);
  delete body->getCollisionShape();
  delete body->getMotionState();
  delete body;
}
