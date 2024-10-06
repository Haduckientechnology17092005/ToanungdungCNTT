#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

#define PI 3.14159265
#define MAX_SIZE 10

using namespace std;

typedef double matrix[MAX_SIZE][MAX_SIZE];
double B1[10][10] = {{1,0,0},{0,1,0},{0,0,1}};

void inputMatrix(int n, matrix A);
void outputMatrix(int n, const matrix A);
void multiMatrix(const matrix A, const matrix B, matrix C, int cola, int rowa, int rowb);
void Danhilepski(matrix A, matrix M, matrix M1, matrix B, int n);
void solution(double a, double b, double c, double d, double x[]);
double determinant(const matrix A, int n);
bool invertMatrix(const matrix A, matrix inverse, int n);

void inputMatrix(int n, matrix A) {
    cout << "Enter matrix elements:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> A[i][j];
        }
    }
}

void outputMatrix(int n, const matrix A) {
    cout << fixed << setprecision(2); 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
}

void multiMatrix(const matrix A, const matrix B, matrix C, int cola, int rowa, int rowb) {
    for (int i = 0; i < cola; i++) {
        for (int j = 0; j < rowb; j++) {
            C[i][j] = 0;
            for (int k = 0; k < rowa; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void Danhilepski(matrix A, matrix M, matrix M1, matrix B, int n) {
    for (int k = n - 2; k >= 0; k--) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != k) {
                    if (i == j) {
                        M[i][j] = 1;
                        M1[i][j] = 1;
                    } else {
                        M[i][j] = 0;
                        M1[i][j] = 0;
                    }
                } else {
                    M1[i][j] = A[k+1][j];
                    if (j == k) {
                        M[i][j] = 1 / A[k+1][k];
                    } else {
                        M[i][j] = -A[k+1][j] / A[k+1][k];
                    }
                }
            }
        }
        multiMatrix(A, M, B, n,n,n);
        multiMatrix(M1, B, A, n, n, n);
        multiMatrix(B1, M, B, n, n, n);
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                B1[i][j] = B[i][j];
            }
        }
    }
}

double determinant(const matrix A, int n) {
    double det = 0;
    if (n == 1) {
        return A[0][0];
    }
    if (n == 2) {
        return A[0][0] * A[1][1] - A[0][1] * A[1][0];
    }

    matrix temp;
    for (int f = 0; f < n; f++) {
        int temp_i = 0;
        for (int i = 1; i < n; i++) {
            int temp_j = 0;
            for (int j = 0; j < n; j++) {
                if (j == f) continue;
                temp[temp_i][temp_j] = A[i][j];
                temp_j++;
            }
            temp_i++;
        }
        det += (f % 2 == 0 ? 1 : -1) * A[0][f] * determinant(temp, n - 1);
    }
    return det;
}

bool invertMatrix(const matrix A, matrix inverse, int n) {
    double det = determinant(A, n);
    if (det == 0) {
        cout << "Matrix is singular and cannot be inverted." << endl;
        return false;
    }

    matrix adjoint;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix temp;
            int temp_i = 0;
            for (int x = 0; x < n; x++) {
                for (int y = 0; y < n; y++) {
                    if (x != i && y != j) {
                        temp[temp_i][temp_i++] = A[x][y];
                    }
                }
                temp_i++;
            }
            adjoint[j][i] = (pow(-1, i + j) * determinant(temp, n - 1)) / det; // Adjoint transpose
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            inverse[i][j] = adjoint[i][j];
        }
    }
    return true;
}

void solution(double a, double b, double c, double d, double x[]) {
    double delta = b*b - 3*a*c;
    double k = (9*a*b*c - 2*b*b*b - 27*a*a*d) / (2 * sqrt(fabs(delta*delta*delta)));
    if(delta>0){
        if(-1 <= k && k <= 1){
            x[0] = (2*sqrt(delta)*cos(acos(k)/3)-b)/(3*a);
            x[1] = (2*sqrt(delta)*cos((acos(k)-2*PI)/3)-b)/(3*a);
            x[2] = (2*sqrt(delta)*cos((acos(k)+2*PI)/3)-b)/(3*a);
        }
        if(k < -1 || k > 1){
            k = (k < 0) ? -k : k;
            double l = (sqrt(delta)*k) / 3*a*k;
            double j = (k+sqrt(k*k-1));
            double i = (k-sqrt(k*k-1));
            double h;
            if(i<0){
                i = -i;
                if(j<0)
                    h = -pow(fabs(j), 1.0/3.0) - pow(i, 1.0/3.0);
                if(j>=0)
                    h = pow(j, 1.0/3.0) - pow(i, 1.0/3.0);
            } else {
                if(j<0)
                    h = -pow(fabs(j), 1.0/3.0) + pow(i, 1.0/3.0);
                if(j>=0)
                    h = pow(j, 1.0/3.0) + pow(i, 1.0/3.0);
            }
            x[0] = 1.0*h-b/(3*a);
        }
    }
    if(delta == 0){
        double l = b*b*b - 27*a*a*d;
        if(l<0){
            l = -l;
            x[0] = (-b -pow(1, 1.0/3.0))/(3*a);
        } else {
            x[0] = (-b +pow(1, 1.0/3.0))/(3*a);
        }
    }
    if(delta < 0){
        delta = delta * (-1.0);
        double j = k + sqrt(k*k+1);
        double i = k - sqrt(k*k+1);
        double h;
        if(i<0){
            i = -i;
            if(j<0)
                h = -pow(fabs(j), 1.0/3.0) - pow(i, 1.0/3.0);
            if(j>=0)
                h = pow(j, 1.0/3.0) - pow(i, 1.0/3.0);
        } else {
            if(j<0)
                h = -pow(fabs(j), 1.0/3.0) + pow(i, 1.0/3.0);
            if(j>=0)
                h = pow(j, 1.0/3.0) + pow(i, 1.0/3.0);
        }
        x[0] = sqrt(delta)*cosh(h)-b/(3*a);
    }
}

int main() {
    int n;
    cout << "Enter the size of the square matrix: ";
    cin >> n;

    matrix A;
    inputMatrix(n, A);
    
    cout << "The matrix you entered is: " << endl;
    outputMatrix(n, A);

    matrix inverse;
    if (invertMatrix(A, inverse, n)) {
        cout << "The inverse of the matrix is: " << endl;
        outputMatrix(n, inverse);
    }

    return 0;
}
