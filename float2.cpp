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
    fp64 c = a * splitter;
    fp64 c_hi = c - (c - a);
    fp64 c_lo = a - c_hi;

    fp32 a_hi = (fp32) c_hi;
    fp32 a_lo = (fp32) c_lo;
    return float2(a_hi, a_lo);
}

float2 float2::split(fp32 a) {
    const fp32 split = (1 << 12) + 1;
    fp32 c = a * split;
    fp32 a_hi = c - (c - a);
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
    fp32 d = a - b;
    fp32 e = (a - d) - b;
    return float2(d, e);
}

float2 float2::twoDiff (fp32 a, fp32 b) {
    fp32 d = a - b;
    fp32 v = d - a;
    fp32 e = (a - (d - v) - (b + v));
    return float2(d, e);
}

float2 float2::twoProd(fp32 a, fp32 b) {
    fp32 p = a * b;
    float2 a_split = split(a);
    float2 b_split = split(b);
    fp32 err = ((a_split.x * b_split.x - p) + a_split.x * b_split.y + a_split.y * b_split.x) + a_split.y * b_split.y;
    return float2(p, err);
}

float2 float2::twoSqr(fp32 a) {
    fp32 p = a * a;
    float2 a_split = split(a);
    fp32 err = ((a_split.x * a_split.x - p) + a_split.x * a_split.y + a_split.y * a_split.x) + a_split.y * a_split.y;
    return float2(p, err);
}

float2 operator+(float2 a, float2 b) {
    float2 s_hi, s_lo;
    s_hi = float2::twoSum(a.x, b.x);
    s_lo = float2::twoSum(a.y, b.y);
    s_hi.y += s_lo.x;
    s_hi = float2::quickTwoSum(s_hi.x, s_hi.y);
    s_hi.y += s_lo.y;
    s_hi = float2::quickTwoSum(s_hi.x, s_hi.y);
    return s_hi;
}

float2 operator-(float2 a, float2 b) {
    float2 d_hi, d_lo;
    d_hi = float2::twoDiff(a.x, b.x);
    d_lo = float2::twoDiff(a.y, b.y);
    d_hi.y += d_lo.x;
    d_hi = float2::quickTwoDiff(d_hi.x, d_hi.y);
    d_hi.y += d_lo.y;
    d_hi = float2::quickTwoDiff(d_hi.x, d_hi.y);
    return d_hi;
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

float2 f2_sqr(float2 a) {
    float2 s;
    s = float2::twoSqr(a.x);
    s.y += a.x * a.y;
    s.y += a.y * a.x;
    s = float2::quickTwoSum(s.x, s.y);
    return s;
}

float2 f2_sqrt(float2 a) {
    fp32 xn = 1 / sqrt(a.x);
    fp32 yn = a.x * xn;
    float2 ynsqr = f2_sqr(yn);
    fp32 diff = (a - ynsqr).x;
    float2 prod = float2::twoProd(xn, diff) / float2(2.0f);
    float2 result = yn + prod;
    return result;
}