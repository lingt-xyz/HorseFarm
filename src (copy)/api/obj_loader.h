#pragma once

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ObjectLoader
{
public:

    static bool LoadObject(
        const char * path,
        std::vector<glm::vec3> & vertices,
        std::vector<glm::vec3> & normals,
        std::vector<glm::vec2> & uvs);
};
