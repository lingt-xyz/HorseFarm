#include "input.h"

bool Input::Keys[1024];
bool Input::KeysProcessed[1024];

std::map<int, bool> Input::keyDown;
std::map<int, bool> Input::keyUp;
std::map<int, bool> Input::keyHeld;
