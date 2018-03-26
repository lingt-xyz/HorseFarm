#include "controller.h"
#include "api/window.h"

float Controller::c_vertical = 0.0f;
float Controller::c_horizontal = 90.0f;
float Controller::c_dir_x = 0.0f;
float Controller::c_dir_y = 0.0f;
float Controller::c_dir_z = 0.0f;

float Controller::fov = 45.0f;//perspective angle

float Controller::c_radius = 80.0f;
glm::vec3 Controller::c_pos;
glm::vec3 Controller::c_dir; // camera direction
glm::vec3 Controller::c_up; // tell the camera which way is 'up'

glm::vec3 Controller::light_position_ = glm::vec3(0.0f, 20.0f, 0.0f);

glm::mat4 Controller::view;
glm::mat4 Controller::projection;

bool Controller::light_on = false;
bool Controller::texture_on = false;
bool Controller::shadow_on = false;

Horse* Controller::horse_;

Controller::Controller() {}
Controller::~Controller() {}

void Controller::UpdateController()
{
    double c_pos_x = c_radius * glm::cos(glm::radians(c_vertical)) * glm::cos(glm::radians(c_horizontal));
    double c_pos_y = c_radius * glm::sin(glm::radians(c_vertical));
    double c_pos_z = c_radius * glm::cos(glm::radians(c_vertical)) * glm::sin(glm::radians(c_horizontal));
    glm::vec3 c_pos = glm::vec3(c_pos_x, c_pos_y, c_pos_z); // camera position
    glm::vec3 c_dir = glm::vec3(c_dir_x, c_dir_y, c_dir_z); // camera direction
    glm::vec3 c_up = glm::vec3(0, 1, 0);
    Controller::view = glm::lookAt(c_pos, c_dir, c_up);
    Controller::projection = glm::perspective(glm::radians(Controller::fov), (GLfloat)(Window::width) / (GLfloat)(Window::height), 1.0f, 100.0f);
}

void Controller::ResetController()
{

    Controller::c_vertical = 0.0f;
    Controller::c_horizontal = 90.0f;
    Controller::c_dir_x = 0.0f;
    Controller::c_dir_y = 0.0f;
    Controller::c_dir_z = 0.0f;

    Controller::fov = 45.0f;//perspective angle

    Controller::c_radius = 80.0f;

    Controller::horse_->ResetModel();
    Controller::UpdateController();
}
