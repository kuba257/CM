#include <iostream>
#include <iomanip>
using namespace std;

#define DiagonalDim 6

void printVector(const double* vector) {
    for (int i = 0; i < DiagonalDim; i++)
        cout << vector[i] << setw(12);
    cout << endl;
}

void matrixThomas(const double* L, const double* U,  double* D) {
    for (int i = 1; i < DiagonalDim; i++)
        D[i] -= L[i-1] * U[i - 1] / D[i - 1];
}

void vectorThomas(const double* L, const double* D, double* b){
    for (int i = 1; i < DiagonalDim; i++) {
        b[i] -= L[i-1] * b[i - 1] / D[i - 1];
    }
}

void calcX(const double* b, const double* U, const double* D, double* X) {
    X[DiagonalDim - 1] = b[DiagonalDim - 1] / D[DiagonalDim - 1];
    for (int i = DiagonalDim - 2; i >= 0; i--)
        X[i] = (b[i] - (U[i] * X[i + 1])) / D[i];
}
int main()
{
    double U[] = { 1.0 / 2.0, 1.0 / 4.0, 1.0 / 6.0, 1.0 / 8.0, 1.0 / 10.0 };
    double D[] = { 10.0, 20.0, 30.0, 30.0, 20.0, 10.0 };
    double L[] = { 1.0 / 3.0, 1.0 / 5.0, 1.0 / 7.0, 1.0 / 9.0, 1.0 / 11.0 };
    double b[] = { 31.0, 165.0 / 4.0, 917.0 / 30.0, 851.0 / 28.0, 3637.0 / 90.0, 332.0 / 11.0 };
    double X[6] = { 0.0, };

    int UCounter = 0;
    int LCounter = 0;
    
    for (int i = 0; i < DiagonalDim; i++) {
        for (int j = 0; j < DiagonalDim; j++) {
            if (i == j)
                cout << setw(12) << D[i];
            else if (i - j == 1) {
                cout << setw(12) << L[LCounter];
                LCounter++;
            }
            else if (i - j == -1) {
                cout << setw(12) << U[UCounter];
                UCounter++;
            }
            else
                cout << "\t" << "";
        }
        cout << endl;
    }

    matrixThomas(L, U, D);
    vectorThomas(L, D, b);
    calcX(b, U, D, X);
    
    cout << "\nWektor b:" << endl;
    printVector(b);
    cout << "\nWektor X:" << endl;
    printVector(X);
    cout << "\nWartosci na przekatnej:" << endl;
    printVector(D);
    
    return 0;
}
