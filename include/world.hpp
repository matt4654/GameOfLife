#ifndef WORLD_HPP
#define WORLD_HPP

#include <memory>
#include <array>
#include <map>

namespace GoL
{
    using bool2DArray = std::array<std::array<bool, 30> , 25>;

    class World
    {
        private:
            std::shared_ptr<bool2DArray> currentState;
            std::shared_ptr<bool2DArray> futureState;
        
        public:
            World();

            std::shared_ptr<bool2DArray>  allFalseState();
            void setSeed();
            bool determineCellFate(std::shared_ptr<bool2DArray>, std::pair<int, int>);
            void updateCurrentState();
            void displayCurrentState();
    };
}

#endif