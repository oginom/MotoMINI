/*
 * RobotModel.h
 */

#pragma once

#include <iostream>
#include <vector>
#include "numogi.h"

class RobotModel {
public:
    virtual void setAngle(int i, float angle) {}
    virtual float getAngle(int i) { return 0; }
    virtual void setAngles(float *angles) {}
    virtual float *getAngles() { return NULL; }
    virtual void setTransform(transmat tra) {}
    virtual transmat getTransform() { return transmat(); }
    virtual bool forwardKinematics() { return false; }
    virtual bool inverseKinematics(transmat T, float *phi) { return false; }
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

    bool inverseKinematics(transmat T, float *phi);

    void exec(float dt);

};

