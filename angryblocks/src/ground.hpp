#ifndef CLASS_GROUND_H
#define CLASS_GROUND_H

#include <GL/glut.h>
#include "entity.hpp"

class Ground : public Entity
{
  public:
    Ground(PhysicsManager* _pm, btVector3 position, btVector3 _normal);
    ~Ground();
    void render();
    void update(float dt);
  private:
    btStaticPlaneShape* shape;
    btVector3 normal;
    void createPhysicsBody(btVector3 position);
};

#endif
