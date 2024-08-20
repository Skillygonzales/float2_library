#include <iostream>
#include <iomanip>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>
#include <random>
#include <fstream>
#include <filesystem>
#include "float2.h"
#include "types.h"
namespace fs = std::filesystem;

int main() {
    fp64 a = M_PI;
    fp64 b = M_E;

    int fp32_p = 6;
    int fp64_p = 15;
    fp32 interval_low = 0.1;
    fp32 interval_max = 1; 

    float2 f2a = float2(fp32(a));
    float2 f2b = float2(fp32(b));
    float2 f2c = f2a + f2b;
    float2 f2d = f2a - f2b;
    float2 f2e = f2a * f2b;
    float2 f2f = f2a / f2b;
    float2 f2g = f2_sqr(f2a);
    float2 f2h = f2_sqrt(f2a);

    fp32 c1 = (fp32)a + (fp32)b;
    fp64 c2 = float2::combine(f2c);

    fp32 d1 = (fp32)a - (fp32)b;
    fp64 d2 = float2::combine(f2d);

    fp32 e1 = (fp32)a * (fp32)b;
    fp64 e2 = float2::combine(f2e);

    fp32 f1 = (fp32)a / (fp32)b;
    fp64 f2 = float2::combine(f2f);

    fp32 g1 = (fp32)a * (fp32)a;
    fp64 g2 = float2::combine(f2g);

    fp32 h1 = sqrt((fp32)a);
    fp64 h2 = float2::combine(f2h);

    std::cout << std::endl;
    // TESTING FP64 addition:
    std::cout << std::setprecision(fp32_p) << "FP32 precision additon   = " << c1 << std::endl;
    std::cout << std::setprecision(fp64_p) << "float2 precision additon = " << c2 << std::endl;
    std::cout << std::setprecision(fp64_p) << "FP64 precision additon   = " << a + b << std::endl;

    std::cout << std::endl;
    // TESTING FP64 subtraction:
    std::cout << std::setprecision(fp32_p) << "FP32 precision subtraction   = " << d1 << std::endl;
    std::cout << std::setprecision(fp64_p) << "float2 precision subtraction = " << d2 << std::endl;
    std::cout << std::setprecision(fp64_p) << "FP64 precision subtraction   = " << a - b << std::endl;

    std::cout << std::endl;
    // TESTING FP64 multiplication:
    std::cout << std::setprecision(fp32_p) << "FP32 precision multiplication   = " << e1 << std::endl;
    std::cout << std::setprecision(fp64_p) << "float2 precision multiplication = " << e2 << std::endl;
    std::cout << std::setprecision(fp64_p) << "FP64 precision multiplication   = " << a * b << std::endl;

    std::cout << std::endl;
    // TESTING FP64 division:
    std::cout << std::setprecision(fp32_p) << "FP32 precision division   = " << f1 << std::endl;
    std::cout << std::setprecision(fp64_p) << "float2 precision division = " << f2 << std::endl;
    std::cout << std::setprecision(fp64_p) << "FP64 precision division   = " << a / b << std::endl;

    std::cout << std::endl;
    // TESTING FP64 square:
    std::cout << std::setprecision(fp32_p) << "FP32 precision square   = " << g1 << std::endl;
    std::cout << std::setprecision(fp64_p) << "float2 precision square = " << g2 << std::endl;
    std::cout << std::setprecision(fp64_p) << "FP64 precision square   = " << a * a << std::endl;

    std::cout << std::endl;
    // TESTING FP64 square root:
    std::cout << std::setprecision(fp32_p) << "FP32 precision square root  = " << h1 << std::endl;
    std::cout << std::setprecision(fp64_p) << "float2 precision square root = " << h2 << std::endl;
    std::cout << std::setprecision(fp64_p) << "FP64 precision square root = " << sqrt(a) << std::endl;

    fs::path dir = "results";
    if (!fs::exists(dir)) {
        fs::create_directories(dir);  // Create the directory if it doesn't exist
    }

    std::ofstream file_add(dir / "1_addition.csv");
    std::ofstream file_sub(dir / "2_subtraction.csv");
    std::ofstream file_mul(dir / "3_multiplication.csv");
    std::ofstream file_div(dir / "4_division.csv");
    std::ofstream file_sqr(dir / "5_square.csv");
    std::ofstream file_sqrt(dir / "6_square_root.csv");

    file_add  << "FP32 precision addition,float2 precision addition,FP64 precision addition\n";
    file_sub  << "FP32 precision subtraction,float2 precision subtraction,FP64 precision subtraction\n";
    file_mul  << "FP32 precision multiplication,float2 precision multiplication,FP64 precision multiplication\n";
    file_div  << "FP32 precision division,float2 precision division,FP64 precision division\n";
    file_sqr  << "FP32 precision square,float2 precision square,FP64 precision square\n";
    file_sqrt << "FP32 precision square root,float2 precision square root,FP64 precision square root\n";

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<> distr(interval_low, interval_max);

    for(int i = 0; i < 1000; i++) {
        fp64 a_test = distr(gen);
        fp64 b_test = distr(gen);

        float2 f2a_test = float2(fp32(a_test));
        float2 f2b_test = float2(fp32(b_test));

        fp64 fp64_add = a_test + b_test;
        fp64 fp64_sub = a_test - b_test;
        fp64 fp64_mul = a_test * b_test;
        fp64 fp64_div = a_test / b_test;
        fp64 fp64_sqr = a_test * a_test;
        fp64 fp64_sqrt = sqrt(a_test);

        float2 f2c_test = f2a_test + f2b_test;
        float2 f2d_test = f2a_test - f2b_test;
        float2 f2e_test = f2a_test * f2b_test;
        float2 f2f_test = f2a_test / f2b_test;
        float2 f2g_test = f2_sqr(f2a_test);
        float2 f2h_test = f2_sqrt(f2a_test);

        fp32 c1_test = (fp32)a_test + (fp32)b_test;
        fp64 c2_test = float2::combine(f2c_test);

        fp32 d1_test = (fp32)a_test - (fp32)b_test;
        fp64 d2_test = float2::combine(f2d_test);

        fp32 e1_test = (fp32)a_test * (fp32)b_test;
        fp64 e2_test = float2::combine(f2e_test);

        fp32 f1_test = (fp32)a_test / (fp32)b_test;
        fp64 f2_test = float2::combine(f2f_test);

        fp32 g1_test = (fp32)a_test * (fp32)a_test;
        fp64 g2_test = float2::combine(f2g_test);

        fp32 h1_test = sqrt((fp32)a_test);
        fp64 h2_test = float2::combine(f2h_test);

        file_add << std::setprecision(fp32_p) << c1_test << ","
                 << std::setprecision(fp64_p) << c2_test << ","
                 << std::setprecision(fp64_p) << fp64_add << "\n";

        file_sub << std::setprecision(fp32_p) << d1_test << ","
                 << std::setprecision(fp64_p) << d2_test << ","
                 << std::setprecision(fp64_p) << fp64_sub << "\n";

        file_mul << std::setprecision(fp32_p) << e1_test << ","
                 << std::setprecision(fp64_p) << e2_test << ","
                 << std::setprecision(fp64_p) << fp64_mul << "\n";

        file_div << std::setprecision(fp32_p) << f1_test << ","
                 << std::setprecision(fp64_p) << f2_test << ","
                 << std::setprecision(fp64_p) << fp64_div << "\n";

        file_sqr << std::setprecision(fp32_p) << g1_test << ","
                 << std::setprecision(fp64_p) << g2_test << ","
                 << std::setprecision(fp64_p) << fp64_sqr << "\n";

        file_sqrt << std::setprecision(fp32_p) << h1_test << ","
                  << std::setprecision(fp64_p) << h2_test << ","
                  << std::setprecision(fp64_p) << fp64_sqrt << "\n";

        std::cout << std::setprecision(fp32_p) << "FP32 precision additon   = " << c1_test << std::endl;
        std::cout << std::setprecision(fp64_p) << "float2 precision additon = " << c2_test << std::endl;
        std::cout << std::setprecision(fp64_p) << "FP64 precision additon   = " << fp64_add << std::endl;
        std::cout << std::endl;

        std::cout << std::setprecision(fp32_p) << "FP32 precision subtraction   = " << d1_test << std::endl;
        std::cout << std::setprecision(fp64_p) << "float2 precision subtraction = " << d2_test << std::endl;
        std::cout << std::setprecision(fp64_p) << "FP64 precision subtraction   = " << fp64_sub << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;

        std::cout << std::setprecision(fp32_p) << "FP32 precision multiplication   = " << e1_test << std::endl;
        std::cout << std::setprecision(fp64_p) << "float2 precision multiplication = " << e2_test << std::endl;
        std::cout << std::setprecision(fp64_p) << "FP64 precision multiplication   = " << fp64_mul << std::endl;
        std::cout << std::endl;

        std::cout << std::setprecision(fp32_p) << "FP32 precision division   = " << f1_test << std::endl;
        std::cout << std::setprecision(fp64_p) << "float2 precision division = " << f2_test << std::endl;
        std::cout << std::setprecision(fp64_p) << "FP64 precision division   = " << fp64_div << std::endl;
        std::cout << std::endl;
        
        std::cout << std::setprecision(fp32_p) << "FP32 precision square   = " << g1_test << std::endl;
        std::cout << std::setprecision(fp64_p) << "float2 precision square = " << g2_test << std::endl;
        std::cout << std::setprecision(fp64_p) << "FP64 precision square   = " << fp64_sqr << std::endl;
        std::cout << std::endl;
        
        std::cout << std::setprecision(fp32_p) << "FP32 precision square root   = " << h1_test << std::endl;
        std::cout << std::setprecision(fp64_p) << "float2 precision square root = " << h2_test << std::endl;
        std::cout << std::setprecision(fp64_p) << "FP64 precision square root   = " << fp64_sqrt << std::endl;
        std::cout << std::endl;

    }

    file_add.close();

    return 0;
}