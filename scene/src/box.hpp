#ifndef CLASS_BOX_H
#define CLASS_BOX_H

#include <GL/glut.h>
#include "entity.hpp"
#include "vector3.hpp"

class Box : public Entity
{
  public:
    Box(PhysicsManager* _pm, Vector3 position, Vector3 _dimension);
    ~Box();
    void render();
    void update(float dt);
    Vector3 getDimension();
  private:
    void createBody(Vector3 position);
    Vector3 dimension;
};

#endif
