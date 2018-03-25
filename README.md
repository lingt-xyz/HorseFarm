Implementation Specifications
---------------------------------------
* Creates a 100x100 square grid (ground surface) in the XZ plane centred at the origin.
* Creates a set of three lines 5 grid units in length, in 3 different colors, representing each coordinate axis in
virtual world space, centered at the origin.
* Creates a model of the horse like the one shown in the figure by suitably transforming One unit cube to create
the different body parts. The horse is initially positioned at the centre of the grid facing along X axis with its
feet on the ground. Different body parts in slightly different color.
* Places a virtual camera with the world space origin as the point of focus.
* For display and animation:
  * create a GLFW window of size 800x800 with double buffering support.
  * render the coordinate axis, ground and horse in the window.
  * The application should use a perspective view to display the objects and use the depth buffer for hidden
surface removal.
* The application should handle the following input:
  * Pressing the spacebar should re-position the horse at a random location on the grid.
  * The user can incrementally size up the horse by pressing ‘U’ for scale-up and ‘J’ for scale-down. Each
key press should result in a small size change.
  * The user can control the horse position and orientation using keyboard input i.e. A → move left 1 grid
unit, D → move right 1 grid unit, W → move up 1 grid unit, S → move down 1 grid unit, a → rotate left
5 degrees about Y axis, d → rotate right 5 degrees about Y axis, w → rotate upwards 5 degrees
raising the front legs, s → rotate downwards 5 degrees raising the hind legs.
  * The world orientation is changed by using keyboard input i.e. left arrow → R x , right arrow → R -x , up
arrow → R y , down arrow → R -y . Pressing the “Home” button should reset to the initial world position
and orientation.
  * The user can change the rendering mode i.e. points, lines, triangles based on keyboard input i.e. key
‘P’ for points, key ‘L’ for lines, key ‘T’ for triangles. The user can pan and tilt the camera as follows:
    * while right button is pressed → use mouse movement in x direction to pan; and
    * while middle button is pressed → use mouse movement in y direction to tilt.
  * The user can zoom in and out of the scene - while left button is pressed → use mouse movement to
move into/out of the scene.
  * Window resize handling: The application should handle window resize events and correctly adjust the
aspect ratio accordingly. This means that the meshes should not be distorted in any way.
  * Illuminate the scene by adding a point light source (white) 20 units above the horse using the phong
model.
  * Render the scene with grass texture on the ground mesh and horse-skin texture on the horse (Key X).
  * Render the scene with shadows using two pass shadow algorithm (Key B).
  * Rotate joint 0 by 5 degrees (Key_0 clockwise and the corresponding Shift + Key_0 for counterclockwise). Similarly for other numbered joints, that is Key_1 for joint 1, Key 2 for joint 2, etc.
  * Make the horse complete a run cycle (Key R).

Submission
---------------------------
* create a zip file containing your C/C++ code, vertex shader, fragment shader, a readme text file (.txt). 
* In the readme file document the features and functionality of the application, and anything else you want the grader to know
i.e. control keys, keyboard/mouse shortcuts, etc.
