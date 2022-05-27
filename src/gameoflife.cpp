#include "../include/gameoflife.hpp"
#include <iostream>
#include <thread>
#include <chrono>

namespace GoL
{
    void GameOfLife::run()
    {
        world.setSeed();
        while(true)
        {
            std::cout << "\n\n";
            world.updateCurrentState();
            world.displayCurrentState();
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
}