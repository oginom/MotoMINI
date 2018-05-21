/*
 * main.cpp
 * created by Masahiro Ogino
 */

#include <iostream>
#include <math.h>
#include <unistd.h>

#include "numogi.h"
//#include "ogiplot.h"
#include "CGnuplot.h"
#include "MotoMINI.h"

using namespace std;

void test() {

    MotoMINI *mm = new MotoMINI();
    transmat T;
    float *ph = mm->mdl->inverseKinematics(T);
    rep(i, 6) cout << ph[i] << " ";
    cout << endl;

    float phi_min[6] = { -170,  -85,    0, -140, -120, -360};
    float phi_max[6] = {  170,   90,  140,  140,  120,  360};
    rep (i, 6) {
        phi_min[i] *= (M_PI/180.0f);
        phi_max[i] *= (M_PI/180.0f);
    }
    Trajectory *t1 = new OginoTrajectory(phi_min, phi_max, 10.0);

    float phi0[6] = {0,0,0,0,0,0};
    float phif[6] = {0,M_PI*0.4,0,0,0,0};
    Trajectory *t2 = new JointSpaceTrajectory(10.0, phi0, phif);

    mm->addTrajectory(t2);

    CGnuplot gplot;
    std::vector<double> vecX, vecY;

    for (int i=0; i<2000; ++i) {
        mm->exec(0.01);

        mm->mdl->setAngles(mm->target);
        mm->mdl->forwardKinematics();
        transmat T = mm->mdl->getTransform();
        vecX.push_back(T.p[X]);
        vecY.push_back(T.p[Z]);
    }

    gplot.Plot(vecX, vecY);

    /*/
    transmat t = transmat();

    t.R = Rot(Z, 1) * Rot(Y, 0.5);
    t.p = vec(50.0, 50.0, 50.0);
    cout << t << endl;
    mm->setTransform(t);
    mm->inverseKinematics();
    float *phis = mm->getAngles();
    for (int i=0; i<6; ++i) {
        cout << phis[i] << endl;
    }

    cout << endl;
    mm->setAngles(phis);
    mm->forwardKinematics();
    transmat t2 = mm->getTransform();
    cout << t2 << endl;
    cout << "error: " << scientific << Tdiff(t, t2) << endl;
    //*/

    /*/
    float phis[6] = {0., 0., 0., 0., 0., 0.};
    for (int i=0; i<6; ++i) {
        mm->setAngle(i, phis[i]);
    }
    mm->forwardKinematics();
    cout << mm->getTransform() << endl;
    //*/

    /*
    for (int i=0; i<6; ++i) {
        for (int p=0; p<360; ++p) {
            mm->setAngle(i, (float)p / 180.0 * M_PI);
            mm->forwardKinematics();
            cout << mm->getTransform() << endl;
            usleep(10 * 1000);
        }
    }
    //*/
}

void plot_test() {
    /*
    plotopen();
    double x[628];
    double y[628];
    double z[628];
    for (int t=0; t<100; ++t) {
        for (int i=0; i<628; ++i) {
            double xi = i / 100.0;
            double yi = sin(xi + t * 0.01);
            double zi = cos(xi + t * 0.01);
            x[i] = xi;
            y[i] = yi;
            z[i] = zi;
        }
        plot3Dstart(1);
        plotXYZ(x, y, z, 628);
        plotend();
        sleep(1);
    }
    */
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

