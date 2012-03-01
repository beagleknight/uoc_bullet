#include <GL/glut.h>
#include "physics_manager.hpp"

class Camera
{
  public:
    Camera(float ex, float ey, float ez, 
           float cx, float cy, float cz, 
           float ux, float uy, float uz);
    ~Camera();
    void place();
    void setEye(float x, float y, float z);
    btVector3 getEye();
    void setCenter(float x, float y, float z);
    btVector3 getCenter();
    void setUp(float x, float y, float z);
    btVector3 getUp();
  private:
    btVector3 eye;    
    btVector3 center;    
    btVector3 up;    
};
