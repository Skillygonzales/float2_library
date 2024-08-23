#include "double2.h"
#include "types.h"
#include <cmath>

double2::double2(fp64 _x = 0, fp64 _y = 0) {
    x = _x;
    y = _y;
}

double2::double2(fp128 _x) {
    double2 result = splitDouble(_x);
    x = result.x;
    y = result.y;
}

fp64 double2::getX() const { return x; }
fp64 double2::getY() const { return y; }

double2 double2::splitDouble(fp128 a) {
    const fp128 splitter = (__int128_t(1) << 60) + 1;
    fp128 t = a * splitter;
    fp128 t_hi = t - (t - a);
    fp128 t_lo = a - t_hi;

    fp64 a_hi = (fp64) t_hi;
    fp64 a_lo = (fp64) t_lo;
    return double2(a_hi, a_lo);
}

double2 double2::split(fp64 a) {
    const fp64 split = (1 << 29) + 1;
    fp64 t = a * split;
    fp64 a_hi = t - (t-a);
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
    fp64 s = a - b;
    fp64 e = (a - s) - b;
    return double2(s, e);
}

double2 double2::twoDiff (fp64 a, fp64 b) {
    fp64 s = a - b;
    fp64 v = s - a;
    fp64 e = (a - (s - v) - (b + v));
    return double2(s, e);
}

double2 double2::twoProd(fp64 a, fp64 b) {
    fp64 p = a * b;
    double2 aS = split(a);
    double2 bS = split(b);
    fp64 err = ((aS.x * bS.x - p) + aS.x * bS.y + aS.y * bS.x) + aS.y * bS.y;
    return double2(p, err);
}

double2 double2::twoSqr(fp64 a) {
    fp64 p = a * a;
    double2 aS = split(a);
    fp64 err = ((aS.x * aS.x - p) + aS.x * aS.y + aS.y * aS.x) + aS.y * aS.y;
    return double2(p, err);
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
    double2 s, t;
    s = double2::twoDiff(a.x, b.x);
    t = double2::twoDiff(a.y, b.y);
    s.y += t.x;
    s = double2::quickTwoDiff(s.x, s.y);
    s.y += t.y;
    s = double2::quickTwoDiff(s.x, s.y);
    return s;
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
    double2 p;
    p = double2::twoSqr(a.x);
    p.y += a.x * a.y;
    p.y += a.y * a.x;
    p = double2::quickTwoSum(p.x, p.y);
    return p;
}

double2 f2_sqrt(double2 a) {
    fp64 xn = 1 / sqrt(a.x);
    fp64 yn = a.x * xn;
    double2 ynsqr = f2_sqr(yn);
    fp64 diff = (a - ynsqr).x;
    double2 prod = double2::twoProd(xn, diff) / double2(2.0f);
    double2 result = yn + prod;
    return result;
}