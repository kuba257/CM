#include <iostream>
#include <cmath>
using namespace std;

#define nMax 50
#define TOLX pow(10,-8)
#define TOLF pow(10,-8)

double sinFun(double x) {
    return(pow(sin(x / 4.0), 2.0) - x);
}

double sinFi(double x) {
    return(pow(sin(x / 4.0), 2.0));
}

double sinDeriv(double x) {
    return ((1.0 / 4.0) * sin(x / 2) - 1.0);
}

double sinFiDeriv(double x) {
    return(sin(x / 2.0) / 4.0);
}

double tanFun(double x) {
    return(tan(2.0 * x) - x - 1.0);
}

double tanDeriv(double x) {
    return (2.0 / (pow(cos(2.0 * x), 2.0)) - 1.0);
}

double tanFi(double x) {
    return(tan(2.0 * x) - 1.0);
}

double tanFiDeriv(double x) {
    return(2.0 / pow(cos(2.0 * x), 2));
}
typedef double (*function)(double);

void Picard(function mainFunction, function fiFunction, function fiFunctionDeriv, double x) {
    cout << "\tPicard:" << endl;
    if (fiFunctionDeriv(x) >= 1.0) {
        cout << "\n\t\tRozbieznosc metody\n" << endl;
        return;
    }

    double errorEstim = 1.0;
    double resid = 1.0;
    double prev = 0.0;
    double val = x;

    cout << "\t---------------------------------------------------------------------------------" << endl;
    cout << "\t|Numer Iteracji\t|Wartosc przyblizenia\t|Estymator bledu\t|Reziduum" << endl;
    cout << "\t---------------------------------------------------------------------------------" << endl;

    int i = 0;
    for (i; i < nMax && errorEstim > TOLX && resid > TOLF; i++) {
        
        prev = val;
        val = sinFi(val);
        errorEstim = fabs(val - prev);
        resid = fabs(mainFunction(val));

        cout << "\t" << i << "\t\t" << val << "\t\t" << errorEstim << "\t\t" << resid << endl;
    }

    cout << "\n\tPowod zakonczenia iteracji: ";
    if (i == nMax)
        cout << "Przekroczono dopuszczalna ilosc iteracji\n" << endl;

    else if (errorEstim <= TOLX)
        cout << "Estymator bledu jest mniejszy niz zadana tolerancja\n" << endl;

    else if (resid<= TOLF) 
        cout << "Reziduum jest mniejsze niz zadana tolerancja\n" << endl;
}

void Bisection(function mainFunction, double a, double b) {
    cout << "\tBisekcja:" << endl;
    if ((mainFunction(a) < 0 && mainFunction(b) < 0) || (mainFunction(a) > 0 && mainFunction(b) > 0)) {
        cout << "Brak zmiany znaku" << endl;
        return;
    }

    double val = 0.0;
    double errorEstim = 1.0;
    double resid = 1.0;

    cout << "\t---------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "\t|Numer Iteracji\t|a\t\t|b\t\t|Wartosc przyblizenia\t|Estymator bledu\t\t\t|Reziduum" << endl;
    cout << "\t---------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    
    int i = 0;
    for (i; i < nMax && errorEstim > TOLX && resid > TOLF; i++) {

        val = (a + b) / 2.0;
        errorEstim = fabs((b - a) / 2.0);
        resid = fabs(mainFunction(val));

        cout << "\t" << i << "\t\t" << a << "\t\t" << b << "\t\t" << val << "\t\t\t" << errorEstim << "\t\t\t\t\t" << resid << endl;

        if ((mainFunction(b) < 0 && mainFunction(val) > 0) || (mainFunction(b) > 0 && mainFunction(val) < 0))
            a = val;
        else if ((mainFunction(a) < 0 && mainFunction(val) > 0) || (mainFunction(a) > 0 && mainFunction(val) < 0))
            b = val;
    }

    cout << "\n\tPowod zakonczenia iteracji: ";
    if (i == nMax)
        cout << "Przekroczono dopuszczalna ilosc iteracji\n" << endl;

    else if (errorEstim <= TOLX)
        cout << "Estymator bledu jest mniejszy niz zadana tolerancja\n" << endl;

    else if (resid <= TOLF)
        cout << "Reziduum jest mniejsze niz zadana tolerancja\n" << endl;
}

void Newton(function mainFunction, function funDeriv, double x) {
    cout << "\tNewton:" << endl;
    double errorEstim = 1.0;
    double resid = 1.0;
    double val = x;
    double next = 0.0;

    cout << "\t--------------------------------------------------------------------------------------" << endl;
    cout << "\t|Numer Iteracji\t|Wartosc przyblizenia\t|Estymator bledu\t|Reziduum" << endl;
    cout << "\t--------------------------------------------------------------------------------------" << endl;

    int i = 0;
    for (i; i < nMax && errorEstim > TOLX && resid > TOLF; i++) {

        if (funDeriv(val) != 0) {
            next = val - (mainFunction(val) / funDeriv(val));
            errorEstim = fabs(next - val);
            val = next;
            resid = fabs(mainFunction(val));
        }

        cout << "\t" << i << "\t\t" << val << "\t\t" << errorEstim << "\t\t" << resid << endl;
    }

    cout << "\n\tPowod zakonczenia iteracji: ";
    if (i == nMax)
        cout << "Przekroczono dopuszczalna ilosc iteracji\n" << endl;

    else if (errorEstim <= TOLX)
        cout << "Estymator bledu jest mniejszy niz zadana tolerancja\n" << endl;

    else if (resid <= TOLF)
        cout << "Reziduum jest mniejsze niz zadana tolerancja\n" << endl;
}

void Sieczne(function mainFunction, double x1, double x2) {
    cout << "\tSieczne:" << endl;
    double errorEstim = 1.0;
    double resid = 1.0;
    double val = 0.0;

    cout << "\t--------------------------------------------------------------------------------------" << endl;
    cout << "\t|Numer Iteracji\t|Wartosc przyblizenia\t|Estymator bledu\t|Reziduum" << endl;
    cout << "\t--------------------------------------------------------------------------------------" << endl;

    int i = 0;
    for (i; i < nMax && errorEstim > TOLX && resid > TOLF; i++) {

        val = x2 - (mainFunction(x2) / ((mainFunction(x2) - mainFunction(x1)) / (x2 - x1)));
        errorEstim = fabs(val - x2);
        resid = fabs(mainFunction(val));
        x1 = x2;
        x2 = val;

        cout << "\t" << i << "\t\t" << val << "\t\t\t" << errorEstim << "\t\t" << resid << endl;
    }

    cout << "\n\tPowod zakonczenia iteracji: ";
    if (i == nMax)
        cout << "Przekroczono dopuszczalna ilosc iteracji\n" << endl;

    else if (errorEstim <= TOLX)
        cout << "Estymator bledu jest mniejszy niz zadana tolerancja\n" << endl;

    else if (resid <= TOLF)
        cout << "Reziduum jest mniejsze niz zadana tolerancja\n" << endl;
}

int main() {
    cout << "\t\t\nFunkcja sinus:\n" << endl;
    Picard(sinFun, sinFi, sinFiDeriv, -0.5);
    Bisection(sinFun, 0.4, 0.7);
    Newton(sinFun, sinDeriv, 0.5);
    Sieczne(sinFun, -0.3, 0.3);

    cout << "\n===================================================================================================================================================================================================================\n";
    cout << "===================================================================================================================================================================================================================\n";
    cout << "\t\t\nFunkcja tangens:\n" << endl;
    Picard(tanFun, tanFi, tanFiDeriv, 0.5);
    Bisection(tanFun, 0.2, 0.7);
    Newton(tanFun, tanDeriv, 0.4);
    Sieczne(tanFun, 0.3, 0.5);
    return 0;
}