/*
 * RobotModel.h
 */

#pragma once

#include <iostream>
#include <vector>
#include "numogi.h"

class RobotModel {
public:
    virtual float *inverseKinematics(transmat T) {
        return NULL;
    }
};

class MotoMINIModel : public RobotModel {
private:
public:
    float phi[6];
    transmat Tj[6];
    transmat T;

public:
    bool isPrintT;

    MotoMINIModel();

    // phi SETTER/GETTER
    void setAngle(int i, float angle);
    float getAngle(int i) { return phi[i]; }
    void setAngles(float *angles);
    float *getAngles() { return phi; }

    // T SETTER/GETTER
    void setTransform(transmat tra) { T = tra; }
    transmat getTransform() { return T; }

    bool forwardKinematics();

    float *inverseKinematics(transmat T);

    void exec(float dt);

};

