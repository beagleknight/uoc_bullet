#ifndef CLASS_SPHERE_H
#define CLASS_SPHERE_H

#include <GL/glut.h>
#include "entity.hpp"

class Sphere : public Entity
{
  public:
    Sphere(PhysicsManager* _pm, btVector3 position, int radius);
    ~Sphere();
    void render();
    void update(float dt);
    int getRadius();
  private:
    btSphereShape* shape;
    void createPhysicsBody(btVector3 position);
    int radius;
};

#endif
