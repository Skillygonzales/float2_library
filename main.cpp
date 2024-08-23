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

    int fp32_p = 16;
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
    // TESTARE adunare:
    std::cout << std::setprecision(fp32_p) << "adunare cu precizie fp32   = " << c1 << std::endl;
    std::cout << std::setprecision(fp64_p) << "adunare cu precizie float2 = " << c2 << std::endl;
    std::cout << std::setprecision(fp64_p) << "adunare cu precizie fp64   = " << a + b << std::endl;

    std::cout << std::endl;
    // TESTARE scadere:
    std::cout << std::setprecision(fp32_p) << "scadere cu precizie fp32   = " << d1 << std::endl;
    std::cout << std::setprecision(fp64_p) << "scadere cu precizie float2 = " << d2 << std::endl;
    std::cout << std::setprecision(fp64_p) << "scadere cu precizie fp64   = " << a - b << std::endl;

    std::cout << std::endl;
    // TESTARE inmultire:
    std::cout << std::setprecision(fp32_p) << "inmultire cu precizie fp32   = " << e1 << std::endl;
    std::cout << std::setprecision(fp64_p) << "inmultire cu precizie float2 = " << e2 << std::endl;
    std::cout << std::setprecision(fp64_p) << "inmultire cu precizie fp64   = " << a * b << std::endl;

    std::cout << std::endl;
    // TESTARE impartire:
    std::cout << std::setprecision(fp32_p) << "impartire cu precizie fp32   = " << f1 << std::endl;
    std::cout << std::setprecision(fp64_p) << "impartire cu precizie float2 = " << f2 << std::endl;
    std::cout << std::setprecision(fp64_p) << "impartire cu precizie fp64   = " << a / b << std::endl;

    std::cout << std::endl;
    // TESTARE ridicare la patrat:
    std::cout << std::setprecision(fp32_p) << "ridicare la patrat cu precizie 32     = " << g1 << std::endl;
    std::cout << std::setprecision(fp64_p) << "ridicare la patrat cu precizie float2 = " << g2 << std::endl;
    std::cout << std::setprecision(fp64_p) << "ridicare la patrat cu precizie fp64   = " << a * a << std::endl;

    std::cout << std::endl;
    // TESTARE radical:
    std::cout << std::setprecision(fp32_p) << "radical cu precizie fp32   = " << h1 << std::endl;
    std::cout << std::setprecision(fp64_p) << "radical cu precizie float2 = " << h2 << std::endl;
    std::cout << std::setprecision(fp64_p) << "radical cu precizie fp64   = " << sqrt(a) << std::endl;

    fs::path dir = "results";
    if (!fs::exists(dir)) {
        fs::create_directories(dir);  
    }

    std::ofstream file_add(dir / "1_adunare.csv");
    std::ofstream file_sub(dir / "2_scadere.csv");
    std::ofstream file_mul(dir / "3_inmultire.csv");
    std::ofstream file_div(dir / "4_impartire.csv");
    std::ofstream file_sqr(dir / "5_ridicare_la_patrat.csv");
    std::ofstream file_sqrt(dir / "6_radical.csv");

    file_add  << "adunare cu precizie fp32,adunare cu precizie float2,adunare cu precizie fp64\n";
    file_sub  << "scadere cu precizie fp32,scadere cu precizie float2,scadere cu precizie fp64\n";
    file_mul  << "inmultire cu precizie fp32,inmultire cu precizie float2,inmultire cu precizie fp64\n";
    file_div  << "impartire cu precizie fp32,impartire cu precizie float2,impartire cu precizie fp64\n";
    file_sqr  << "ridicare la patrat cu precizie 32,ridicare la patrat cu precizie float2,ridicare la patrat cu precizie fp64\n";
    file_sqrt << "radical cu precizie fp32,radical cu precizie float2,radical cu precizie fp64\n";

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

        std::cout << std::setprecision(fp32_p) << "adunare cu precizie fp32   = " << c1_test << std::endl;
        std::cout << std::setprecision(fp64_p) << "adunare cu precizie float2 = " << c2_test << std::endl;
        std::cout << std::setprecision(fp64_p) << "adunare cu precizie fp64   = " << fp64_add << std::endl;
        std::cout << std::endl;

        std::cout << std::setprecision(fp32_p) << "scadere cu precizie fp32   = " << d1_test << std::endl;
        std::cout << std::setprecision(fp64_p) << "scadere cu precizie float2 = " << d2_test << std::endl;
        std::cout << std::setprecision(fp64_p) << "scadere cu precizie fp64   = " << fp64_sub << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;

        std::cout << std::setprecision(fp32_p) << "inmultire cu precizie fp32   = " << e1_test << std::endl;
        std::cout << std::setprecision(fp64_p) << "inmultire cu precizie float2 = " << e2_test << std::endl;
        std::cout << std::setprecision(fp64_p) << "inmultire cu precizie fp64   = " << fp64_mul << std::endl;
        std::cout << std::endl;

        std::cout << std::setprecision(fp32_p) << "impartire cu precizie fp32   = " << f1_test << std::endl;
        std::cout << std::setprecision(fp64_p) << "impartire cu precizie float2 = " << f2_test << std::endl;
        std::cout << std::setprecision(fp64_p) << "impartire cu precizie fp64   = " << fp64_div << std::endl;
        std::cout << std::endl;
        
        std::cout << std::setprecision(fp32_p) << "ridicare la patrat cu precizie 32   = " << g1_test << std::endl;
        std::cout << std::setprecision(fp64_p) << "ridicare la patrat cu precizie float2 = " << g2_test << std::endl;
        std::cout << std::setprecision(fp64_p) << "ridicare la patrat cu precizie fp64   = " << fp64_sqr << std::endl;
        std::cout << std::endl;
        
        std::cout << std::setprecision(fp32_p) << "radical cu precizie fp32   = " << h1_test << std::endl;
        std::cout << std::setprecision(fp64_p) << "radical cu precizie float2 = " << h2_test << std::endl;
        std::cout << std::setprecision(fp64_p) << "radical cu precizie fp64   = " << fp64_sqrt << std::endl;
        std::cout << std::endl;

    }

    file_add.close();

    return 0;
}