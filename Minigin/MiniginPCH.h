#pragma once

#include "targetver.h"

#include <stdio.h>
#include <iostream> // std::cout
#include <sstream> // stringstream
#include <tchar.h>
#include <memory> // smart pointers
#include <vector>
#include <vld.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "Log.h" // Various logging functions
#define UNUSED(x) (void)x;


#pragma warning(push)
#pragma warning(disable: 4505) //Unreferenced local function removed (FMOD_ErrorString)

#pragma warning(pop)

