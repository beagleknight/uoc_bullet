#ifndef CLASS_ENTITY_H
#define CLASS_ENTITY_H

#include "physics_manager.hpp"
#include "vector3.hpp"

class Entity
{
  public:
    Entity(PhysicsManager* _pm);
    ~Entity();
    Vector3 getPosition();
    virtual void render()=0;
    virtual void update(float dt)=0;
  private:
    virtual void createBody(Vector3 position)=0;
  protected:
    Vector3 color;
    PhysicsManager* pm;
    btRigidBody* body;
};

#endif
