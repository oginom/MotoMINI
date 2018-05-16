/*
 * RobotModel.cpp
 */

#include "RobotModel.h"
#include <math.h>

MotoMINIModel::MotoMINIModel() : phi(), Tj(), T() {
    std::cout << "MotoMINIModel constructor" << std::endl;
    isPrintT = false;

    Tj[1].p[X] = 20;
    Tj[2].p[X] = 165;
    Tj[3].p[Y] = -165;

    for (int i=0; i<6; ++i) {
        setAngle(i, 0);
    }
}

void MotoMINIModel::setAngle(int i, float angle) {
    phi[i] = angle;
    rotation Ri = rotation();
    float si = sin(angle);
    float ci = cos(angle);
    switch (i) {
        case 0:
            Ri[0][0] = Ri[1][1] = ci;
            Ri[0][1] = -si;
            Ri[1][0] = si;
            break;
        case 1:
            Ri[0][1] = Ri[2][0] = ci;
            Ri[0][0] = si;
            Ri[2][1] = -si;
            Ri[1][1] = Ri[2][2] = 0;
            Ri[1][2] = 1;
            break;
        case 2:
            Ri[0][0] = Ri[1][1] = -si;
            Ri[0][1] = -ci;
            Ri[1][0] = ci;
            break;
        case 3:
        case 5:
            Ri[0][0] = Ri[2][1] = ci;
            Ri[0][1] = -si;
            Ri[2][0] = si;
            Ri[1][1] = Ri[2][2] = 0;
            Ri[1][2] = -1;
            break;
        case 4:
            Ri[0][1] = Ri[2][0] = -si;
            Ri[0][0] = ci;
            Ri[2][1] = -ci;
            Ri[1][1] = Ri[2][2] = 0;
            Ri[1][2] = 1;
            break;
        default:
            std::cerr << "JOINT " << i << " doesn't exist" << std::endl;
    }
    Tj[i].R = Ri;
}
void MotoMINIModel::setAngles(float *angles) {
    for (int i=0; i<6; ++i) {
        setAngle(i, angles[i]);
    }
}

bool MotoMINIModel::forwardKinematics() {
    T = transmat();
    for (int i=0; i<6; ++i) {
        if (isPrintT) std::cout << Tj[i] << std::endl;
        T *= Tj[i];
    }
    return true;
}

float *MotoMINIModel::inverseKinematics(transmat T) {
    static const float a0 = 20;
    static const float a1 = 165;
    static const float d3 = 165;

    phi[0] = atan2(T.p[Y], T.p[X]);

    float c0 = cos(phi[0]);
    float s0 = sin(phi[0]);

    // plus or minus
    phi[2] = acos((
        pow2(c0 * T.p[X] + s0 * T.p[Y] - a0) +
        pow2(T.p[Z]) -
        pow2(a1) -
        pow2(d3)
    )/(
        2 * a1 * d3
    ));

    float c2 = cos(phi[2]);
    float s2 = sin(phi[2]);

    phi[1]=
    atan2(
    a1*s2*T.p[Z]+(c0*T.p[X]+s0*T.p[Y]-a0)*(a1*c2+d3),
    (a1*c2+d3)*T.p[Z]-a1*s2*(c0*T.p[X]+s0*T.p[Y]-a0)
    )-phi[2];

    float c12 = cos(phi[1]+phi[2]);
    float s12 = sin(phi[1]+phi[2]);

    phi[3]=atan2(
    -T.R[0][2]*s0+T.R[1][2]*c0,
    T.R[0][2]*c0*c12+T.R[1][2]*s0*c12-T.R[2][2]*s12
    );

    float c3 = cos(phi[3]);
    float s3 = sin(phi[3]);

    phi[4]=atan2(
    T.R[0][2]*(c0*c12*c3 - s0*s3)+
    T.R[1][2]*(s0*c12*c3 + c0*s3)+
    T.R[2][2]*(-s12*c3)
    ,
    T.R[0][2]*(c0*s12)+
    T.R[1][2]*(s0*s12)+
    T.R[2][2]*(c12)
    );

    float c4 = cos(phi[4]);
    float s4 = sin(phi[4]);

    phi[5]=atan2(
    -T.R[0][0]*(c0*c12*s3 + s0*c3)
    -T.R[1][0]*(s0*c12*s3 - c0*c3)
    +T.R[2][0]*s12*s3
    ,
    T.R[0][0]*((c0*c12*c3 - s0*s3)*c4-c0*s12*s4)+
    T.R[1][0]*((s0*c12*c3 + c0*s3)*c4-s0*s12*s4)+
    T.R[2][0]*(-s12*c3*c4-c12*s4)
    );

    return phi;
}

void MotoMINIModel::exec(float dt) {
}


