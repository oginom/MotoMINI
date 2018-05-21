/*
 * numogi.h
 */

#include "numogi.h"

#include <math.h>

float pow2(float x){ return x * x;}

rotation Rot(Axis ax, float theta) {
    rotation ret = rotation();
    float s = sin(theta);
    float c = cos(theta);
    switch (ax) {
        case X:
            ret[1][1] = ret[2][2] = c;
            ret[1][2] = -s;
            ret[2][1] = s;
            break;
        case Y:
            ret[2][2] = ret[0][0] = c;
            ret[2][0] = -s;
            ret[0][2] = s;
            break;
        case Z:
            ret[0][0] = ret[1][1] = c;
            ret[0][1] = -s;
            ret[1][0] = s;
            break;
        default:
            cerr << "BAD AXIS FOR Rot()." << endl;
            break;
    }
    return ret;
}

#include <iostream>
void numogi_sample() {
    cout << "numogi_sample" << endl;
    rotation r = Rot(Z, M_PI_2);
    std::cout << r << std::endl;
    transmat t = transmat();
    std::cout << t << std::endl;
}

