#include<iostream>
#include<cmath>
#include<cstring>
#include<iomanip>

using namespace std;

double L[4][4];
void inputMatrix(double A[4][4], int n, int m);
bool checkMatrixCholesky(double A[4][4], int n, int m);
bool SymmetricalMatrix(double A[4][4], int n);
void swap(double &a, double &b);
float DetMatrix(double A[4][4], int n);
bool checkpositive(double A[4][4], int n);
void Cholesky_Decomposition(double A[4][4], int n);
void printMatrix(double A[4][4], int n);

int main(){
    double A[4][4];
    int n, m;
    cout<<"Enter n: ";
    cin>>n;
    cout<<"Enter m: ";
    cin>>m;
    inputMatrix(A,n,m);
    if(!checkMatrixCholesky(A, n, m)){
        cout<<"Matrix is not positive definite\n";
        return 0;
    } else {
        Cholesky_Decomposition(A, n);
    }
    printMatrix(L, n);
    return 0;
}

void inputMatrix(double A[4][4], int n, int m){
    if(n != m){
        cout<<"Matrix is not square\n";
        return;
    }
    cout<<"Enter matrix A: \n";
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cout<<"Enter A["<<i<<"]["<<j<<"]: ";
            cin>>A[i][j];
        }
    }
}

bool checkMatrixCholesky(double A[4][4], int n, int m){
    if(n != m){
        return false;
    }
    if(!SymmetricalMatrix(A, n)){
        return false;
    }
    if(!checkpositive(A, n)){
        return false;
    }
    return true;
}

bool SymmetricalMatrix(double A[4][4], int n){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(A[i][j] != A[j][i]){
                return false;
            }
        }
    }
    return true;
}

void swap(double &a, double &b){
    double temp = a;
    a = b;
    b = temp;
}
float DetMatrix(double A[4][4], int n){
    double temp[4][4];
    memcpy(temp, A, sizeof(double) * 4 * 4);
    float det = 1.0;
    for(int i=0; i<n; i++){
        if(temp[i][i] == 0){
            int check = 0;
            for(int j=i+1; j<n; j++){
                if(temp[j][i] != 0){
                    for(int k=0; k<n; k++){
                        swap(temp[i][k], temp[j][k]);
                    }
                    check = 1;
                    det *= -1; 
                    break;
                }
            }
            if(check == 0){
                return 0;
            }
        }
        for (int j=i+1; j<n; j++){
            float h = -temp[j][i] / temp[i][i];
            for(int k = i; k<n; k++){
                temp[j][k] += h * temp[i][k];
            }
        }
        det *= temp[i][i];
    }
    return det;
}

bool checkpositive(double A[4][4], int n){
    double subMatrix[4][4];
    
    for(int k = 1; k <= n; k++){
        for(int i = 0; i < k; i++){
            for(int j = 0; j < k; j++){
                subMatrix[i][j] = A[i][j];
            }
        }
        if(DetMatrix(subMatrix, k) <= 0){
            return false;
        }
    }
    return true;
}

void Cholesky_Decomposition(double A[4][4], int n){
    memset(L, 0, sizeof(L));
    for(int i=0; i<n; i++){
        for(int j = 0; j<=i; j++){
            double sum = 0;
            if(i == j){
                for(int k = 0; k<j; k++){
                    sum += L[j][k] * L[j][k];
                }
                L[j][j] = sqrt(A[j][j] - sum);
            } else {
                for(int k = 0; k<j; k++){
                    sum += L[i][k] * L[j][k];
                }
                L[i][j] = (A[i][j] - sum) / L[j][j];
            }
        }
    }
}

void printMatrix(double A[4][4], int n) {
    cout << "Matrix L and L^T: \n";
    cout << fixed << setprecision(2);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j > i)
                cout << setw(6) << "0.00" << " "; 
            else
                cout << setw(6) << A[i][j] << " "; 
        }
        cout<<" | ";
        for (int k = 0; k < n; k++) {
            if (k < i)
                cout << setw(6) << "0.00" << " ";
            else
                cout << setw(6) << A[k][i] << " "; 
        }
        cout << "\n";
    }
    cout << "\n";
}
