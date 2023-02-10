#pragma once
#include"TargetFunctions.h"

float moveHorizLine(float t) { return 0.25f; }

float changeSlope(float t) { return t; }

float changeSlopeAndMove(float t) { return t; }

float moveParabolaLeft(float t) { return sqr(t); }  //sqr(t) is same as t*t 

float moveParabolaUp(float t) { return sqr(t - 0.5); }

float invertParabola(float t) { return sqr(t - 0.5); }

float widenParabola(float t) { return 2 * sqr(t - 0.5); }

float widenAndMoveParabola(float t) { return  2 * sqr(t - 0.75); }

float easeIn(float t) { return sqr(t); }

float easeInUpsideDown(float t) { return 1 - sqr(t); }

float easeInFlipVert(float t) { return sqr(1 - t); }

float easeOut(float t) { return 1 - sqr(1 - t); }

float easeInThruCentre(float t) { return 2 * sqr(t); }

float easeOutThruCentre(float t) { return 1 - 2 * sqr(1 - t); }

float tween(float t, float start, float end) {
    return start + t * (end - start);
}
float easeInQuadratic(float t) {
    return 2 * t * t;
}

float easeOutQuadratic(float t) {
    return 1 - easeInQuadratic(1 - t);
}

float easeInOutQuadratic(float t) {
    //return tween(t, easeInQuadratic(t), easeOutQuadratic(t));
    return  t < 0.5 ? easeInQuadratic(t) : easeOutQuadratic(t);
}

float easeInCubic(float t) {
    return 4 * t * t * t;
}

float easeOutCubic(float t) {
    return 1 - easeInCubic(1 - t);
}

float easeInOutCubic(float t) {
    //return tween(t, easeInCubic(t), easeOutCubic(t));
    return  t < 0.5 ? easeInCubic(t) : easeOutCubic(t);
}

float easeInQuintic(float t) {
    return 16 * t * t * t * t * t;
}

float easeOutQuintic(float t) {
    return 1 - easeInQuintic(1 - t);
}

float easeInOutQuintic(float t) {
    //return tween(t, easeInCubic(t), easeOutCubic(t));
    return  t < 0.5 ? easeInQuintic(t) : easeOutQuintic(t);
}

float easeInBack(float t) {

    const float c1 = 1.70158;
    const float c3 = c1 + 1;

    return 4 * c3 * t * t * t - 2 * c1 * t * t;

}

float easeOutBack(float t) {

    return 1 - easeInBack(1 - t);

}

float easeInOutBack(float t) {
    //return tween(t, easeInCubic(t), easeOutCubic(t));
    return  t < 0.5 ? easeInBack(t) : easeOutBack(t);
}

//float sqr(float f) { return f * f; }
float cub(float f) { return f * f * f; }

float parabola(float t) {

    return 4 * sqr(t - 0.5);

}

float parabolaTarget(float t) {

    return sqr(t - 0.75);

}