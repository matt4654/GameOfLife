#ifndef GAMEOFLIFE_HPP
#define GAMEOFLIFE_HPP

#include "world.hpp"

namespace GoL
{
    class GameOfLife
    {
        private:
            World world;

        public:
            void run();
    };
}

#endif