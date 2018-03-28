// Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
static const GLfloat buffer_data_grid[] =
{
    0.f, 0.f, 0.f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
    1.f, 0.f, 0.f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    1.f, 0.f, 1.f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
    0.f, 0.f, 1.f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
};

unsigned int indices[] = {
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};

static const GLfloat buffer_data_axis[] =
{
     0.0f, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
     5.0f, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
     5.0f, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
     4.5f, 0.0f,  0.2f, 1.0f, 0.0f, 0.0f, 1.0f,
     5.0f, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
     4.5f, 0.0f, -0.2f, 1.0f, 0.0f, 0.0f, 1.0f,

     0.0f, 0.0f,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
     0.0f, 5.0f,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
     0.0f, 5.0f,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
     0.2f, 4.5f,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
     0.0f, 5.0f,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
    -0.2f, 4.5f,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f,

     0.0f, 0.0f,  0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
     0.0f, 0.0f,  5.0f, 0.0f, 0.0f, 1.0f, 1.0f,
     0.0f, 0.0f,  5.0f, 0.0f, 0.0f, 1.0f, 1.0f,
     0.2f, 0.0f,  4.5f, 0.0f, 0.0f, 1.0f, 1.0f,
     0.0f, 0.0f,  5.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    -0.2f, 0.0f,  4.5f, 0.0f, 0.0f, 1.0f, 1.0f,
};

static const GLfloat buffer_data_cube[] =
{
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,

    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,

     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,

    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f
};
