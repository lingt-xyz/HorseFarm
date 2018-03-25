const std::string TITLE = "RobotHorse";
unsigned int WIDTH=800, HEIGHT=800;

const int gridX = 50;
const int gridZ = 50;

//float c_rotate_x = 0.0f;
float c_vertical = 0.0f;
float c_horizontal = 90.0f;
float c_dir_x = 0.0f;
float c_dir_y = 0.0f;
float c_dir_z = 0.0f;

float fov = 45.0f;//perspective angle

bool texture_on = false;
bool shadow_on = false;

// lighting
// -------------
glm::vec3 lightPos(0.0f, 20.0f, 0.0f);

// camera
float c_radius = 80.0f;
glm::vec3 c_pos;
glm::vec3 c_dir; // camera direction
glm::vec3 c_up = glm::vec3(0, 1, 0); // tell the camera which way is 'up'


void resetConfiguration()
{
    c_vertical = 0.0f;
    c_horizontal = 90.0f;

    c_dir_x = 0.0f;
    c_dir_y = 0.0f;
    c_dir_z = 0.0f;

    fov = 45.0f;

    texture_on = false;
    shadow_on = false;
}
