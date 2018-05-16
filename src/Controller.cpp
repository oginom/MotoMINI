
#include "Controller.h"

PDController::PDController() {
    d = 6;
}

void PDController::exec(float dt, float *observed, float *target) {
    rep(i, d) {
        std::cout << observed[i] << " " << target[i] << std::endl;
    }
}
