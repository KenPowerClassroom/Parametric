/*==============================================================================
 Note to Students:
 Each method in this file corresponds to one of the green curves
 plotted in the application main screen

 Your task is to modify each method so that the green curve matches 
 the grey (thicker) curve.
 
 Don't add new methods or remove any existing methods 

 Tackle these one at a time, get each one working before moving on to the next.


███    ███  ██████  ██████  ██ ███████ ██    ██     ███    ███ ███████ ████████ ██   ██  ██████  ██████      ██████   ██████  ██████  ██ ███████ ███████
████  ████ ██    ██ ██   ██ ██ ██       ██  ██      ████  ████ ██         ██    ██   ██ ██    ██ ██   ██     ██   ██ ██    ██ ██   ██ ██ ██      ██
██ ████ ██ ██    ██ ██   ██ ██ █████     ████       ██ ████ ██ █████      ██    ███████ ██    ██ ██   ██     ██████  ██    ██ ██   ██ ██ █████   ███████
██  ██  ██ ██    ██ ██   ██ ██ ██         ██        ██  ██  ██ ██         ██    ██   ██ ██    ██ ██   ██     ██   ██ ██    ██ ██   ██ ██ ██           ██
██      ██  ██████  ██████  ██ ██         ██        ██      ██ ███████    ██    ██   ██  ██████  ██████      ██████   ██████  ██████  ██ ███████ ███████ ▄█


██████  ██    ██ ████████     ██████   ██████      ███    ██  ██████  ████████      █████  ██████  ██████      ███    ██ ███████ ██     ██      ██████  ██████      ██████  ███████ ███    ███  ██████  ██    ██ ███████
██   ██ ██    ██    ██        ██   ██ ██    ██     ████   ██ ██    ██    ██        ██   ██ ██   ██ ██   ██     ████   ██ ██      ██     ██     ██    ██ ██   ██     ██   ██ ██      ████  ████ ██    ██ ██    ██ ██
██████  ██    ██    ██        ██   ██ ██    ██     ██ ██  ██ ██    ██    ██        ███████ ██   ██ ██   ██     ██ ██  ██ █████   ██  █  ██     ██    ██ ██████      ██████  █████   ██ ████ ██ ██    ██ ██    ██ █████
██   ██ ██    ██    ██        ██   ██ ██    ██     ██  ██ ██ ██    ██    ██        ██   ██ ██   ██ ██   ██     ██  ██ ██ ██      ██ ███ ██     ██    ██ ██   ██     ██   ██ ██      ██  ██  ██ ██    ██  ██  ██  ██
██████   ██████     ██        ██████   ██████      ██   ████  ██████     ██        ██   ██ ██████  ██████      ██   ████ ███████  ███ ███       ██████  ██   ██     ██   ██ ███████ ██      ██  ██████    ████   ███████


███████ ██   ██ ██ ███████ ████████ ██ ███    ██  ██████      ███    ███ ███████ ████████ ██   ██  ██████  ██████  ███████
██       ██ ██  ██ ██         ██    ██ ████   ██ ██           ████  ████ ██         ██    ██   ██ ██    ██ ██   ██ ██
█████     ███   ██ ███████    ██    ██ ██ ██  ██ ██   ███     ██ ████ ██ █████      ██    ███████ ██    ██ ██   ██ ███████
██       ██ ██  ██      ██    ██    ██ ██  ██ ██ ██    ██     ██  ██  ██ ██         ██    ██   ██ ██    ██ ██   ██      ██
███████ ██   ██ ██ ███████    ██    ██ ██   ████  ██████      ██      ██ ███████    ██    ██   ██  ██████  ██████  ███████

==============================================================================*/

#pragma once
#include"TargetFunctions.h"

float moveHorizLine(float t) { 
    return 0.3f; // <= Modify this line
}

float changeSlope(float t) { 
    return t; // <= Modify this line
}

float changeSlopeAndMove(float t) { 
    return t; // <= Modify this line
}

float makeParabolic(float t) {
    return t;// <= Modify this line
}

float moveParabolaLeft(float t) { 
    //sqr(t) is same as t*t 
    return sqr(t);   // <= Modify this line
}  

float moveParabolaUp(float t) { 
    return sqr(t - 0.5);  // <= Modify this line
}

float invertParabola(float t) { 
    return sqr(t - 0.5); // <= Modify this line
}

float narrowParabola(float t) { 
    return sqr(t - 0.5);  // <= Modify this line
}

float widenAndMoveParabola(float t) { 
    return  4 * sqr(t - 0.5);  // <= Modify this line
}

float moveCubicLeft(float t) { 
    return  13 * cub(t) - 10 * sqr(t) + 1;  // <= Modify this line
}

float moveCubicDown(float t) { 
    return  13*cub(t) -10 * sqr(t) + 1 ;  // <= Modify this line
}

float easeIn(float t) { 
    return t;   // <= Modify this line
}

float easeInUpsideDown(float t) { 
    return t;  // <= Modify this line
}

float easeInFlipLeftRight(float t) {
    return t; // <= Modify this line
}

float easeOut(float t) { 
    return t;  // <= Modify this line
}

float easeInThruCentre(float t) { 
    return t;  // <= Modify this line
}

float easeOutThruCentre(float t) { 
    return t;  // <= Modify this line
}

float easeInOut(float t) { 
    // Modify this function
    if (t < 0.5)
        return t;
    else
        return 0.5;
}

float easeInCubic(float t) {
    // Modify this function

    return t * t;
}

float easeInCubicThruCenter(float t) {
    // Modify this function

    return t * t;
}

float easeInOutCubic(float t) {
    // Modify this function

    return t;
}

sf::Vector2f doughnut(float t) {

    //0 <= t <= 2PI
    sf::Vector2f r;
    r.x = 1.5 * cos(t) + -cos(30 * t);
    r.y = 1.5 * sin(t) + -sin(30 * t);
 
    return r;
}

sf::Vector2f cartoid(float t) {

    //0 <= t <= 2PI
    sf::Vector2f r;
    r.x = 0.5 * cos(t) + -0.25 * cos(2 * t);
    r.y = 0.5 * sin(t) + -0.25 * sin(2 * t);

    return r;
}

sf::Vector2f XXXXXX(float t) {

    //0 <= t <= 2PI
    sf::Vector2f r;
    r.x = t + 2 * cos(2 * t);
    r.y = t + 2 * sin(5 * t);

    return r;
}

/*
      ____
   .d""  ""b.        `7MMF' `YMM'                        `7MM"""Mq.
 .P'  ,..., `W,        MM   .M'                            MM   `MM.
6' ,MP   YM   `b       MM .d"     .gP"Ya `7MMpMMMb.        MM   ,M9 ,pW"Wq.`7M'    ,A    `MF'.gP"Ya `7Mb,od8      pd*"*b.  ,pP""Yq.   pd*"*b.  pd""b.
M  MP     `    M       MMMMM.    ,M'   Yb  MM    MM        MMmmdM9 6W'   `Wb VA   ,VAA   ,V ,M'   Yb  MM' "'     (O)   j8 6W'    `Wb (O)   j8 (O)  `8b
M  Mb          M       MM  VMA   8M""""""  MM    MM        MM      8M     M8  VA ,V  VA ,V  8M""""""  MM             ,;j9 8M      M8     ,;j9      ,89
Y. `Wbm..."   ,9       MM   `MM. YM.    ,  MM    MM        MM      YA.   ,A9   VVV    VVV   YM.    ,  MM          ,-='    YA.    ,A9  ,-='       ""Yb.
 Yb.  ``''  .d'      .JMML.   MMb.`Mbmmd'.JMML  JMML.    .JMML.     `Ybmd9'     W      W     `Mbmmd'.JMML.       Ammmmmmm  `Ybmmd9'  Ammmmmmm       88
   `Ybq__pdP'                                                                                                                                 (O)  .M'
                                                                                                                                               bmmmd'
*/