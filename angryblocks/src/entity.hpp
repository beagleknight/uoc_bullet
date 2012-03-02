#ifndef CLASS_ENTITY_H
#define CLASS_ENTITY_H

#include "physics_manager.hpp"

class Entity
{
  public:
    Entity(PhysicsManager* _pm);
    ~Entity();
    btVector3 getPosition();
    void setPosition(btVector3 position);
    btRigidBody* getBody();
    virtual void render()=0;
    virtual void update(float dt)=0;
  private:
    virtual void createPhysicsBody(btVector3 position)=0;
  protected:
    btVector3 color;
    PhysicsManager* pm;
    btRigidBody* body;
};

#endif
