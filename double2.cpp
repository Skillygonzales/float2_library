#include "double2.h"
#include "types.h"
#include <cmath>

// implementarea metodelor din fisierul de tip header double2.h

double2::double2(fp64 _x = 0, fp64 _y = 0) {
    x = _x;
    y = _y;
}

double2::double2(fp128 _x) {
    double2 result = split_fp128(_x);
    x = result.x;
    y = result.y;
}

fp64 double2::getX() const { return x; }
fp64 double2::getY() const { return y; }

double2 double2::split_fp128(fp128 a) {
    const fp128 splitter = (__int128_t(1) << 60) + 1;
    fp128 c = a * splitter;
    fp128 c_hi = c - (c - a);
    fp128 c_lo = a - c_hi;

    fp64 a_hi = (fp64) c_hi;
    fp64 a_lo = (fp64) c_lo;
    return double2(a_hi, a_lo);
}

double2 double2::split(fp64 a) {
    const fp64 split = (1 << 29) + 1;
    fp64 c = a * split;
    fp64 a_hi = c - (c - a);
    fp64 a_lo = a - a_hi;
    return double2(a_hi, a_lo);
}

fp128 double2::combine(double2 a) {
    fp128 result = a.x;
    result = result + a.y;
    return result;
}

double2 double2::twoSum(fp64 a, fp64 b) {
    fp64 s = a + b;
    fp64 v = s - a;
    fp64 e = (a - (s - v)) + (b - v);
    return double2(s, e);
}

double2 double2::quickTwoSum(fp64 a, fp64 b) {
    fp64 s = a + b;
    fp64 e = b - (s - a);
    return double2(s, e);
}

double2 double2::quickTwoDiff(fp64 a, fp64 b) {
    fp64 d = a - b;
    fp64 e = (a - d) - b;
    return double2(d, e);
}

double2 double2::twoDiff (fp64 a, fp64 b) {
    fp64 d = a - b;
    fp64 v = d - a;
    fp64 e = (a - (d - v) - (b + v));
    return double2(d, e);
}

double2 double2::twoProd(fp64 a, fp64 b) {
    fp64 p = a * b;
    double2 a_split = split(a);
    double2 b_split = split(b);
    fp64 err = ((a_split.x * b_split.x - p) + a_split.x * b_split.y + a_split.y * b_split.x) + a_split.y * b_split.y;
    return double2(p, err);
}

double2 double2::twoSqr(fp64 a) {
    fp64 s = a * a;
    double2 a_split = split(a);
    fp64 err = ((a_split.x * a_split.x - s) + a_split.x * a_split.y + a_split.y * a_split.x) + a_split.y * a_split.y;
    return double2(s, err);
}

double2 operator+(double2 a, double2 b) {
    double2 s, t;
    s = double2::twoSum(a.x, b.x);
    t = double2::twoSum(a.y, b.y);
    s.y += t.x;
    s = double2::quickTwoSum(s.x, s.y);
    s.y += t.y;
    s = double2::quickTwoSum(s.x, s.y);
    return s;
}

double2 operator-(double2 a, double2 b) {
    double2 d, t;
    d = double2::twoDiff(a.x, b.x);
    t = double2::twoDiff(a.y, b.y);
    d.y += t.x;
    d = double2::quickTwoDiff(d.x, d.y);
    d.y += t.y;
    d = double2::quickTwoDiff(d.x, d.y);
    return d;
}

double2 operator*(double2 a, double2 b) {
    double2 p;
    p = double2::twoProd(a.x, b.x);
    p.y += a.x * b.y;
    p.y += a.y * b.x;
    p = double2::quickTwoSum(p.x, p.y);
    return p;
}

double2 operator/(double2 b, double2 a) {
    fp64 xn = 1.0f / a.x;
    fp64 yn = b.x * xn;
    fp64 diff = (b - (a * double2(yn))).x;
    double2 prod = double2::twoProd(xn, diff);
    double2 result = yn + prod;
    return result;
}

double2 f2_sqr(double2 a) {
    double2 s;
    s = double2::twoSqr(a.x);
    s.y += a.x * a.y;
    s.y += a.y * a.x;
    s = double2::quickTwoSum(s.x, s.y);
    return s;
}

double2 f2_sqrt(double2 a) {
    fp64 xn = 1 / sqrt(a.x);
    fp64 yn = a.x * xn;
    double2 ynsqr = f2_sqr(yn);
    fp64 diff = (a - ynsqr).x;
    double2 prod = double2::twoProd(xn, diff) / double2(fp64(2.0f));
    double2 result = yn + prod;
    return result;
}