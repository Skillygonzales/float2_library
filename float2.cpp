#include "float2.h"
#include "types.h"
#include <cmath>

float2::float2(fp32 _x = 0, fp32 _y = 0) {
    x = _x;
    y = _y;
}

float2::float2(fp64 _x) {
    float2 result = splitDouble(_x);
    x = result.x;
    y = result.y;
}

fp32 float2::getX() const { return x; }
fp32 float2::getY() const { return y; }

float2 float2::splitDouble(fp64 a) {
    const double splitter = (1 << 29) + 1;
    fp64 t = a * splitter;
    fp64 t_hi = t - (t - a);
    fp64 t_lo = a - t_hi;

    fp32 a_hi = (fp32) t_hi;
    fp32 a_lo = (fp32) t_lo;
    return float2(a_hi, a_lo);
}

float2 float2::split(fp32 a) {
    const fp32 split = 4097;
    fp32 t = a * split;
    fp32 a_hi = t - (t-a);
    fp32 a_lo = a - a_hi;
    return float2(a_hi, a_lo);
}

fp64 float2::combine(float2 a) {
    fp64 result = a.x;
    result = result + a.y;
    return result;
}

float2 float2::twoSum(fp32 a, fp32 b) {
    fp32 s = a + b;
    fp32 v = s - a;
    fp32 e = (a - (s - v)) + (b - v);
    return float2(s, e);
}

float2 float2::quickTwoSum(fp32 a, fp32 b) {
    fp32 s = a + b;
    fp32 e = b - (s - a);
    return float2(s, e);
}

float2 float2::quickTwoDiff(fp32 a, fp32 b) {
    fp32 s = a - b;
    fp32 e = (a - s) - b;
    return float2(s, e);
}

float2 float2::twoDiff (fp32 a, fp32 b) {
    fp32 s = a - b;
    fp32 v = s - a;
    fp32 e = (a - (s - v) - (b + v));
    return float2(s, e);
}

float2 float2::twoProd(fp32 a, fp32 b) {
    fp32 p = a * b;
    float2 aS = split(a);
    float2 bS = split(b);
    fp32 err = ((aS.x * bS.x - p) + aS.x * bS.y + aS.y * bS.x) + aS.y * bS.y;
    return float2(p, err);
}

float2 operator+(float2 a, float2 b) {
    float2 s, t;
    s = float2::twoSum(a.x, b.x);
    t = float2::twoSum(a.y, b.y);
    s.y += t.x;
    s = float2::quickTwoSum(s.x, s.y);
    s.y += t.y;
    s = float2::quickTwoSum(s.x, s.y);
    return s;
}

float2 operator-(float2 a, float2 b) {
    float2 s, t;
    s = float2::twoDiff(a.x, b.x);
    t = float2::twoDiff(a.y, b.y);
    s.y += t.x;
    s = float2::quickTwoDiff(s.x, s.y);
    s.y += t.y;
    s = float2::quickTwoDiff(s.x, s.y);
    return s;
}

float2 operator*(float2 a, float2 b) {
    float2 p;
    p = float2::twoProd(a.x, b.x);
    p.y += a.x * b.y;
    p.y += a.y * b.x;
    p = float2::quickTwoSum(p.x, p.y);
    return p;
}

float2 operator/(float2 b, float2 a) {
    fp32 xn = 1.0f / a.x;
    fp32 yn = b.x * xn;
    fp32 diff = (b - (a * float2(yn))).x;
    float2 prod = float2::twoProd(xn, diff);
    float2 result = yn + prod;
    return result;
}