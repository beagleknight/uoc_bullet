#ifndef CLASS_SPHERE_H
#define CLASS_SPHERE_H

#include <GL/glut.h>
#include "entity.hpp"
#include "vector3.hpp"

class Sphere : public Entity
{
  public:
    Sphere(PhysicsManager* _pm, Vector3 position, int radius);
    ~Sphere();
    void render();
    void update(float dt);
    int getRadius();
  private:
    void createBody(Vector3 position);
    int radius;
};

#endif
