#pragma once

#include <cstdlib>
#include <random>
#include <iostream>

static int getRandomFromRange(int gridX)
{
    return rand() % gridX + 1;
}

static float getRandomFromRange(float from, float to){
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(from, to);
    return dis(gen);
}

static bool getRandomBool()
{
    return (rand() % 2 == 0) ? true:false;
}

static float getRandomFloat(){
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(0.0, 1.0);
    return dis(gen);
}
