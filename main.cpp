#include <iostream>
#include <iomanip>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>
#include <random>
#include <fstream>
#include <filesystem>
#include <quadmath.h>
#include "double2.h"
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

    fp64 interval_min = 0.1;
    fp64 interval_max = 1; 

    double2 f2a = double2(fp64(a));
    double2 f2b = double2(fp64(b));
    double2 f2c = f2a + f2b;
    double2 f2d = f2a - f2b;
    double2 f2e = f2a * f2b;
    double2 f2f = f2a / f2b;
    double2 f2g = f2_sqr(f2a);
    double2 f2h = f2_sqrt(f2a);

    fp64 c1 = (fp64)a + (fp64)b;
    fp128 c2 = double2::combine(f2c);

    fp64 d1 = (fp64)a - (fp64)b;
    fp128 d2 = double2::combine(f2d);

    fp64 e1 = (fp64)a * (fp64)b;
    fp128 e2 = double2::combine(f2e);

    fp64 f1 = (fp64)a / (fp64)b;
    fp128 f2 = double2::combine(f2f);

    fp64 g1 = (fp64)a * (fp64)a;
    fp128 g2 = double2::combine(f2g);

    fp64 h1 = sqrt((fp64)a);
    fp128 h2 = double2::combine(f2h);

    std::cout << std::endl;
    // TESTARE adunare:
    std::cout << std::setprecision(fp64_p) << "adunare cu precizie fp64    = " << c1 << std::endl;
    std::cout << "adunare cu precizie double2 = " << float128_to_string(c2) << std::endl;
    std::cout << "adunare cu precizie fp128   = " << float128_to_string(a + b) << std::endl;

    std::cout << std::endl;
    // TESTARE scadere:
    std::cout << std::setprecision(fp64_p) << "scadere cu precizie fp64    = " << d1 << std::endl;
    std::cout << "scadere cu precizie double2 = " << float128_to_string(d2) << std::endl;
    std::cout << "scadere cu precizie fp128   = " << float128_to_string(a - b) << std::endl;

    std::cout << std::endl;
    // TESTARE inmultire:
    std::cout << std::setprecision(fp64_p) << "inmultire cu precizie fp64    = " << e1 << std::endl;
    std::cout << "inmultire cu precizie double2 = " << float128_to_string(e2) << std::endl;
    std::cout << "inmultire cu precizie fp128   = " << float128_to_string(a * b) << std::endl;

    std::cout << std::endl;
    // TESTARE impartire:
    std::cout << std::setprecision(fp64_p) << "impartire cu precizie fp64    = " << f1 << std::endl;
    std::cout << "impartire cu precizie double2 = " << float128_to_string(f2) << std::endl;
    std::cout << "impartire cu precizie fp128   = " << float128_to_string(a / b) << std::endl;

    std::cout << std::endl;
    // TESTARE ridicare la patrat:
    std::cout << std::setprecision(fp64_p) << "ridicare la patrat cu precizie 64      = " << g1 << std::endl;
    std::cout << "ridicare la patrat cu precizie double2 = " << float128_to_string(g2) << std::endl;
    std::cout << "ridicare la patrat cu precizie fp128   = " << float128_to_string(a * a) << std::endl;

    std::cout << std::endl;
    // TESTARE radical:
    std::cout << std::setprecision(fp64_p) << "radical cu precizie fp64    = " << h1 << std::endl;
    std::cout << "radical cu precizie double2 = " << float128_to_string(h2) << std::endl;
    std::cout << "radical cu precizie fp128   = " << float128_to_string(sqrtq(a)) << std::endl;
    
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

    file_add  << "adunare cu precizie fp64,adunare cu precizie double2,adunare cu precizie fp128\n";
    file_sub  << "scadere cu precizie fp64,scadere cu precizie double2,scadere cu precizie fp128\n";
    file_mul  << "inmultire cu precizie fp64,inmultire cu precizie double2,inmultire cu precizie fp128\n";
    file_div  << "impartire cu precizie fp64,impartire cu precizie double2,impartire cu precizie fp128\n";
    file_sqr  << "ridicare la patrat cu precizie 64,ridicare la patrat cu precizie double2,ridicare la patrat cu precizie fp128\n";
    file_sqrt << "radical cu precizie fp64,radical cu precizie double2,radical cu precizie fp128\n";

    unsigned int seed = 12345;
    std::mt19937 gen(seed);

    std::uniform_real_distribution<> distr(interval_min, interval_max);

    for(int i = 0; i < 1000; i++) {
        fp128 a_test = distr(gen);
        fp128 b_test = distr(gen);

        double2 f2a_test = double2(fp64(a_test));
        double2 f2b_test = double2(fp64(b_test));

        fp128 fp128_add = a_test + b_test;
        fp128 fp128_sub = a_test - b_test;
        fp128 fp128_mul = a_test * b_test;
        fp128 fp128_div = a_test / b_test;
        fp128 fp128_sqr = a_test * a_test;
        fp128 fp128_sqrt = sqrtq(a_test);

        double2 f2c_test = f2a_test + f2b_test;
        double2 f2d_test = f2a_test - f2b_test;
        double2 f2e_test = f2a_test * f2b_test;
        double2 f2f_test = f2a_test / f2b_test;
        double2 f2g_test = f2_sqr(f2a_test);
        double2 f2h_test = f2_sqrt(f2a_test);

        fp64 c1_test = (fp64)a_test + (fp64)b_test;
        fp128 c2_test = double2::combine(f2c_test);

        fp64 d1_test = (fp64)a_test - (fp64)b_test;
        fp128 d2_test = double2::combine(f2d_test);

        fp64 e1_test = (fp64)a_test * (fp64)b_test;
        fp128 e2_test = double2::combine(f2e_test);

        fp64 f1_test = (fp64)a_test / (fp64)b_test;
        fp128 f2_test = double2::combine(f2f_test);

        fp64 g1_test = (fp64)a_test * (fp64)a_test;
        fp128 g2_test = double2::combine(f2g_test);

        fp64 h1_test = sqrt((fp64)a_test);
        fp128 h2_test = double2::combine(f2h_test);

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

        std::cout << std::setprecision(fp64_p) << "adunare cu precizie fp64    = " << c1_test << std::endl;
        std::cout << "adunare cu precizie double2 = " << float128_to_string(c2_test) << std::endl;
        std::cout << "adunare cu precizie fp128   = " << float128_to_string(fp128_add) << std::endl;
        std::cout << std::endl;

        std::cout << std::setprecision(fp64_p) << "scadere cu precizie fp64    = " << d1_test << std::endl;
        std::cout << "scadere cu precizie double2 = " << float128_to_string(d2_test) << std::endl;
        std::cout << "scadere cu precizie fp128   = " << float128_to_string(fp128_sub) << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;

        std::cout << std::setprecision(fp64_p) << "inmultire cu precizie fp64    = " << e1_test << std::endl;
        std::cout << "inmultire cu precizie double2 = " << float128_to_string(e2_test) << std::endl;
        std::cout << "inmultire cu precizie fp128   = " << float128_to_string(fp128_mul) << std::endl;
        std::cout << std::endl;

        std::cout << std::setprecision(fp64_p) << "impartire cu precizie fp64    = " << f1_test << std::endl;
        std::cout << "impartire cu precizie double2 = " << float128_to_string(f2_test) << std::endl;
        std::cout << "impartire cu precizie fp128   = " << float128_to_string(fp128_div) << std::endl;
        std::cout << std::endl;
        
        std::cout << std::setprecision(fp64_p) << "ridicare la patrat cu precizie 64      = " << g1_test << std::endl;
        std::cout << "ridicare la patrat cu precizie double2 = " << float128_to_string(g2_test) << std::endl;
        std::cout << "ridicare la patrat cu precizie fp128   = " << float128_to_string(fp128_sqr) << std::endl;
        std::cout << std::endl;
        
        std::cout << std::setprecision(fp64_p) << "radical cu precizie fp64    = " << h1_test << std::endl;
        std::cout << "radical cu precizie double2 = " << float128_to_string(h2_test) << std::endl;
        std::cout << "radical cu precizie fp128   = " << float128_to_string(fp128_sqrt) << std::endl;
        std::cout << std::endl;

    }

    file_add.close();
    file_sub.close();
    file_mul.close();
    file_div.close();
    file_sqr.close();
    file_sqrt.close();

    return 0;
}