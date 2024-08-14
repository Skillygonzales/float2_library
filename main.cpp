#include <iostream>
#include <iomanip>
#include <cmath>
#include <random>
#include "float2.h"
#include "types.h"

int main() {
    fp64 a = M_PI;
    fp64 b = M_E;

    float2 f2a = float2(fp32(a));
    float2 f2b = float2(fp32(b));
    float2 f2c = f2a + f2b;
    float2 f2d = f2a - f2b;
    float2 f2e = f2a * f2b;
    float2 f2f = f2a / f2b;

    fp32 c1 = (fp32)a + (fp32)b;
    fp64 c2 = float2::combine(f2c);

    fp32 d1 = (fp32)a - (fp32)b;
    fp64 d2 = float2::combine(f2d);

    fp32 e1 = (fp32)a * (fp32)b;
    fp64 e2 = float2::combine(f2e);

    fp32 f1 = (fp32)a / (fp32)b;
    fp64 f2 = float2::combine(f2f);

    std::cout << std::endl;
    // TESTING FP64 addition:
    std::cout << std::setprecision(16) << "FP32 precision additon   = " << c1 << std::endl;
    std::cout << std::setprecision(16) << "float2 precision additon = " << c2 << std::endl;
    std::cout << std::setprecision(16) << "FP64 precision additon   = " << a + b << std::endl;

    std::cout << std::endl;
    // TESTING FP64 subtraction:
    std::cout << std::setprecision(16) << "FP32 precision subtraction   = " << d1 << std::endl;
    std::cout << std::setprecision(16) << "float2 precision subtraction = " << d2 << std::endl;
    std::cout << std::setprecision(16) << "FP64 precision subtraction   = " << a - b << std::endl;

    std::cout << std::endl;
    // TESTING FP64 multiplication:
    std::cout << std::setprecision(16) << "FP32 precision multiplication   = " << e1 << std::endl;
    std::cout << std::setprecision(16) << "float2 precision multiplication = " << e2 << std::endl;
    std::cout << std::setprecision(16) << "FP64 precision multiplication   = " << a * b << std::endl;

    std::cout << std::endl;
    // TESTING FP64 division:
    std::cout << std::setprecision(16) << "FP32 precision division   = " << f1 << std::endl;
    std::cout << std::setprecision(16) << "float2 precision division = " << f2 << std::endl;
    std::cout << std::setprecision(16) << "FP64 precision division   = " << a / b << std::endl;

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<> distr(0.0, 1.0);

    for(int i = 0; i < 10; i++) {
        fp64 a_test = distr(gen);
        fp64 b_test = distr(gen);

        fp64 fp64_add = a_test + b_test;

        float2 f2a_test = float2(fp32(a_test));
        float2 f2b_test = float2(fp32(b_test));

        float2 f2c_test = f2a_test + f2b_test;

        fp32 c1_test = (fp32)a_test + (fp32)b_test;
        fp64 c2_test = float2::combine(f2c_test);

        std::cout << std::setprecision(16) << "FP32 precision additon   = " << c1_test << std::endl;
        std::cout << std::setprecision(16) << "float2 precision additon = " << c2_test << std::endl;
        std::cout << std::setprecision(16) << "FP64 precision additon   = " << fp64_add << std::endl;
        std::cout << std::endl;

    }

    return 0;
}