#include "../include/world.hpp"
#include <iostream>
#include <map>
#include <functional>
#include <conio.h>

namespace GoL
{
    World::World()
        : currentState(allFalseState()) {}


    std::shared_ptr<bool2DArray>  World::allFalseState()
    {
        std::shared_ptr<bool2DArray> state = std::make_shared<bool2DArray>();
        (*state)[0].fill(false);
        state->fill((*state)[0]);
        return state;
    }

    void World::setSeed()
    {
        std::pair<int, int> cursor(9, 14);

        std::map<char, std::function<void()>> navMap = {
        {'w', [&cursor](){--cursor.first;}},
        {'a', [&cursor](){--cursor.second;}},
        {'s', [&cursor](){++cursor.first;}},
        {'d', [&cursor](){++cursor.second;}},
        {'e', [this, &cursor](){(*currentState)[cursor.first][cursor.second] = !((*currentState)[cursor.first][cursor.second]);}},
        };

        std::pair<int, int> loopPosition;
        char input;

        while(true)
        {
            std::cout << "Move: w,a,s,d\n";
            std::cout << "Edit Cell: e\n";
            std::cout << "Start GoL: q\n";

            loopPosition.first = 0;
            for(auto y : *currentState)
            {
                loopPosition.second = 0;
                if(loopPosition.first < 9 || loopPosition.first > 14){ ++loopPosition.first; continue; }
                for(bool x : y)
                {
                    if(loopPosition.second < 14 || loopPosition.second > 24){ ++loopPosition.second; continue; }
                    if(loopPosition != cursor){ x ? std::cout << '*' : std::cout << '.'; }
                    else{ std::cout << '_'; }
                    ++loopPosition.second;
                }
                std::cout << "\n";
                ++loopPosition.first;
            }

            input = getch();
            if(input == 'q'){ std::cout << "\n\n"; break; }
            else if(navMap.find(input) != navMap.end()){ navMap[input](); std::cout << "\n\n"; }
            else{ std::cout << "\n\n Invalid Input\n"; }
        }
    }

    bool World::determineCellFate(std::shared_ptr<bool2DArray> state, std::pair<int, int> coord)
    {
        bool cellAlive;
        (*state)[coord.first][coord.second] ? cellAlive = true : cellAlive = false; 

        int neighbours = 0;
        for(int i = -1; i < 2; i = i + 2)
        {
            for(int j = -1; j < 2; j = j + 2)
            {
                if((*state)[coord.first + i][coord.second + j]){ neighbours++; }; 
            }
            if((*state)[coord.first + i][coord.second]){ neighbours++; };
            if((*state)[coord.first][coord.second + i]){ neighbours++; };
        }

        if(!cellAlive)
        {
            if(neighbours == 3){ return true; }
            else{ return false; }
        }
        else
        {
            if(neighbours < 2){ return false; }
            else if(neighbours == 2 || neighbours == 3){ return true; }
            else{ return false; }
        }
    }   

    void World::updateCurrentState()
    {
        futureState = allFalseState();
        std::pair<int, int> loopPosition;

        loopPosition.first = 0;
        for(auto y : *currentState)
        {
            loopPosition.second = 0;
            if(loopPosition.first == 0 ||  loopPosition.first == currentState->size()-1){ ++loopPosition.first; continue; }
            for(bool x : y)
            {
                if(loopPosition.second == 0 || loopPosition.second == (*currentState)[0].size()-1){ ++loopPosition.second; continue; }
                else
                {
                    bool cellFate = determineCellFate(currentState, loopPosition);
                    (*futureState)[loopPosition.first][loopPosition.second] = cellFate;
                }
                ++loopPosition.second;
            }
            ++loopPosition.first;
        }

        *currentState = *futureState;
    }

    void World::displayCurrentState()
    {
        std::pair<int, int> loopPosition;
        loopPosition.first = 0;
        for(auto y : *currentState)
        {
            loopPosition.second = 0;
            if(loopPosition.first < 9 || loopPosition.first > 14) { ++loopPosition.first; continue; }
            for(bool x : y)
            {
                if(loopPosition.second < 14 || loopPosition.second > 24){ ++loopPosition.second; continue; }
                else
                {
                    x ? std::cout << '*' : std::cout << '.';
                }
                ++loopPosition.second; 
            }
            std::cout << "\n";
            ++loopPosition.first;
        }
    }
}