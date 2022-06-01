#pragma once
#include <chrono>

class TimingManager
{
  private:
    std::chrono::_V2::steady_clock::time_point nextTickEnd;
    std::chrono::_V2::steady_clock::time_point lastTickEnd;
    std::chrono::microseconds tickLength();

    std::chrono::microseconds lastFrameTime;
    std::chrono::microseconds averageFrameTime;

  public:
    unsigned int fps;

    TimingManager(unsigned int fps);
    void init();
    void tick();
    void printStats();
};