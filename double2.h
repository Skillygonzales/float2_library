#ifndef DOUBLE2_H
#define DOUBLE2_H

#include "types.h"

class double2 {
private:
    fp64 x;
    fp64 y;

public:
    double2(fp64 _x, fp64 _y);
    double2(fp128 _x);

    fp64 getX() const;
    fp64 getY() const;

    static double2 splitDouble(fp128 a);
    static double2 split(fp64 a);
    static fp128 combine(double2 a);
    static double2 twoSum(fp64 a, fp64 b);
    static double2 quickTwoSum(fp64 a, fp64 b);
    static double2 quickTwoDiff(fp64 a, fp64 b);
    static double2 twoDiff(fp64 a, fp64 b);
    static double2 twoProd(fp64 a, fp64 b);
    static double2 twoSqr(fp64 a);

    friend double2 operator+(double2 a, double2 b);
    friend double2 operator-(double2 a, double2 b);
    friend double2 operator*(double2 a, double2 b);
    friend double2 operator/(double2 b, double2 a);
    friend double2 f2_sqr(double2 a);
    friend double2 f2_sqrt(double2 a);
};

#endif
