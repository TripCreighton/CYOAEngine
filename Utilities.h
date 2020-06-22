#pragma once // Forces the compiler to include this file once, prevents scoping and linking problems...

#include <string>
#include <cmath>
#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

class Utilities
{
public:
	/*
	 - Splits a string by a delimiter

	 - Type: Vector of type String
	 - Params:
	  - input - The string to split
	  - delimiter - The character to split by
	 */
	static vector<string> split(string input, char delimiter);
	
	/*
	 - Converts an array of integers to a string

	 - Type: String
	 - Params:
	  - input - A vector of integers
	 */
	static string arrayToString(vector<int> input);
	
	/*
	 - Converts and returns the string in lowercase

	 - Type: String
	 - Params:
	  - input - The string to convert
	 */
	static string toLower(string input);
};

