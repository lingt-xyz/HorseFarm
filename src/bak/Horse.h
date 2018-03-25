//----------------------------------------------------------------------------

#define BASE_TORSO_HEIGHT 1.0
#define BASE_TORSO_WIDTH 3.0
#define BASE_TORSO_DEPTH 1.0

#define BASE_NECK_HEIGHT 1.5
#define BASE_NECK_WIDTH 0.6
#define BASE_NECK_DEPTH 0.6

#define BASE_HEAD_HEIGHT 1.0
#define BASE_HEAD_WIDTH 0.5
#define BASE_HEAD_DEPTH 0.5

#define BASE_UPPER_ARM_HEIGHT 1.0
#define BASE_LOWER_ARM_HEIGHT 1.0
#define BASE_UPPER_ARM_WIDTH  0.3
#define BASE_LOWER_ARM_WIDTH  0.3

#define BASE_UPPER_LEG_HEIGHT 1.0
#define BASE_LOWER_LEG_HEIGHT 1.0
#define BASE_UPPER_LEG_WIDTH  0.3
#define BASE_LOWER_LEG_WIDTH  0.3


double TORSO_HEIGHT = 1.0;
double TORSO_WIDTH = 3.0;
double TORSO_DEPTH = 1.0;

double NECK_HEIGHT = 1.5;
double NECK_WIDTH = 0.6;
double NECK_DEPTH = 0.6;

double HEAD_HEIGHT = 1.0;
double HEAD_WIDTH = 0.5;
double HEAD_DEPTH = 0.5;

double UPPER_ARM_HEIGHT = 1.0;
double LOWER_ARM_HEIGHT = 1.0;
double UPPER_ARM_WIDTH  = 0.3;
double LOWER_ARM_WIDTH  = 0.3;

double UPPER_LEG_HEIGHT = 1.0;
double LOWER_LEG_HEIGHT = 1.0;
double UPPER_LEG_WIDTH  = 0.3;
double LOWER_LEG_WIDTH  = 0.3;

double base_scale = 1.0f;

float base_x = 0.0;
float base_y = 0.0;
float base_z = 0.0;

double rotateX = 0.0;
double rotateY = 0.0;
double rotateZ = 0.0;

bool run_on = false;

typedef glm::vec3 point3;
typedef glm::vec4 color4;

// 36 vertices for a cube: (6 faces)(2 triangles/face)(3 vertices/triangle)
const int NumVertices = 36;

glm::vec3 points[NumVertices];
glm::vec3 normals[NumVertices];
glm::vec2 textures[NumVertices];

// eight points of a base cube
glm::vec3 vertices[8] =
{
    glm::vec3(-0.5, -0.5, 0.5),
    glm::vec3(-0.5, 0.5, 0.5),
    glm::vec3(0.5, 0.5, 0.5),
    glm::vec3(0.5, -0.5, 0.5),
    glm::vec3(-0.5, -0.5, -0.5),
    glm::vec3(-0.5, 0.5, -0.5),
    glm::vec3(0.5, 0.5, -0.5),
    glm::vec3(0.5, -0.5, -0.5)
};

//----------------------------------------------------------------------------

// Set up menu item indices, which we can also use with the joint angles
enum
{
    Torso = 0,
    Head = 1,
    LeftUpperArm = 2,
    LeftLowerArm = 3,
    RightUpperArm = 4,
    RightLowerArm = 5,
    LeftUpperLeg = 6,
    LeftLowerLeg = 7,
    RightUpperLeg = 8,
    RightLowerLeg = 9,
    Neck = 10,
    NumNodes
};

// Joint angles with initial values
GLfloat theta[NumNodes] =
{
    0.0,	// Torso
    80.0,	// Head
    190.0,	// LeftUpperArm
    -10.0,	// LeftLowerArm
    190.0,	// RightUpperArm
    -10.0,	// RightLowerArm
    180.0,	// LeftUpperLeg
    0.0,	// LeftLowerLeg
    180.0,	// RightUpperLeg
    0.0,	// RightLowerLeg
    45.0	// Neck
};

//----------------------------------------------------------------------------

Node nodes[NumNodes];

//----------------------------------------------------------------------------

int tmp_index = 0;
// given a face, initialize four points (two triangles) of it and their normals.
void quad(int a, int b, int c, int d)
{
    glm::vec3 u = vertices[b] - vertices[a];
    glm::vec3 v = vertices[c] - vertices[b];

    glm::vec3 normal = normalize(cross(u, v));
    normals[tmp_index] = normal;
    points[tmp_index] = vertices[a];
    textures[tmp_index] = glm::vec2(1.0f, 0.0f);

    tmp_index++;
    normals[tmp_index] = normal;
    points[tmp_index] = vertices[b];
    textures[tmp_index] = glm::vec2(1.0f, 1.0f);

    tmp_index++;
    normals[tmp_index] = normal;
    points[tmp_index] = vertices[c];
    textures[tmp_index] = glm::vec2(0.0f, 1.0f);

    tmp_index++;
    normals[tmp_index] = normal;
    points[tmp_index] = vertices[a];
    textures[tmp_index] = glm::vec2(1.0f, 0.0f);

    tmp_index++;
    normals[tmp_index] = normal;
    points[tmp_index] = vertices[c];
    textures[tmp_index] = glm::vec2(0.0f, 1.0f);

    tmp_index++;
    normals[tmp_index] = normal;
    points[tmp_index] = vertices[d];
    textures[tmp_index] = glm::vec2(0.0f, 0.0f);

    tmp_index++;
}

// initialize the base cube and all the normals
void generateBaseCube(void)
{
    quad(1, 0, 3, 2);
    quad(2, 3, 7, 6);
    quad(3, 0, 4, 7);
    quad(6, 5, 1, 2);
    quad(4, 5, 6, 7);
    quad(5, 4, 0, 1);
}

void updateTorso()
{
    TORSO_HEIGHT = BASE_TORSO_HEIGHT * base_scale;
    TORSO_WIDTH = BASE_TORSO_WIDTH * base_scale;
    TORSO_DEPTH = BASE_TORSO_DEPTH * base_scale;

    NECK_HEIGHT = BASE_NECK_HEIGHT * base_scale;
    NECK_WIDTH = BASE_NECK_WIDTH * base_scale;
    NECK_DEPTH = BASE_NECK_DEPTH * base_scale;

    UPPER_ARM_HEIGHT = BASE_UPPER_ARM_HEIGHT * base_scale;
    LOWER_ARM_HEIGHT = BASE_LOWER_ARM_HEIGHT * base_scale;
    UPPER_ARM_WIDTH = BASE_UPPER_ARM_WIDTH * base_scale;
    LOWER_ARM_WIDTH = BASE_LOWER_ARM_WIDTH * base_scale;

    UPPER_LEG_HEIGHT = BASE_UPPER_LEG_HEIGHT * base_scale;
    LOWER_LEG_HEIGHT = BASE_LOWER_LEG_HEIGHT * base_scale;
    UPPER_LEG_WIDTH = BASE_UPPER_LEG_WIDTH * base_scale;
    LOWER_LEG_WIDTH = BASE_LOWER_LEG_WIDTH * base_scale;

    HEAD_HEIGHT = BASE_HEAD_HEIGHT * base_scale;
    HEAD_WIDTH = BASE_HEAD_WIDTH * base_scale;
    HEAD_DEPTH = BASE_HEAD_DEPTH * base_scale;
}

int tmp_step = 1;
// to waste some frames to keep the horse run slowly
int tmp_time = 0;
int speedDivision = 10;

void run()
{
    switch(tmp_step)
    {
    case 1 :
        theta[RightUpperLeg] = 150;
        theta[RightLowerLeg] = 90;
        theta[LeftUpperLeg] = 110;
        theta[LeftLowerLeg] = 90;
        theta[RightUpperArm] = 130;
        theta[RightLowerArm] = -10;
        theta[LeftUpperArm] = 150;
        theta[LeftLowerArm] = -20;
        theta[Neck] = 55;
        theta[Torso] = 0;
        break;
    case 2 :
        theta[RightUpperLeg] = 110;
        theta[RightLowerLeg] = 90;
        theta[LeftUpperLeg] = 110;
        theta[LeftLowerLeg] = 50;
        theta[RightUpperArm] = 170;
        theta[RightLowerArm] = -10;
        theta[LeftUpperArm] = 220;
        theta[LeftLowerArm] = -20;
        theta[Neck] = 45;
        theta[Torso] = -5;
        break;
    case 3 :
        theta[RightUpperLeg] = 120;
        theta[RightLowerLeg] = 70;
        theta[LeftUpperLeg] = 160;
        theta[LeftLowerLeg] = 0;
        theta[RightUpperArm] = 200;
        theta[RightLowerArm] = -30;
        theta[LeftUpperArm] = 250;
        theta[LeftLowerArm] = -10;
        theta[Neck] = 55;
        theta[Torso] = -2;
        break;
    case 4 :
        theta[RightUpperLeg] = 160;
        theta[RightLowerLeg] = 0;
        theta[LeftUpperLeg] = 190;
        theta[LeftLowerLeg] = 0;
        theta[RightUpperArm] = 220;
        theta[RightLowerArm] = -20;
        theta[LeftUpperArm] = 250;
        theta[LeftLowerArm] = -70;
        theta[Neck] = 45;
        theta[Torso] = 2;
        break;
    case 5 :
        theta[RightUpperLeg] = 190;
        theta[RightLowerLeg] = 0;
        theta[LeftUpperLeg] = 200;
        theta[LeftLowerLeg] = 10;
        theta[RightUpperArm] = 250;
        theta[RightLowerArm] = -90;
        theta[LeftUpperArm] = 230;
        theta[LeftLowerArm] = -90;
        theta[Neck] = 55;
        theta[Torso] = 5;
        break;
    case 6 :
        theta[RightUpperLeg] = 200;
        theta[RightLowerLeg] = 20;
        theta[LeftUpperLeg] = 170;
        theta[LeftLowerLeg] = 80;
        theta[RightUpperArm] = 210;
        theta[RightLowerArm] = -90;
        theta[LeftUpperArm] = 190;
        theta[LeftLowerArm] = -80;
        theta[Neck] = 55;
        theta[Torso] = 2;
        break;
    }
}

void resetHorse(){
    base_scale = 1.0;
    updateTorso();

    base_x = 0.0;
    base_y = 0.0;
    base_z = 0.0;

    rotateX = 0.0;
    rotateY = 0.0;
    rotateZ = 0.0;

    tmp_step = 1;
    tmp_time = 0;
    speedDivision = 10;
    run_on = false;

    theta[Torso] = 0.0f;
    theta[Head] = 80.0f;
    theta[LeftUpperArm] = 190.0f;
    theta[LeftLowerArm] = -10.0f;
    theta[RightUpperArm] = 190.0f;
    theta[RightLowerArm] = -10.0f;
    theta[LeftUpperLeg] = 180.0f;
    theta[LeftLowerLeg] = 0.0f;
    theta[RightUpperLeg] = 180.0f;
    theta[RightLowerLeg] = 0.0f;
    theta[Neck] = 45.0f;
}


MatrixStack mvstack;
glm::mat4 base_model;
GLuint shader_current;

//----------------------------------------------------------------------------

void traverse(Node* node)
{
    if (node == NULL)
    {
        return;
    }

    mvstack.push(base_model);

    base_model *= node->transform;
    node->render();

    if (node->child)
    {
        traverse(node->child);
    }

    base_model = mvstack.pop();

    if (node->sibling)
    {
        traverse(node->sibling);
    }
}

//----------------------------------------------------------------------------

void torso()
{
    mvstack.push(base_model);

    glUniform4f(glGetUniformLocation(shader_current, "shader_color"), 0.7f,1.0f,0.7f,1.0f);
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.5f * TORSO_HEIGHT, 0.0f));
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(TORSO_WIDTH, TORSO_HEIGHT, TORSO_DEPTH));
    glUniformMatrix4fv(glGetUniformLocation(shader_current, "model"), 1, GL_FALSE, value_ptr(base_model * translate * scale));
    glDrawArrays(GL_TRIANGLES, 0, NumVertices);

    base_model = mvstack.pop();
}

void neck()
{
    mvstack.push(base_model);

    glUniform4f(glGetUniformLocation(shader_current, "shader_color"), 0.8f,0.9f,0.75f,1.0f);
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.5 * NECK_HEIGHT, 0.0));
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(NECK_WIDTH, NECK_HEIGHT, NECK_DEPTH));
    glUniformMatrix4fv(glGetUniformLocation(shader_current, "model"), 1, GL_FALSE, value_ptr(base_model * translate * scale));
    glDrawArrays(GL_TRIANGLES, 0, NumVertices);

    base_model = mvstack.pop();
}

void head()
{
    mvstack.push(base_model);

    glUniform4f(glGetUniformLocation(shader_current, "shader_color"), 0.6f,0.6f,0.65f,1.0f);
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.5 * HEAD_HEIGHT, 0.0));
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(HEAD_WIDTH, HEAD_HEIGHT, HEAD_DEPTH));
    glUniformMatrix4fv(glGetUniformLocation(shader_current, "model"), 1, GL_FALSE, value_ptr(base_model * translate * scale));
    glDrawArrays(GL_TRIANGLES, 0, NumVertices);

    base_model = mvstack.pop();
}

void left_upper_arm()
{
    mvstack.push(base_model);

    glUniform4f(glGetUniformLocation(shader_current, "shader_color"), 0.6f,0.7f,0.8f,1.0f);
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.5 * UPPER_ARM_HEIGHT, 0.0));
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(UPPER_ARM_WIDTH, UPPER_ARM_HEIGHT, UPPER_ARM_WIDTH));
    glUniformMatrix4fv(glGetUniformLocation(shader_current, "model"), 1, GL_FALSE, value_ptr(base_model * translate * scale));
    glDrawArrays(GL_TRIANGLES, 0, NumVertices);

    base_model = mvstack.pop();
}

void left_lower_arm()
{
    mvstack.push(base_model);

    glUniform4f(glGetUniformLocation(shader_current, "shader_color"), 0.7f,0.6f,0.7f,1.0f);
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.5 * LOWER_ARM_HEIGHT, 0.0));
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(LOWER_ARM_WIDTH, LOWER_ARM_HEIGHT, LOWER_ARM_WIDTH));
    glUniformMatrix4fv(glGetUniformLocation(shader_current, "model"), 1, GL_FALSE, value_ptr(base_model * translate * scale));
    glDrawArrays(GL_TRIANGLES, 0, NumVertices);

    base_model = mvstack.pop();
}

void right_upper_arm()
{
    mvstack.push(base_model);

    glUniform4f(glGetUniformLocation(shader_current, "shader_color"), 0.6f,0.7f,0.8f,1.0f);
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.5 * UPPER_ARM_HEIGHT, 0.0));
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(UPPER_ARM_WIDTH, UPPER_ARM_HEIGHT, UPPER_ARM_WIDTH));
    glUniformMatrix4fv(glGetUniformLocation(shader_current, "model"), 1, GL_FALSE, value_ptr(base_model * translate * scale));
    glDrawArrays(GL_TRIANGLES, 0, NumVertices);

    base_model = mvstack.pop();
}

void right_lower_arm()
{
    mvstack.push(base_model);

    glUniform4f(glGetUniformLocation(shader_current, "shader_color"), 0.7f,0.6f,0.7f,1.0f);
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.5 * LOWER_ARM_HEIGHT, 0.0));
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(LOWER_ARM_WIDTH, LOWER_ARM_HEIGHT, LOWER_ARM_WIDTH));
    glUniformMatrix4fv(glGetUniformLocation(shader_current, "model"), 1, GL_FALSE, value_ptr(base_model * translate * scale));
    glDrawArrays(GL_TRIANGLES, 0, NumVertices);

    base_model = mvstack.pop();
}

void left_upper_leg()
{
    mvstack.push(base_model);

    glUniform4f(glGetUniformLocation(shader_current, "shader_color"), 0.6f,0.7f,0.8f,1.0f);
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.5 * UPPER_LEG_HEIGHT, 0.0));
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(UPPER_LEG_WIDTH, UPPER_LEG_HEIGHT, UPPER_LEG_WIDTH));
    glUniformMatrix4fv(glGetUniformLocation(shader_current, "model"), 1, GL_FALSE, value_ptr(base_model * translate * scale));
    glDrawArrays(GL_TRIANGLES, 0, NumVertices);

    base_model = mvstack.pop();
}

void left_lower_leg()
{
    mvstack.push(base_model);

    glUniform4f(glGetUniformLocation(shader_current, "shader_color"), 0.7f,0.6f,0.7f,1.0f);
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.5 * LOWER_LEG_HEIGHT, 0.0));
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(LOWER_LEG_WIDTH, LOWER_LEG_HEIGHT, LOWER_LEG_WIDTH));
    glUniformMatrix4fv(glGetUniformLocation(shader_current, "model"), 1, GL_FALSE, value_ptr(base_model * translate * scale));
    glDrawArrays(GL_TRIANGLES, 0, NumVertices);

    base_model = mvstack.pop();
}

void right_upper_leg()
{
    mvstack.push(base_model);

    glUniform4f(glGetUniformLocation(shader_current, "shader_color"), 0.6f,0.7f,0.8f,1.0f);
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.5 * UPPER_LEG_HEIGHT, 0.0));
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(UPPER_LEG_WIDTH, UPPER_LEG_HEIGHT, UPPER_LEG_WIDTH));
    glUniformMatrix4fv(glGetUniformLocation(shader_current, "model"), 1, GL_FALSE, value_ptr(base_model * translate * scale));
    glDrawArrays(GL_TRIANGLES, 0, NumVertices);

    base_model = mvstack.pop();
}

void right_lower_leg()
{
    mvstack.push(base_model);

    glUniform4f(glGetUniformLocation(shader_current, "shader_color"), 0.7f,0.6f,0.7f,1.0f);
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.5 * LOWER_LEG_HEIGHT, 0.0));
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(LOWER_LEG_WIDTH, LOWER_LEG_HEIGHT, LOWER_LEG_WIDTH));
    glUniformMatrix4fv(glGetUniformLocation(shader_current, "model"), 1, GL_FALSE, value_ptr(base_model * translate * scale));
    glDrawArrays(GL_TRIANGLES, 0, NumVertices);

    base_model = mvstack.pop();
}


void initNodes()
{
    glm::mat4  m;

    m = glm::translate(glm::mat4(1.0), glm::vec3(base_x, base_y + 1.9*TORSO_HEIGHT, base_z)) * RotateX(rotateX) * RotateY(rotateY) * RotateZ(rotateZ + theta[Torso]);
    nodes[Torso] = Node(m, torso, NULL, &nodes[Neck]);

    m = glm::translate(glm::mat4(1.0), glm::vec3(-(TORSO_WIDTH / 2 - NECK_WIDTH / 2), TORSO_HEIGHT, 0.0)) * RotateZ(theta[Neck]);
    nodes[Neck] = Node(m, neck, &nodes[LeftUpperArm], &nodes[Head]);

    m = glm::translate(glm::mat4(1.0), glm::vec3(0.0, NECK_HEIGHT, 0.0)) * RotateZ(theta[Head]);
    nodes[Head] = Node(m, head, NULL, NULL);

    m = glm::translate(glm::mat4(1.0), glm::vec3(TORSO_WIDTH / 2 - UPPER_LEG_WIDTH / 2, 0.1*UPPER_LEG_HEIGHT, -TORSO_DEPTH/2 + UPPER_LEG_WIDTH / 2)) * RotateZ(theta[LeftUpperArm]);
    nodes[LeftUpperArm] = Node(m, left_upper_arm, &nodes[RightUpperArm], &nodes[LeftLowerArm]);

    m = glm::translate(glm::mat4(1.0), glm::vec3(TORSO_WIDTH / 2 - UPPER_LEG_WIDTH / 2, 0.1*UPPER_ARM_HEIGHT, TORSO_DEPTH/2 - UPPER_ARM_WIDTH / 2)) * RotateZ(theta[RightUpperArm]);
    nodes[RightUpperArm] = Node(m, right_upper_arm, &nodes[LeftUpperLeg], &nodes[RightLowerArm]);

    m = glm::translate(glm::mat4(1.0), glm::vec3(-(TORSO_WIDTH / 2 - UPPER_ARM_WIDTH / 2), 0.1*UPPER_ARM_HEIGHT, -TORSO_DEPTH/2 + UPPER_ARM_WIDTH / 2)) * RotateZ(theta[LeftUpperLeg]);
    nodes[LeftUpperLeg] = Node(m, left_upper_leg, &nodes[RightUpperLeg], &nodes[LeftLowerLeg]);

    m = glm::translate(glm::mat4(1.0), glm::vec3(-(TORSO_WIDTH / 2 - UPPER_LEG_WIDTH / 2), 0.1*UPPER_LEG_HEIGHT, TORSO_DEPTH/2 - UPPER_LEG_WIDTH / 2)) * RotateZ(theta[RightUpperLeg]);
    nodes[RightUpperLeg] = Node(m, right_upper_leg, NULL, &nodes[RightLowerLeg]);

    m = glm::translate(glm::mat4(1.0), glm::vec3(0.0, UPPER_ARM_HEIGHT, 0.0)) * RotateZ(theta[LeftLowerArm]);
    nodes[LeftLowerArm] = Node(m, left_lower_arm, NULL, NULL);

    m = glm::translate(glm::mat4(1.0), glm::vec3(0.0, UPPER_ARM_HEIGHT, 0.0)) * RotateZ(theta[RightLowerArm]);
    nodes[RightLowerArm] = Node(m, right_lower_arm, NULL, NULL);

    m = glm::translate(glm::mat4(1.0), glm::vec3(0.0, UPPER_LEG_HEIGHT, 0.0)) * RotateZ(theta[LeftLowerLeg]);
    nodes[LeftLowerLeg] = Node(m, left_lower_leg, NULL, NULL);

    m = glm::translate(glm::mat4(1.0), glm::vec3(0.0, UPPER_LEG_HEIGHT, 0.0))* RotateZ(theta[RightLowerLeg]);
    nodes[RightLowerLeg] = Node(m, right_lower_leg, NULL, NULL);
}

