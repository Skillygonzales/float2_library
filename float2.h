#ifndef FLOAT2_H
#define FLOAT2_H

#include "types.h"

// definirea clasei float2

class float2 {
private:
    fp32 x;
    fp32 y;

public:
    //constructori
    float2(fp32 _x, fp32 _y);
    float2(fp64 _x);

    // metode de acces la valorile datelor membre ale clasei
    fp32 getX() const;
    fp32 getY() const;

    // functii statice ajutatoare
    static float2 splitDouble(fp64 a);
    static float2 split(fp32 a);
    static fp64 combine(float2 a);
    static float2 twoSum(fp32 a, fp32 b);
    static float2 quickTwoSum(fp32 a, fp32 b);
    static float2 quickTwoDiff(fp32 a, fp32 b);
    static float2 twoDiff(fp32 a, fp32 b);
    static float2 twoProd(fp32 a, fp32 b);
    static float2 twoSqr(fp32 a);

    // supraincarcarea operatorilor + - * /
    friend float2 operator+(float2 a, float2 b);
    friend float2 operator-(float2 a, float2 b);
    friend float2 operator*(float2 a, float2 b);
    friend float2 operator/(float2 b, float2 a);

    /* functii friend pentru operatiile de ridicare la puterea a doua
    si radical de ordinul al doilea */
    friend float2 f2_sqr(float2 a);
    friend float2 f2_sqrt(float2 a);
};

#endif
