#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
    cout << scientific << setprecision(16); // ustawiam precyzję wyświetlania wartości

    //dla float
    int floatCounter = 0;
    float floatStep = 1.0f, floatValue = 2.0f;
    while (floatValue > 1.0) {  //pętlę powtarzam do momentu dotarcia do limitu precyzji
        floatStep /= 2;
        floatValue = 1.0 + floatStep;
        if (floatValue > 1.0)
            floatCounter++;
    }
    //liczba bitów mantysy jest równa wartości zmiennej floatCounter
    //wartość zmiennej floatStep jest równa wartości Ni, wartość epsilona maszynowego to 2*Ni
    float floatEps = 2.0 * floatStep;

    //dla double
    int doubleCounter = 0;
    double doubleStep = 1.0f, doubleValue = 2.0;
    while (doubleValue > 1.0) {  //pętlę powtarzam do momentu dotarcia do limitu precyzji
        doubleStep /= 2;
        doubleValue = 1.0 + doubleStep;
        if (doubleValue > 1.0)
            doubleCounter++;
    }
    //liczba bitów mantysy jest równa wartości zmiennej doubleCounter
    //wartość zmiennej doubleStep jest równa wartości Ni, wartość epsilona maszynowego to 2*Ni
    float doubleEps = 2.0 * doubleStep;

    //Wyswietlanie wyników
    cout << "\t\t\t\t|Float\t\t\t|Double\t\t\t|" << endl;
    cout << "\t\t\t\t|-----------------------|-----------------------|" << endl;
    cout << "Liczba bitow mantysy: \t\t|" << floatCounter << "\t\t\t|" << doubleCounter << "\t\t\t|" << endl;
    cout << "Wartosc epsylona maszynowego: \t|" << floatEps << "\t|" << doubleEps << "\t|" << endl;
    return 0;
}
