#include "collision_filter.hpp"

CollisionFilter::CollisionFilter(PhysicsManager* _pm, GameLogic* _game_logic)
{
  pm = _pm;
  game_logic = _game_logic;
  pm->setCollisionCallback(this);
}

CollisionFilter::~CollisionFilter()
{

}

bool CollisionFilter::needBroadphaseCollision(btBroadphaseProxy* proxy0,btBroadphaseProxy* proxy1) const
{
  if(game_logic->getTarget() != 0 && game_logic->getObjective() != 0)
  {
    btRigidBody* body0 = (btRigidBody*) proxy0->m_clientObject;
    btRigidBody* body1 = (btRigidBody*) proxy1->m_clientObject;

    if(body0 == game_logic->getObjective() && body1 == game_logic->getTarget())
    {
      std::cout << "Collision with objective!" << std::endl;
    }
    else 
    {
      if(body1 == game_logic->getTarget())
      {
        if(body0 != game_logic->getObjective() && 
            body0 != game_logic->getGround())
        {
          game_logic->setControl(body0);
        }
      }
    }
  }
  return true;
}
