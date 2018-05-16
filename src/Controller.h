/*
 * Controller.h
 */

#pragma once

#include "numogi.h"
#include "Trajectory.h"

class Controller {
public:
    Trajectory* t;
    virtual void exec(float dt, float *observed, float *target) { return; }
};

class PDController : public Controller {
public:
    int d;
    PDController();
    void exec(float dt, float *observed, float *target);
};

