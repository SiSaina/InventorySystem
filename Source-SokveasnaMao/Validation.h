#pragma once
#include <iostream>
#include <string>
#include <limits>
#include <functional>
#include <algorithm>
#include "ItemType.h"
using namespace std;
class Validation
{
public:
	// validate int input within range
	// prompt: message shown to user
	// min, max: allow range
	// return valid int, or error message
	static int ValidateIntInput(string prompt, int min, int max);

	// validate string input within range
	// prompt: message shown to user
	// return valid string, or error message
	static string ValidateStringInput(string prompt);

	// validate float input within range
	// prompt: message shown to user
	// min, max: allow range
	// return valid float, or error message
	static float ValidateFloatInput(string prompt, float min, float max);

	// validate item type input within range
	// prompt: message shown to user
	// return valid item type, or error message
	static ItemType ValidateItemTypeInput(string prompt);

	// validate file input within range
	// prompt: message shown to user
	// return valid file path, or error message
	static bool ValidateFilePath(const string& path);

	// convert string to lowercase
	static string ToLower(string value);
};

