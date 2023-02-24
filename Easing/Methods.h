#pragma once
#include"TargetFunctions.h"

float moveHorizLine(float t) { return 0.3f; }

float changeSlope(float t) { return t; }

float changeSlopeAndMove(float t) { return t; }

float makeParabolic(float t) {
    return t;
}

float moveParabolaLeft(float t) { return sqr(t); }  //sqr(t) is same as t*t 

float moveParabolaUp(float t) { return sqr(t - 0.5); }

float invertParabola(float t) { return sqr(t - 0.5); }

float narrowParabola(float t) { return sqr(t - 0.5); }

float widenAndMoveParabola(float t) { return  4 * sqr(t - 0.5); }

float moveCubicLeft(float t) { return  13 * cub(t) - 10 * sqr(t) + 1; }

float moveCubicDown(float t) { return  13*cub(t) -10 * sqr(t) + 1 ; }

float easeIn(float t) { return t; }

float easeInUpsideDown(float t) { return t; }

float easeInFlipLeftRight(float t) { return t; }

float easeOut(float t) { return t; }

float easeInThruCentre(float t) { return t; }

float easeOutThruCentre(float t) { return t; }

float easeInOut(float t) { 
    if (t < 0.5)
        return t;
    else
        return 0.5;
}

float easeInCubic(float t) {
    return t * t;
}

float easeInCubicThruCenter(float t) {
    return t * t;
}

float easeInOutCubic(float t) {
    return t;
}

