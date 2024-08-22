#ifndef FLOAT2_H
#define FLOAT2_H

#include "types.h"

class float2 {
private:
    fp64 x;
    fp64 y;

public:
    float2(fp64 _x, fp64 _y);
    float2(fp128 _x);

    fp64 getX() const;
    fp64 getY() const;

    static float2 splitDouble(fp128 a);
    static float2 split(fp64 a);
    static fp128 combine(float2 a);
    static float2 twoSum(fp64 a, fp64 b);
    static float2 quickTwoSum(fp64 a, fp64 b);
    static float2 quickTwoDiff(fp64 a, fp64 b);
    static float2 twoDiff(fp64 a, fp64 b);
    static float2 twoProd(fp64 a, fp64 b);
    static float2 twoSqr(fp64 a);

    friend float2 operator+(float2 a, float2 b);
    friend float2 operator-(float2 a, float2 b);
    friend float2 operator*(float2 a, float2 b);
    friend float2 operator/(float2 b, float2 a);
    friend float2 f2_sqr(float2 a);
    friend float2 f2_sqrt(float2 a);
};

#endif
