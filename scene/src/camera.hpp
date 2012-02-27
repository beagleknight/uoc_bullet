#include "vector3.hpp"
#include <GL/glut.h>

class Camera
{
  public:
    Camera(float ex, float ey, float ez, 
           float cx, float cy, float cz, 
           float ux, float uy, float uz);
    ~Camera();
    void place();
    void setEye(float x, float y, float z);
    Vector3 getEye();
    void setCenter(float x, float y, float z);
    Vector3 getCenter();
    void setUp(float x, float y, float z);
    Vector3 getUp();
  private:
    Vector3 eye;    
    Vector3 center;    
    Vector3 up;    
};
