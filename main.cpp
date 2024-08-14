#include <iostream>
#include <iomanip>
#include <cmath>
#include <random>
#include <fstream>
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

    std::ofstream file_add("addition.csv");
    std::ofstream file_sub("subtraction.csv");
    std::ofstream file_mul("multiplication.csv");
    std::ofstream file_div("division.csv");

    file_add << "FP32 precision addition,float2 precision addition,FP64 precision addition\n";
    file_sub << "FP32 precision subtraction,float2 precision subtraction,FP64 precision subtraction\n";
    file_mul << "FP32 precision multiplication,float2 precision multiplication,FP64 precision multiplication\n";
    file_div << "FP32 precision division,float2 precision division,FP64 precision division\n";

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<> distr(0.0, 1.0);

    for(int i = 0; i < 1000; i++) {
        fp64 a_test = distr(gen);
        fp64 b_test = distr(gen);

        float2 f2a_test = float2(fp32(a_test));
        float2 f2b_test = float2(fp32(b_test));

        fp64 fp64_add = a_test + b_test;
        fp64 fp64_sub = a_test - b_test;
        fp64 fp64_mul = a_test * b_test;
        fp64 fp64_div = a_test / b_test;

        float2 f2c_test = f2a_test + f2b_test;
        float2 f2d_test = f2a_test - f2b_test;
        float2 f2e_test = f2a_test * f2b_test;
        float2 f2f_test = f2a_test / f2b_test;

        fp32 c1_test = (fp32)a_test + (fp32)b_test;
        fp64 c2_test = float2::combine(f2c_test);

        fp32 d1_test = (fp32)a_test - (fp32)b_test;
        fp64 d2_test = float2::combine(f2d_test);

        fp32 e1_test = (fp32)a_test * (fp32)b_test;
        fp64 e2_test = float2::combine(f2e_test);

        fp32 f1_test = (fp32)a_test / (fp32)b_test;
        fp64 f2_test = float2::combine(f2f_test);

        file_add << std::setprecision(15)
             << c1_test << ","
             << c2_test << ","
             << fp64_add << "\n";

        file_sub << std::setprecision(15)
             << d1_test << ","
             << d2_test << ","
             << fp64_sub << "\n";

        file_mul << std::setprecision(15)
             << e1_test << ","
             << e2_test << ","
             << fp64_mul << "\n";

        file_div << std::setprecision(15)
             << f1_test << ","
             << f2_test << ","
             << fp64_div << "\n";

        std::cout << std::setprecision(15) << "FP32 precision additon   = " << c1_test << std::endl;
        std::cout << std::setprecision(15) << "float2 precision additon = " << c2_test << std::endl;
        std::cout << std::setprecision(15) << "FP64 precision additon   = " << fp64_add << std::endl;
        std::cout << std::endl;

        std::cout << std::setprecision(15) << "FP32 precision subtraction   = " << d1_test << std::endl;
        std::cout << std::setprecision(15) << "float2 precision subtraction = " << d2_test << std::endl;
        std::cout << std::setprecision(15) << "FP64 precision subtraction   = " << fp64_sub << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;

        std::cout << std::setprecision(15) << "FP32 precision multiplication   = " << e1_test << std::endl;
        std::cout << std::setprecision(15) << "float2 precision multiplication = " << e2_test << std::endl;
        std::cout << std::setprecision(15) << "FP64 precision multiplication   = " << fp64_mul << std::endl;
        std::cout << std::endl;

        std::cout << std::setprecision(15) << "FP32 precision division   = " << f1_test << std::endl;
        std::cout << std::setprecision(15) << "float2 precision division = " << f2_test << std::endl;
        std::cout << std::setprecision(15) << "FP64 precision division   = " << fp64_div << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;

    }

    file_add.close();

    return 0;
}