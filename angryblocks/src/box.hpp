#ifndef CLASS_BOX_H
#define CLASS_BOX_H

#include <GL/glut.h>
#include "entity.hpp"

class Box : public Entity
{
  public:
    Box(PhysicsManager* _pm, btVector3 position, btVector3 _dimension, btVector3 color = btVector3(0,0,0));
    ~Box();
    void render();
    void update(float dt);
    btVector3 getDimension();
  private:
    void createPhysicsBody(btVector3 position);
    btBoxShape* shape;
    btVector3 dimension;
};

#endif
