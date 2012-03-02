#ifndef CLASS_GAME_H
#define CLASS_GAME_H

#include <iostream>
#include <vector>

#include "physics_manager.hpp"
#include "collision_filter.hpp"
#include "timer.hpp"
#include "god_camera.hpp"
#include "camera.hpp"
#include "entity.hpp"
#include "sphere.hpp"
#include "box.hpp"
#include "ground.hpp"
#include "capsule.hpp"
#include "game_logic.hpp"

class Game
{
  public:
    Game();
    ~Game();
    void init();
    void render();
    void update();
    void input(unsigned char key, int x, int y, bool pressed);
    void mouse(int x, int y);
    Camera* getCamera();
  private:
    PhysicsManager *pm;
    CollisionFilter *collision_filter;
    Timer *timer;
    std::vector<Entity*> entities;
    std::vector<Camera*> cameras;
    Camera *camera;
    float lastx; 
    float lasty;
    GameLogic logic;
};

#endif
