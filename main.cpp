#include <iostream>
#include <iomanip>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>
#include <random>
#include <fstream>
#include <filesystem>
#include <quadmath.h>
#include "float2.h"
#include "types.h"
namespace fs = std::filesystem;

std::string float128_to_string(__float128 value, int precision = 35) {
    char buffer[128];
    quadmath_snprintf(buffer, sizeof(buffer), "%.*Qg", precision, value);
    return std::string(buffer);
}

int main() {
    fp128 a = M_PI;
    fp128 b = M_E;

    int fp64_p = 15;

    float2 f2a = float2(fp64(a));
    float2 f2b = float2(fp64(b));
    float2 f2c = f2a + f2b;
    float2 f2d = f2a - f2b;
    float2 f2e = f2a * f2b;
    float2 f2f = f2a / f2b;
    float2 f2g = f2_sqr(f2a);
    float2 f2h = f2_sqrt(f2a);

    fp64 c1 = (fp64)a + (fp64)b;
    fp128 c2 = float2::combine(f2c);

    fp64 d1 = (fp64)a - (fp64)b;
    fp128 d2 = float2::combine(f2d);

    fp64 e1 = (fp64)a * (fp64)b;
    fp128 e2 = float2::combine(f2e);

    fp64 f1 = (fp64)a / (fp64)b;
    fp128 f2 = float2::combine(f2f);

    fp64 g1 = (fp64)a * (fp64)a;
    fp128 g2 = float2::combine(f2g);

    fp64 h1 = sqrt((fp64)a);
    fp128 h2 = float2::combine(f2h);

    std::cout << std::endl;
    // TESTING fp128 addition:
    std::cout << std::setprecision(fp64_p) << "fp64 precision additon   = " << c1 << std::endl;
    std::cout << "float2 precision additon = " << float128_to_string(c2) << std::endl;
    std::cout << "fp128 precision additon   = " << float128_to_string(a + b) << std::endl;

    std::cout << std::endl;
    // TESTING fp128 subtraction:
    std::cout << std::setprecision(fp64_p) << "fp64 precision subtraction   = " << d1 << std::endl;
    std::cout << "float2 precision subtraction = " << float128_to_string(d2) << std::endl;
    std::cout << "fp128 precision subtraction   = " << float128_to_string(a - b) << std::endl;

    std::cout << std::endl;
    // TESTING fp128 multiplication:
    std::cout << std::setprecision(fp64_p) << "fp64 precision multiplication   = " << e1 << std::endl;
    std::cout << "float2 precision multiplication = " << float128_to_string(e2) << std::endl;
    std::cout << "fp128 precision multiplication   = " << float128_to_string(a * b) << std::endl;

    std::cout << std::endl;
    // TESTING fp128 division:
    std::cout << std::setprecision(fp64_p) << "fp64 precision division   = " << f1 << std::endl;
    std::cout << "float2 precision division = " << float128_to_string(f2) << std::endl;
    std::cout << "fp128 precision division   = " << float128_to_string(a / b) << std::endl;

    std::cout << std::endl;
    // TESTING fp128 square:
    std::cout << std::setprecision(fp64_p) << "fp64 precision square   = " << g1 << std::endl;
    std::cout << "float2 precision square = " << float128_to_string(g2) << std::endl;
    std::cout << "fp128 precision square   = " << float128_to_string(a * a) << std::endl;

    std::cout << std::endl;
    // TESTING fp128 square root:
    std::cout << std::setprecision(fp64_p) << "fp64 precision square root  = " << h1 << std::endl;
    std::cout << "float2 precision square root = " << float128_to_string(h2) << std::endl;
    std::cout << "fp128 precision square root = " << float128_to_string(sqrtq(a)) << std::endl;
    /*
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

    file_add  << "fp64 precision addition,float2 precision addition,fp128 precision addition\n";
    file_sub  << "fp64 precision subtraction,float2 precision subtraction,fp128 precision subtraction\n";
    file_mul  << "fp64 precision multiplication,float2 precision multiplication,fp128 precision multiplication\n";
    file_div  << "fp64 precision division,float2 precision division,fp128 precision division\n";
    file_sqr  << "fp64 precision square,float2 precision square,fp128 precision square\n";
    file_sqrt << "fp64 precision square root,float2 precision square root,fp128 precision square root\n";

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<> distr(0.1, 1.0);

    for(int i = 0; i < 1000; i++) {
        fp128 a_test = distr(gen);
        fp128 b_test = distr(gen);

        float2 f2a_test = float2(fp64(a_test));
        float2 f2b_test = float2(fp64(b_test));

        fp128 fp128_add = a_test + b_test;
        fp128 fp128_sub = a_test - b_test;
        fp128 fp128_mul = a_test * b_test;
        fp128 fp128_div = a_test / b_test;
        fp128 fp128_sqr = a_test * a_test;
        fp128 fp128_sqrt = sqrtq(a_test);

        float2 f2c_test = f2a_test + f2b_test;
        float2 f2d_test = f2a_test - f2b_test;
        float2 f2e_test = f2a_test * f2b_test;
        float2 f2f_test = f2a_test / f2b_test;
        float2 f2g_test = f2_sqr(f2a_test);
        float2 f2h_test = f2_sqrt(f2a_test);

        fp64 c1_test = (fp64)a_test + (fp64)b_test;
        fp128 c2_test = float2::combine(f2c_test);

        fp64 d1_test = (fp64)a_test - (fp64)b_test;
        fp128 d2_test = float2::combine(f2d_test);

        fp64 e1_test = (fp64)a_test * (fp64)b_test;
        fp128 e2_test = float2::combine(f2e_test);

        fp64 f1_test = (fp64)a_test / (fp64)b_test;
        fp128 f2_test = float2::combine(f2f_test);

        fp64 g1_test = (fp64)a_test * (fp64)a_test;
        fp128 g2_test = float2::combine(f2g_test);

        fp64 h1_test = sqrt((fp64)a_test);
        fp128 h2_test = float2::combine(f2h_test);

        file_add << std::setprecision(fp64_p)
             << c1_test << ","
             << float128_to_string(c2_test) << ","
             << float128_to_string(fp128_add) << "\n";

        file_sub << std::setprecision(fp64_p)
             << d1_test << ","
             << float128_to_string(d2_test) << ","
             << float128_to_string(fp128_sub) << "\n";

        file_mul << std::setprecision(fp64_p)
             << e1_test << ","
             << float128_to_string(e2_test) << ","
             << float128_to_string(fp128_mul) << "\n";

        file_div << std::setprecision(fp64_p)
             << f1_test << ","
             << float128_to_string(f2_test) << ","
             << float128_to_string(fp128_div) << "\n";

        file_sqr << std::setprecision(fp64_p)
             << g1_test << ","
             << float128_to_string(g2_test) << ","
             << float128_to_string(fp128_sqr) << "\n";

        file_sqrt << std::setprecision(fp64_p)
             << h1_test << ","
             << float128_to_string(h2_test) << ","
             << float128_to_string(fp128_sqrt) << "\n";

        std::cout << std::setprecision(fp64_p) << "fp64 precision additon   = " << c1_test << std::endl;
        std::cout << "float2 precision additon = " << float128_to_string(c2_test) << std::endl;
        std::cout << "fp128 precision additon  = " << float128_to_string(fp128_add) << std::endl;
        std::cout << std::endl;

        std::cout << std::setprecision(fp64_p) << "fp64 precision subtraction   = " << d1_test << std::endl;
        std::cout << "float2 precision subtraction = " << float128_to_string(d2_test) << std::endl;
        std::cout << "fp128 precision subtraction  = " << float128_to_string(fp128_sub) << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;

        std::cout << std::setprecision(fp64_p) << "fp64 precision multiplication   = " << e1_test << std::endl;
        std::cout << "float2 precision multiplication = " << float128_to_string(e2_test) << std::endl;
        std::cout << "fp128 precision multiplication  = " << float128_to_string(fp128_mul) << std::endl;
        std::cout << std::endl;

        std::cout << std::setprecision(fp64_p) << "fp64 precision division   = " << f1_test << std::endl;
        std::cout << "float2 precision division = " << float128_to_string(f2_test) << std::endl;
        std::cout << "fp128 precision division  = " << float128_to_string(fp128_div) << std::endl;
        std::cout << std::endl;
        
        std::cout << std::setprecision(fp64_p) << "fp64 precision square   = " << g1_test << std::endl;
        std::cout << "float2 precision square = " << float128_to_string(g2_test) << std::endl;
        std::cout << "fp128 precision square  = " << float128_to_string(fp128_sqr) << std::endl;
        std::cout << std::endl;
        
        std::cout << std::setprecision(fp64_p) << "fp64 precision square root   = " << h1_test << std::endl;
        std::cout << "float2 precision square root = " << float128_to_string(h2_test) << std::endl;
        std::cout << "fp128 precision square root  = " << float128_to_string(fp128_sqrt) << std::endl;
        std::cout << std::endl;

    }

    file_add.close();*/

    return 0;
}