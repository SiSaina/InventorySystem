#pragma once
#include <iostream>
#include <string>
#include <limits>
#include "ItemType.h"
using namespace std;
class Validation
{
public:
	static int ValidateIntInput(string prompt, int min, int max);
	static string ValidateStringInput(string prompt);
	static float ValidateFloatInput(string prompt, float min, float max);
	static ItemType ValidateItemTypeInput(string prompt);
};

