#pragma once
#include <string>
#include<assert.h>
using namespace std;

struct Problem
{
	Problem() { assert("default contructor should not be called"); };
	Problem(string title, string description, string solution, float (*target)(float), float (*starter)(float)) :
		title(title), description(description), target(target), starter(starter)
	{
	};
	
	string title;
	string description;
	string starterFunction;

	float (*target)(float);
	float (*starter)(float);
};

