#pragma once
#include <string>
#include<assert.h>
using namespace std;

struct Problem
{
	Problem():title(""), description(""), target(NULL), starter(NULL) { assert("default contructor should not be called"); };
	Problem(string title, int index, string description, string starterFunction,  float (*starter)(float), float (*target)(float)) :
		title(title), index(index), description(description), starterFunction(starterFunction), target(target), starter(starter)
	{
	};
	
	string title;
	int index = 0;
	string description;
	string starterFunction;

	float (*target)(float);
	float (*starter)(float);
};

