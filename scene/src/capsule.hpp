#ifndef CLASS_CAPSULE_H
#define CLASS_CAPSULE_H

#include <GL/glut.h>
#include "entity.hpp"

class Capsule : public Entity
{
  public:
    Capsule(PhysicsManager* _pm, btVector3 position, btScalar _radius, btScalar _height);
    ~Capsule();
    void render();
    void update(float dt);
  private:
    btCapsuleShape* shape;
    void createPhysicsBody(btVector3 position);
    btScalar radius;
    btScalar height;
};

#endif
