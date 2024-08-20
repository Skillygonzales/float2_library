#include "float2.h"
#include "types.h"
#include <cmath>

float2::float2(fp64 _x = 0, fp64 _y = 0) {
    x = _x;
    y = _y;
}

float2::float2(fp128 _x) {
    float2 result = splitDouble(_x);
    x = result.x;
    y = result.y;
}

fp64 float2::getX() const { return x; }
fp64 float2::getY() const { return y; }

float2 float2::splitDouble(fp128 a) {
    const fp128 splitter = (1 << 66) + 1;
    fp128 t = a * splitter;
    fp128 t_hi = t - (t - a);
    fp128 t_lo = a - t_hi;

    fp64 a_hi = (fp64) t_hi;
    fp64 a_lo = (fp64) t_lo;
    return float2(a_hi, a_lo);
}

float2 float2::split(fp64 a) {
    const fp64 split = (1 << 29) + 1;
    fp64 t = a * split;
    fp64 a_hi = t - (t-a);
    fp64 a_lo = a - a_hi;
    return float2(a_hi, a_lo);
}

fp128 float2::combine(float2 a) {
    fp128 result = a.x;
    result = result + a.y;
    return result;
}

float2 float2::twoSum(fp64 a, fp64 b) {
    fp64 s = a + b;
    fp64 v = s - a;
    fp64 e = (a - (s - v)) + (b - v);
    return float2(s, e);
}

float2 float2::quickTwoSum(fp64 a, fp64 b) {
    fp64 s = a + b;
    fp64 e = b - (s - a);
    return float2(s, e);
}

float2 float2::quickTwoDiff(fp64 a, fp64 b) {
    fp64 s = a - b;
    fp64 e = (a - s) - b;
    return float2(s, e);
}

float2 float2::twoDiff (fp64 a, fp64 b) {
    fp64 s = a - b;
    fp64 v = s - a;
    fp64 e = (a - (s - v) - (b + v));
    return float2(s, e);
}

float2 float2::twoProd(fp64 a, fp64 b) {
    fp64 p = a * b;
    float2 aS = split(a);
    float2 bS = split(b);
    fp64 err = ((aS.x * bS.x - p) + aS.x * bS.y + aS.y * bS.x) + aS.y * bS.y;
    return float2(p, err);
}

float2 float2::twoSqr(fp64 a) {
    fp64 p = a * a;
    float2 aS = split(a);
    fp64 err = ((aS.x * aS.x - p) + aS.x * aS.y + aS.y * aS.x) + aS.y * aS.y;
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
    fp64 xn = 1.0f / a.x;
    fp64 yn = b.x * xn;
    fp64 diff = (b - (a * float2(yn))).x;
    float2 prod = float2::twoProd(xn, diff);
    float2 result = yn + prod;
    return result;
}

float2 f2_sqr(float2 a) {
    float2 p;
    p = float2::twoSqr(a.x);
    p.y += a.x * a.y;
    p.y += a.y * a.x;
    p = float2::quickTwoSum(p.x, p.y);
    return p;
}

float2 f2_sqrt(float2 a) {
    fp64 xn = 1 / sqrt(a.x);
    fp64 yn = a.x * xn;
    float2 ynsqr = f2_sqr(yn);
    fp64 diff = (a - ynsqr).x;
    float2 prod = float2::twoProd(xn, diff) / float2(2.0f);
    float2 result = yn + prod;
    return result;
}