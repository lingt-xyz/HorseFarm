#include <cstdlib>

int getRandomFromRange(int gridX)
{
    return rand() % gridX + 1;
}

bool getRandomBool()
{
    return (rand() % 2 == 0) ? true:false;
}

//----------------------------------------------------------------------------
glm::mat4 RotateX(float f)
{
    return glm::rotate(glm::mat4(1.0f), glm::radians(f), glm::vec3(1, 0, 0));
}

glm::mat4 RotateY(float f)
{
    return glm::rotate(glm::mat4(1.0f), glm::radians(f), glm::vec3(0, 1, 0));
}

glm::mat4 RotateZ(float f)
{
    return glm::rotate(glm::mat4(1.0f), glm::radians(f), glm::vec3(0, 0, 1));
}
