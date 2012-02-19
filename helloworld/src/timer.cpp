#include "timer.hpp"

Timer::Timer()
{

}

Timer::~Timer()
{

}

void Timer::init()
{
  frames = 0;
  fps = 0;
  frame_time = 0;
  current_time = glutGet(GLUT_ELAPSED_TIME);
}

float Timer::tick()
{
  int oldCurrentTime;
  int dt;

  oldCurrentTime = current_time;
  current_time = glutGet(GLUT_ELAPSED_TIME);
  dt = current_time - oldCurrentTime;

  frame_time += dt;
  frames++;

  if(frame_time > 1000)
  {
    fps = frames / (frame_time / 1000.0f);
    frames = 0;
    frame_time = 0;
  }

  return dt / 1000.0f;
}

float Timer::getFPS()
{
  return fps;
}
