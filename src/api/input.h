#pragma once

#include <map>

class Input
{
public:

    static bool Keys[1024];
    static bool KeysProcessed[1024];

private:
	static std::map<int, bool> keyDown;
	static std::map<int, bool> keyUp;
	static std::map<int, bool> keyHeld;
};
