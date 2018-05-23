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
    transmat T;
    float ph[6];
    mm->mdl->inverseKinematics(T, ph);
    cout << ph << endl;

    float phi_min[6] = { -170,  -85,    0, -140, -120, -360};
    float phi_max[6] = {  170,   90,  140,  140,  120,  360};
    rep (i, 6) {
        phi_min[i] *= (M_PI/180.0f);
        phi_max[i] *= (M_PI/180.0f);
    }
    Trajectory *t1 = new OginoTrajectory(phi_min, phi_max, 10.0);

    float phi0[6] = {M_PI*-0.2,0,0,0,0,0};
    float phif[6] = {M_PI*0.2,M_PI*0.4,0,0,0,0};
    Trajectory *t2 = new JointSpaceTrajectory(10.0, phi0, phif);

    /*
    transmat T0 = transmat();
    T0.R = Rot(Z, 1) * Rot(Y, 0.5);
    T0.p = vec(50.0, 50.0, 50.0);
    transmat Tf = transmat();
    Tf.R = Rot(Z, 1) * Rot(Y, 0.5);
    Tf.p = vec(50.0, -50.0, 50.0);
    Trajectory *t3 = new JointSpaceTrajectory(10.0, mm->mdl, T0, Tf);
    */

    transmat T0 = transmat();
    T0.R = Rot(Z, 1) * Rot(Y, 0.5);
    T0.p = vec(50.0, 50.0, 50.0);
    point pf = vec(100.0, -100.0, 100.0);
    Trajectory *t4 = new LineTrajectory(10.0, mm->mdl, T0, pf);

    mm->addTrajectory(t4);

    transmat T00 = transmat();
    T00.R = Rot(Z, 1) * Rot(Y, 0.5);
    T00.p = vec(100.0, -100.0, 100.0);
    point pf0 = vec(50.0, 50.0, 50.0);
    Trajectory *t5 = new LineTrajectory(10.0, mm->mdl, T00, pf0);

    //mm->addTrajectory(t5);

    CGnuplot gplot;
    std::vector<double> vecX;
    std::vector<double> vecYs[6];

    float t = 0;
    for (int i=0; i<2000; ++i) {
        t += 0.01;
        mm->exec(0.01);

        mm->mdl->setAngles(mm->target);
        mm->mdl->forwardKinematics();
        transmat T = mm->mdl->getTransform();
        vecX.push_back(t);
        rep (i, 6) {
            vecYs[i].push_back(mm->target[i]);
        }
    }

    gplot.SetXLabel("t (s)");
    gplot.SetYLabel("phi (rad)");
    gplot.PlotN(vecX, vecYs, CGnuplot::PLOT_TYPE_OUTPUT);

}

void plot_test() {
    CGnuplot gplot;
    std::vector<double> vecX, vecY;
    for (int i=0; i<100; i++) {
        double x = (double)i/100;
        double y = (x-0.25)*(x-0.5)*(x-0.75);
        vecX.push_back(x);
        vecY.push_back(y);
    }
    //gplot.Command("set xrange[0:%f]", vecX[99]); // printfライクにコマンドが打てます
    //gplot.Command("set yrange[0:%f]", vecY[99]);
    gplot.Plot(vecX, vecY);  // 配列でもコンテナでもプロットできます（まだ1次元と2次元のみ）
}

int main(int argc, char** argv) {
    cout << "Hell Ogino World" << endl;

    //numogi_sample();
    //plot_test();
    test();

    return 0;
}

