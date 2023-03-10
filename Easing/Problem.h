/*==============================================================================
Do not edit any code in this file!!!


██████   ██████      ███    ██  ██████  ████████     ███████ ██████  ██ ████████
██   ██ ██    ██     ████   ██ ██    ██    ██        ██      ██   ██ ██    ██
██   ██ ██    ██     ██ ██  ██ ██    ██    ██        █████   ██   ██ ██    ██
██   ██ ██    ██     ██  ██ ██ ██    ██    ██        ██      ██   ██ ██    ██
██████   ██████      ██   ████  ██████     ██        ███████ ██████  ██    ██


████████ ██   ██ ██ ███████     ███████ ██ ██      ███████ ██
   ██    ██   ██ ██ ██          ██      ██ ██      ██      ██
   ██    ███████ ██ ███████     █████   ██ ██      █████   ██
   ██    ██   ██ ██      ██     ██      ██ ██      ██
   ██    ██   ██ ██ ███████     ██      ██ ███████ ███████ ██

==============================================================================*/
#pragma once
#include <string>
#include<assert.h>
using namespace std;

struct Vec2 {
	float x, y;
};

struct Problem
{
	Problem():title(""), description(""), target(NULL), starter(NULL), ptarget(NULL), pstarter(NULL) { assert("default contructor should not be called"); };
	Problem(string title, int index, string description, string starterFunction,  
		float (*starter)(float), float (*target)(float), bool s=false, Vec2(*ptarget)(float) =NULL, Vec2(*pstarter)(float) =NULL) :
		title(title), index(index), description(description), starterFunction(starterFunction), target(target), starter(starter), showBall(s),
		ptarget(ptarget), pstarter(pstarter)
	{
	};
	
	bool check();
	string title;
	int index = 0;
	string description;
	string starterFunction;

	bool passing = false;
	bool showBall = false;

	float (*target)(float);
	float (*starter)(float);

	//parametric
	Vec2 (*ptarget)(float);
	Vec2 (*pstarter)(float);
};

