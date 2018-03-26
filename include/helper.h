#include <cstdlib>
#include <random>
#include <iostream>

int getRandomFromRange(int gridX)
{
    return rand() % gridX + 1;
}

bool getRandomBool()
{
    return (rand() % 2 == 0) ? true:false;
}

float getRandomFloat(){
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(0.0, 1.0);
    return dis(gen);
}
