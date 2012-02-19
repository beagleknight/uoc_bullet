#include "physics_manager.hpp"

int main () {
  PhysicsManager *pm = new PhysicsManager();

  // Simulation 300 times at 60hz
  for (int i=0 ; i<300 ; i++) {
    pm->simulate();
  }

  delete pm;
  return 0;
}
