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


// functia pentru afisarea unei valori fp128
std::string float128_to_string(__float128 value, int precision = 35) {
    char buffer[128];
    quadmath_snprintf(buffer, sizeof(buffer), "%.*Qg", precision, value);
    return std::string(buffer);
}

int main() {
    
    // variabile pentru testele initiale
    fp128 a = M_PI;
    fp128 b = M_E;

    // precizia pentru afisarea unei valori de tip fp64
    int fp64_p = 15;

    // intervalul pentru care se fac testele
    fp64 interval_min = 0.1;
    fp64 interval_max = 1; 

    // obiecte de tip double2 obtinute din fp64 - pentru a putea compara rezultatele operatiilor
    double2 f2a = double2(fp64(a));
    double2 f2b = double2(fp64(b));

    // operații initiale pe obiecte de tip double2
    double2 f2c = f2a + f2b;
    double2 f2d = f2a - f2b;
    double2 f2e = f2a * f2b;
    double2 f2f = f2a / f2b;
    double2 f2g = f2_sqr(f2a);
    double2 f2h = f2_sqrt(f2a);

    fp64 c1 = (fp64)a + (fp64)b; // adunare pe fp64
    fp128 c2 = double2::combine(f2c); // conversie double2 -> fp128

    fp64 d1 = (fp64)a - (fp64)b; // scadere pe fp64
    fp128 d2 = double2::combine(f2d); // conversie double2 -> fp128

    fp64 e1 = (fp64)a * (fp64)b; // inmultire pe fp64
    fp128 e2 = double2::combine(f2e); // conversie double2 -> fp128

    fp64 f1 = (fp64)a / (fp64)b; // impartire pe fp64
    fp128 f2 = double2::combine(f2f); // conversie double2 -> fp128

    fp64 g1 = (fp64)a * (fp64)a; // ridicare la puterea a doua pe fp64
    fp128 g2 = double2::combine(f2g); // conversie double2 -> fp128

    fp64 h1 = sqrt((fp64)a); // radical de ordinul al doilea pe fp64
    fp128 h2 = double2::combine(f2h); // conversie double2 -> fp128

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
    
    // crearea directorului results
    fs::path dir = "results";
    if (!fs::exists(dir)) {
        fs::create_directories(dir); 
    }

    // definirea fisierelor in care vor fi scrise rezultatele
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

    // definirea metodei de generare a valorilor aleatoare folosind o distributie uniforma
    unsigned int seed = 12345;
    std::mt19937 gen(seed);

    std::uniform_real_distribution<> distr(interval_min, interval_max);

    for(int i = 0; i < 1000; i++) {
        // variabilele aleatoare folosite pentru testare
        fp128 a_test = distr(gen);
        fp128 b_test = distr(gen);
        
        // obiecte de tip double2 obtinute din fp64
        double2 f2a_test = double2(fp64(a_test));
        double2 f2b_test = double2(fp64(b_test));

        // operatii cu variabile de tip fp128
        fp128 fp128_add = a_test + b_test;
        fp128 fp128_sub = a_test - b_test;
        fp128 fp128_mul = a_test * b_test;
        fp128 fp128_div = a_test / b_test;
        fp128 fp128_sqr = a_test * a_test;
        fp128 fp128_sqrt = sqrtq(a_test);

        // operatii cu obiecte de tip double2
        double2 f2c_test = f2a_test + f2b_test;
        double2 f2d_test = f2a_test - f2b_test;
        double2 f2e_test = f2a_test * f2b_test;
        double2 f2f_test = f2a_test / f2b_test;
        double2 f2g_test = f2_sqr(f2a_test);
        double2 f2h_test = f2_sqrt(f2a_test);

        fp64 c1_test = (fp64)a_test + (fp64)b_test; // adunare pe fp64
        fp128 c2_test = double2::combine(f2c_test); // conversie double2 -> fp128

        fp64 d1_test = (fp64)a_test - (fp64)b_test; // scadere pe fp64
        fp128 d2_test = double2::combine(f2d_test); // conversie double2 -> fp128

        fp64 e1_test = (fp64)a_test * (fp64)b_test; // inmultire pe fp64
        fp128 e2_test = double2::combine(f2e_test); // conversie double2 -> fp128

        fp64 f1_test = (fp64)a_test / (fp64)b_test; // impartire pe fp64
        fp128 f2_test = double2::combine(f2f_test); // conversie double2 -> fp128

        fp64 g1_test = (fp64)a_test * (fp64)a_test; // ridicare la puterea a doua pe fp64
        fp128 g2_test = double2::combine(f2g_test); // conversie double2 -> fp128

        fp64 h1_test = sqrt((fp64)a_test); // radical de ordinul al doilea pe fp64
        fp128 h2_test = double2::combine(f2h_test); // conversie double2 -> fp128

        // scrierea rezultatelor in fisiere

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

        // scrierea rezultatelor in consola pentru verificare

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

    // inchiderea fisierelor in care au fost scrise rezultatele
    file_add.close();
    file_sub.close();
    file_mul.close();
    file_div.close();
    file_sqr.close();
    file_sqrt.close();

    return 0;
}