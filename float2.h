#ifndef FLOAT2_H
#define FLOAT2_H

#include "types.h"

class float2 {
private:
    fp32 x;
    fp32 y;

public:
    float2(fp32 _x, fp32 _y);
    float2(fp64 _x);

    fp32 getX() const;
    fp32 getY() const;

    static float2 splitDouble(fp64 a);
    static float2 split(fp32 a);
    static fp64 combine(float2 a);
    static float2 twoSum(fp32 a, fp32 b);
    static float2 quickTwoSum(fp32 a, fp32 b);
    static float2 quickTwoDiff(fp32 a, fp32 b);
    static float2 twoDiff(fp32 a, fp32 b);
    static float2 twoProd(fp32 a, fp32 b);
    static float2 twoSqr(fp32 a);

    friend float2 operator+(float2 a, float2 b);
    friend float2 operator-(float2 a, float2 b);
    friend float2 operator*(float2 a, float2 b);
    friend float2 operator/(float2 b, float2 a);
    friend float2 f2_sqr(float2 a);
    friend float2 f2_sqrt(float2 a);
};

#endif
