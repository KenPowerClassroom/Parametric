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
#include<SFML/System/Vector2.hpp>
using namespace std;

typedef  sf::Vector2f Vec2;

struct Problem
{
	Problem():title(""), description(""), target(NULL), starter(NULL) { assert("default contructor should not be called"); };
	Problem(string title, int index, string description, string starterFunction,  
		float (*starter)(float), float (*target)(float), bool s=false, Vec2(*ptarget)(float) =NULL, Vec2(*pstarter)(float) =NULL, float interval = 1.0f) :
		title(title), index(index), description(description), starterFunction(starterFunction), target(target), starter(starter), showBall(s),
		ptarget(ptarget), pstarter(pstarter), interval(interval)
	{
	};
	
	bool check();
	string title;
	int index = 0;
	float interval;
	string description;
	string starterFunction;
	float lastT=0;

	bool passing = false;
	bool showBall = false;

	float (*target)(float);
	float (*starter)(float);

	//parametric
	Vec2 (*ptarget)(float);
	Vec2 (*pstarter)(float);
};

