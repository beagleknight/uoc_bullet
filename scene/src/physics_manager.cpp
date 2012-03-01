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

btRigidBody* PhysicsManager::createRigidBody(btCollisionShape* shape, btVector3 position)
{
  btDefaultMotionState* motionState;
  btRigidBody* rigidBody;

  motionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1), position));

  btScalar mass = 1; // 1kg
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
