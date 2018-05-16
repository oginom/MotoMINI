
#ifndef _NUMOGI_H_
#define _NUMOGI_H_
#include <iostream>
#include <iomanip>
using namespace std;

#define rep(i,N) for(int i=0; i<N; ++i)
#define rep3(i) rep(i,3)

float pow2(float x);

//########## vector3<T> ##########

template <typename T>
struct vector3 {
    T value[3];
    vector3() : value() {}
    vector3(T x, T y, T z) {
        value[0] = x;
        value[1] = y;
        value[2] = z;
    }
    vector3(const vector3& v) {
        rep3(i) value[i] = v.value[i];
    }
    vector3& operator += (const vector3& v){
        rep3(i) value[i] += v.value[i];
        return *this;
    }
    vector3& operator -= (const vector3& v){
        rep3(i) value[i] -= v.value[i];
        return *this;
    }
    vector3& operator *= (T l){
        rep3(i) value[i] *= l;
        return *this;
    }
    vector3& operator /= (T l){
        rep3(i) value[i] /= l;
        return *this;
    }
    vector3 operator + (const vector3& v)const{ return vector3(*this) += v;}
    vector3 operator - (const vector3& v)const{ return vector3(*this) -= v;}
    vector3 operator * (T l)const{ return vector3(*this) *= l;}
    vector3 operator / (T l)const{ return vector3(*this) /= l;}
    T &operator[](int index) {
        return value[index];
    }
};

template <typename T>
istream& operator >> (istream& i, vector3<T>& v){
    i >> v.value[0] >> v.value[1] >> v.value[2];
    return i;
}

template <typename T>
ostream& operator << (ostream& o, const vector3<T>& v){
    o << fixed << setprecision(8);
    o << "[" << v.value[0] << "\t" << v.value[1] << "\t" << v.value[2] << "]";
    return o;
}

typedef vector3<float> vector3f;

//########## matrix33f  ##########

//typedef float matrix33f[3][3];
template <typename T>
struct matrix33 {
    T elements[3][3];
    matrix33() : elements() {
        elements[0][0] = elements[1][1] = elements[2][2] = 1;
    }
    matrix33(const matrix33& M) {
        rep3(i) rep3(j) elements[i][j] = M.elements[i][j];
    }
    T* operator[](int index) {
        return elements[index];
    }
    template <typename T2>
    matrix33& operator *= (matrix33<T2> M){
        T newelements[3][3] = {};
        rep3(i) rep3(j) rep3(k) {
            newelements[i][j] += elements[i][k] * M.elements[k][j];
        }
        rep3(i) rep3(j) {
            elements[i][j] = newelements[i][j];
        }
        return *this;
    }
    template <typename T2>
    matrix33 operator * (matrix33<T2> M)const{ return matrix33(*this) *= M;}
    //template <typename T2>
    //vector3<T2>& operator *= (vector3<T2> v){ }
    template <typename T2>
    vector3<T2> operator * (vector3<T2> v)const{
        vector3<T2> ret = vector3<T2>();
        rep3(i) rep3(j) {
            ret[i] += elements[i][j] * v[j];
        }
        return ret;
    }
};

template <typename T>
ostream& operator << (ostream& o, const matrix33<T>& m) {
    o << fixed << setprecision(8);
    for (int i=0; i<3; ++i) {
        for (int j=0; j<3; ++j) {
            o << m.elements[i][j] << "\t";
        }
        o << endl;
    }
    return o;
}

typedef matrix33<float> matrix33f;

//##########    Axis    ##########

enum Axis {
    X = 0,
    Y = 1,
    Z = 2
};

//##########            ##########

typedef matrix33f rotation;
//struct rotation : public matrix33f {};

rotation Rot(Axis ax, float theta);

typedef vector3f vec;
typedef vec point;
typedef vec velo;

struct transmat {
    rotation R;
    point p;
    transmat() : R(), p() {}
    transmat(const transmat& T) {
        R = rotation(T.R);
        p = point(T.p);
    }
    transmat& operator *= (transmat T){
        p = R * T.p + p;
        R *= T.R;
        return *this;
    }
    transmat operator * (transmat T)const{ return transmat(*this) *= T;}
};

static ostream& operator << (ostream& o, const transmat& T){
    o << fixed << setprecision(8);
    for (int i=0; i<3; ++i) {
        for (int j=0; j<3; ++j) {
            o << T.R.elements[i][j] << "\t";
        }
        o << T.p.value[i] << endl;
    }
    return o;
}

void numogi_sample();
#endif //_NUMOGI_H_

