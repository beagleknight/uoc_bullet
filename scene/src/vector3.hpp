#ifndef CLASS_VECTOR3
#define CLASS_VECTOR3

#include <btBulletDynamicsCommon.h>

class Vector3
{
  public:
    Vector3();
    Vector3(float _x, float _y, float _z);
    ~Vector3();
    btVector3 toBtVector3();
    float x;
    float y;
    float z;
};

#endif
