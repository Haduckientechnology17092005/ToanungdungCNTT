#include<iostream>
#include<cmath>
#include<cstring>
#include<stdlib.h>
#include<iomanip>

using namespace std;

double L[4][4], D[4];
void inputMatrix(double A[4][4], int n, int m);
bool checkMatrixCholesky(double A[4][4], int n, int m);
bool SymmetricalMatrix(double A[4][4], int n);
void CholeskyLDL_Decomposition(double A[4][4], double L[4][4], double D[4], int n);
void printMatrix(double L[4][4], double D[4], int n);

int main(){
    double A[4][4];
    int n, m;
    cout << "Enter a number n: ";
    cin >> n;
    cout << "Enter a number m: ";
    cin >> m;
    cout<<fixed<<setprecision(2);
    inputMatrix(A, n, m);
    if(!checkMatrixCholesky(A, n, m)){
        cout << "Matrix is not positive definite\n";
        return 0;
    } else {
        CholeskyLDL_Decomposition(A, L, D, n);
    }
    printMatrix(L, D, n);
    return 0;
}

void inputMatrix(double A[4][4], int n, int m){
    if(n != m){
        cout << "Matrix is not square\n";
        return;
    }
    cout << "Enter matrix A: \n";
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cout << "Enter A[" << i << "][" << j << "]: ";
            cin >> A[i][j];
        }
    }
}

bool SymmetricalMatrix(double A[4][4], int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(A[i][j] != A[j][i]){
                return false;
            }
        }
    }
    return true;
}

bool checkMatrixCholesky(double A[4][4], int n, int m){
    if(n != m){
        return false;
    }
    if(!SymmetricalMatrix(A, n)){
        return false;
    }
    return true;
}

void CholeskyLDL_Decomposition(double A[4][4], double L[4][4], double D[4], int n){
    memset(L, 0, sizeof(double) * 4 * 4);
    for (int j = 0; j < n; j++){
        for (int k = 0; k < j; k++){
            A[j][j] -= L[j][k] * L[j][k] * D[k];
        }
        D[j] = A[j][j];
        for(int i = j + 1; i < n; i++){
            L[i][j] = A[i][j];
            for(int k = 0; k < j; k++){
                L[i][j] -= L[i][k] * L[j][k] * D[k];
            }
            L[i][j] /= D[j];
        }
        L[j][j] = 1.0;
    }
}

#include <iostream>
#include <iomanip> // thêm để dùng hàm setprecision và setw
using namespace std;

void printMatrix(double L[4][4], double D[4], int n) {
    cout << "Matrix L | D | L^T\n";
    cout << fixed << setprecision(2);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j > i)
                cout << setw(6) << "0.00" << " ";
            else
                cout << setw(6) << L[i][j] << " ";
        }
        cout << " | ";
        for (int j = 0; j < n; j++) {
            if (i == j)
                cout << setw(6) << D[i] << " ";
            else
                cout << setw(6) << "0.00" << " ";
        }
        cout << " | ";
        for (int j = 0; j < n; j++) {
            if (j < i)
                cout << setw(6) << "0.00" << " ";
            else
                cout << setw(6) << L[j][i] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

