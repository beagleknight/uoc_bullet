#include "game_logic.hpp"

GameLogic::GameLogic()
{
  ground = 0;
  objective = 0;
  target = 0;
  control = 0;
}

GameLogic::~GameLogic()
{

}

void GameLogic::setGround(btRigidBody* body)
{
  ground = body;
}

btRigidBody* GameLogic::getGround()
{
  return ground;
}

void GameLogic::setObjective(btRigidBody* body)
{
  objective = body;
}

btRigidBody* GameLogic::getObjective()
{
  return objective;
}

void GameLogic::setTarget(btRigidBody* body)
{
  target = body;
}

btRigidBody* GameLogic::getTarget()
{
  return target;
}

void GameLogic::setControl(btRigidBody* body)
{
  control = body;
}

btRigidBody* GameLogic::getControl()
{
  return control;
}
