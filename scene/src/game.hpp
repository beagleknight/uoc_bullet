#ifndef CLASS_GAME_H
#define CLASS_GAME_H

#include <iostream>
#include <vector>

#include "physics_manager.hpp"
#include "timer.hpp"
#include "camera.hpp"
#include "entity.hpp"
#include "sphere.hpp"
#include "box.hpp"

class Game
{
  public:
    Game();
    ~Game();
    void init();
    void render();
    void update();
    void input(unsigned char key, int x, int y);
  private:
    PhysicsManager *pm;
    Timer *timer;
    std::vector<Entity*> entities;
};

#endif