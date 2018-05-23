/*
 * main.cpp
 * created by Masahiro Ogino
 */

#include <iostream>
#include <math.h>
#include <unistd.h>

#include "numogi.h"
#include "CGnuplot.h"
#include "MotoMINI.h"

using namespace std;

void test() {

    MotoMINI *mm = new MotoMINI();

    /*
    transmat T = transmat();
    float ph[6];
    mm->mdl->inverseKinematics(T, ph);
    cout << ph << endl;
    */

    /*
    float phi_min[6] = { -170,  -85,    0, -140, -120, -360};
    float phi_max[6] = {  170,   90,  140,  140,  120,  360};
    rep (i, 6) {
        phi_min[i] *= (M_PI/180.0f);
        phi_max[i] *= (M_PI/180.0f);
    }
    Trajectory *t1 = new OginoTrajectory(phi_min, phi_max, 10.0);
    */

    /*
    float phi0[6] = {M_PI*-0.2,0,0,0,0,0};
    float phif[6] = {M_PI*0.2,M_PI*0.4,0,0,0,0};
    Trajectory *t2 = new JointSpaceTrajectory(10.0, phi0, phif);
    */

    /*
    transmat T0 = transmat();
    T0.R = Rot(Z, 1) * Rot(Y, 0.5);
    T0.p = vec(50.0, 50.0, 50.0);
    transmat Tf = transmat();
    Tf.R = Rot(Z, 1) * Rot(Y, 0.5);
    Tf.p = vec(50.0, -50.0, 50.0);
    Trajectory *t3 = new JointSpaceTrajectory(10.0, mm->mdl, T0, Tf);
    */

    /*
    transmat T0 = transmat();
    T0.R = Rot(Z, 1) * Rot(Y, 0.5);
    T0.p = vec(50.0, 50.0, 50.0);
    point pf = vec(100.0, -100.0, 100.0);
    Trajectory *t4 = new LineTrajectory(10.0, mm->mdl, T0, pf);
    */

    rotation R = Rot(Z, 1) * Rot(Y, 0.5);
    point centerp = vec(100.0, 50.0, 100.0);
    point cosvec = vec(0.0, 10.0, 0.0);
    point sinvec = vec(0.0, 0.0, 10.0);
    float angle0 = -M_PI * 0.5;
    float anglef = M_PI * 1.5;
    Trajectory *t5 = new CircleTrajectory(10.0, mm->mdl, R, centerp,
        cosvec, sinvec, angle0, anglef);

    mm->addTrajectory(t5);

    CGnuplot gplot;
    std::vector<double> vecX;
    std::vector<double> vecYs[6];
    std::vector<double> vecTs[6];

    float t = 0;
    for (int i=0; i<1000; ++i) {
        t += 0.01;
        mm->exec(0.01);

        vecX.push_back(t);

        mm->mdl->setAngles(mm->target);
        mm->mdl->forwardKinematics();
        transmat T = mm->mdl->getTransform();
        rep (i, 3) { vecTs[i].push_back(T.p[i]); }
        rep (i, 3) { vecTs[i+3].push_back(T.R[i][2] * (180/M_PI)); }

        rep (i, 6) { vecYs[i].push_back(mm->target[i]); }
    }

    // print 3D Target Trajectory
    //gplot.SetXLabel("x");
    //gplot.SetYLabel("y");
    //gplot.SetZLabel("z");
    //gplot.SetXRange(90, 110);
    //gplot.PlotXYZ(vecTs[0], vecTs[1], vecTs[2]);

    // print joint angles
    //gplot.SetXLabel("t (s)");
    //gplot.SetYLabel("phi (rad)");
    //gplot.PlotN(vecX, vecYs, CGnuplot::PLOT_TYPE_OUTPUT);

    // print wrist frame
    gplot.SetXLabel("t (s)");
    gplot.SetYLabel("T.p, T.R[:,3]");
    gplot.PlotN(vecX, vecTs, CGnuplot::PLOT_TYPE_OUTPUT);

}

void plot_test() {
    CGnuplot gplot;
    std::vector<float> vecX, vecYs[3];
    for (int i=0; i<100; i++) {
        float x = (float)i/100;
        float y0 = x * x + 1;
        float y1 = x * (1 - x);
        float y2 = 2 - 2 * x;
        vecX.push_back(x);
        vecYs[0].push_back(y0);
        vecYs[1].push_back(y1);
        vecYs[2].push_back(y2);
    }
    //gplot.PlotN(vecX, vecYs);
    gplot.PlotXYZ(vecYs[0], vecYs[1], vecYs[2]);
}

int main(int argc, char** argv) {
    cout << "Hell Ogino World" << endl;

    //numogi_sample();
    plot_test();
    //test();

    return 0;
}

