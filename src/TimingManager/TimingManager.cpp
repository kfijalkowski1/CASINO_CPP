#include "TimingManager.h"
#include "GraphicsManager/GraphicsCommands/GraphicsCommands.h"
#include <iomanip>
#include <iostream>
#include <thread>

TimingManager::TimingManager(unsigned int fps) : fps(fps) {}

std::chrono::microseconds TimingManager::tickLength()
{
    return std::chrono::microseconds(1000000 / fps);
}

void TimingManager::init()
{
    lastFrameTime = std::chrono::microseconds(0);
    averageFrameTime = std::chrono::microseconds(0);
    nextTickEnd = std::chrono::steady_clock::now() + tickLength();
    lastTickEnd = std::chrono::steady_clock::now();
}
void TimingManager::tick()
{
    using namespace std::chrono;
    using namespace std::this_thread;
    lastFrameTime = round<microseconds>(steady_clock::now() - lastTickEnd);
    if (averageFrameTime.count() == 0)
        averageFrameTime = lastFrameTime;
    averageFrameTime += (lastFrameTime - averageFrameTime) / fps;

    nextTickEnd += tickLength();
    sleep_until(nextTickEnd);

    lastTickEnd = steady_clock::now();
}
void TimingManager::printStats()
{
    GraphicsCommands::moveCursor(81, 1);
    std::cout << std::setw(9) << std::setprecision(3) << std::fixed
              << (double)averageFrameTime.count() / 1000 << "ms";

    double utilization = 100.0 * ((double)averageFrameTime.count() /
                                  (double)tickLength().count());
    GraphicsCommands::moveCursor(81, 2);
    std::cout << std::setw(10) << std::setprecision(3) << std::fixed
              << utilization << '%';
}