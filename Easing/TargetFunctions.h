#pragma once
#pragma comment(lib,"TargetFunctions.lib")

float sqr(float n);
float cub(float n);


float moveHorizLineTarget(float t);

float changeSlopeTarget(float t);

float changeSlopeAndMoveTarget(float t);

float moveParabolsLeftTarget(float t);

float moveParabolaUpTarget(float t);

float invertParabolaTarget(float t);

float widenParabolaTarget(float t);

float widenAndMoveParabolaTarget(float t);

float easeInTarget(float t);

float easeInUpsideDownTarget(float t);

float easeInFlipVertTarget(float t);

float easeOutTarget(float t);

float easeInThruCentreTarget(float t);

float easeOutThruCentreTarget(float t);
