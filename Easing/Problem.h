#pragma once
#include <string>
using namespace std;
class Problem
{
	string title;
	string description;
	string starterFunction;

	float (*target)(float);
	float (*starter)(float);
};

