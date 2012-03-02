#ifndef CLASS_GAME_LOGIC_H
#define CLASS_GAME_LOGIC_H

#include "entity.hpp"

class GameLogic
{
  public:
    GameLogic();
    ~GameLogic();
    void setGround(btRigidBody* body);
    btRigidBody* getGround();
    void setObjective(btRigidBody* body);
    btRigidBody* getObjective();
    void setTarget(btRigidBody* body);
    btRigidBody* getTarget();
    void setControl(btRigidBody* body);
    btRigidBody* getControl();
  private:
    btRigidBody* ground;
    btRigidBody* objective;
    btRigidBody* target;
    btRigidBody* control;
};

#endif
