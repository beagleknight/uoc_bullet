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

btRigidBody* PhysicsManager::createRigidBody(btCollisionShape* shape, btVector3 position, btScalar mass)
{
  btDefaultMotionState* motionState;
  btRigidBody* rigidBody;

  motionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1), position));

  btVector3 inertia(0,0,0);
  shape->calculateLocalInertia(mass,inertia);

  btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(mass,motionState,shape,inertia);
  rigidBody = new btRigidBody(rigidBodyCI);

  dynamicsWorld->addRigidBody(rigidBody);
  return rigidBody;
}

void PhysicsManager::removeRigidBody(btRigidBody* body)
{
  // Delete sphere
  dynamicsWorld->removeRigidBody(body);
  delete body->getMotionState();
  delete body;
}
