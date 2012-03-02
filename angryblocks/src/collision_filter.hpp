#ifndef CLASS_COLLISION_FILTER_H
#define CLASS_COLLISION_FILTER_H

#include "physics_manager.hpp"
#include "game_logic.hpp"

class CollisionFilter : public btOverlapFilterCallback
{
  public:
    CollisionFilter(PhysicsManager* _pm, GameLogic* game_logic);
    ~CollisionFilter();
    bool needBroadphaseCollision(btBroadphaseProxy* proxy0,btBroadphaseProxy* proxy1) const;
  private:
    PhysicsManager* pm;
    GameLogic* game_logic;
};

#endif
