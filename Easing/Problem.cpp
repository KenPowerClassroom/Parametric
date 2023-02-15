#include "Problem.h"

bool Problem::check() {
	float error = 0.0001f;

	float t = 0;
	float step = 0.01;
	for (; t < 1.0; t += step) {
		if (fabs(target(t) - starter(t)) > error)
			return false;
	}
	return true;
}