#include <Eigen/Dense>
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;
using namespace Eigen;

void swap(double &a, double &b);
void inputMatrix(double A[][4], int row, int col);
void showMatrix(double A[][4], int row, int col);
void transpose(double A[][4], double B[][4], int row, int col);
void multiplyMatrix(MatrixXd &S, double B[][4], double C[][4], int row1, int col1, int col2);
void getEigenValuesAndVectors(MatrixXd S, MatrixXd &lambda, MatrixXd &vector);
void matrixS(MatrixXd lambda, double sigma[][4], int row, int col);
void matrixU(MatrixXd lambda, MatrixXd vector, double U[][4], double A[][4], int rows, int cols);
void matrixV(MatrixXd vector, double V[][4]);

int main() {
    int rows, cols;
    double A[4][4], At[4][4];
    cout << "Enter the number of rows and columns: \n";
    cout << "Rows: ";
    cin >> rows;
    cout << "Columns: ";
    cin >> cols;
    inputMatrix(A, rows, cols);
    
    MatrixXd S(cols, cols), lambda(cols, 1), vector(cols, cols);
    transpose(A, At, rows, cols);
    multiplyMatrix(S, At, A, cols, rows, cols);
    getEigenValuesAndVectors(S, lambda, vector);
    
    double sigma[4][4], U[4][4], V[4][4];
    matrixU(lambda, vector, U, A, rows, cols);
    
    cout << "Matrix U: \n";
    showMatrix(U, rows, rows);
    
    matrixS(lambda, sigma, rows, cols);
    cout << "Matrix S: \n";
    showMatrix(sigma, rows, cols);
    
    matrixV(vector, V);
    double Vt[4][4];
    transpose(V, Vt, cols, cols);
    
    cout << "Matrix VT: \n";
    showMatrix(Vt, cols, cols);
    
    return 0;
}

void inputMatrix(double A[][4], int row, int col) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cout << "Enter the element: ";
            cin >> A[i][j];
        }
    }
}

void swap(double &a, double &b) {
    double temp = a;
    a = b;
    b = temp;
}

void showMatrix(double A[][4], int row, int col) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cout << setw(9) << setprecision(3) << A[i][j];
        }
        cout << endl;
    }
}

void transpose(double A[][4], double B[][4], int row, int col) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            B[j][i] = A[i][j];
        }
    }
}

void multiplyMatrix(MatrixXd &S, double B[][4], double C[][4], int row1, int col1, int col2) {
    for (int i = 0; i < row1; i++) {
        for (int j = 0; j < col2; j++) {
            double sum = 0;
            for (int k = 0; k < col1; k++) {
                sum += B[i][k] * C[k][j];
            }
            S(i, j) = sum;
        }
    }
}

void getEigenValuesAndVectors(MatrixXd S, MatrixXd &lambda, MatrixXd &vector) {
    SelfAdjointEigenSolver<Eigen::MatrixXd> eigensolver(S);
    vector = eigensolver.eigenvectors();
    lambda = eigensolver.eigenvalues();
    
    int k = lambda.rows();
    int l = vector.cols();
    
    for (int i = 0; i < k; i++) {
        if (lambda(i, 0) < 0.00001) {
            lambda(i, 0) = 0;
        }
    }
    for (int i = 0; i < k; i++) {
        for (int j = i + 1; j < k; j++) {
            if (lambda(j, 0) >= lambda(i, 0)) {
                swap(lambda(i, 0), lambda(j, 0));
                for (int h = 0; h < l; h++) {
                    swap(vector(h, i), vector(h, j));
                }
            }
        }
    }
}

void matrixU(MatrixXd lambda, MatrixXd vector, double U[][4], double A[][4], int rows, int cols) {
    MatrixXd ui(rows, 1);
    double Vi[4][4];
    
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < cols; j++) {
            Vi[j][0] = vector(j, i);
        }
        multiplyMatrix(ui, A, Vi, rows, cols, 1);
        for (int k = 0; k < rows; k++) {
            if (lambda(i, 0) != 0) {
                U[k][i] = (1 / sqrt(lambda(i, 0))) * ui(k, 0);
            } else {
                k = rows;
            }
        }
    }
    for (int i = 0; i < rows; i++) {
        if (lambda(i, 0) == 0) {
            MatrixXd A1(rows - 1, rows);
            MatrixXd B(rows - 1, 1), x1(rows, 1);
            for(int k = 0; k<rows; k++){
                B(k, 0) = 0;
            }
            for(int j = 0; j<rows-1; j++){
                for(int h = 0; h<rows; h++){
                    if(j != i)
                        A1(j, h) = U[h][j];
                }
            }
            x1 = A1.colPivHouseholderQr().solve(B);
            for (int k = 0; k < rows; k++) {
                U[k][i] = x1(k, 0);
            }
        }
    }
}

void matrixV(MatrixXd vector, double V[][4]) {
    int row = vector.rows();
    int col = vector.cols();
    
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            V[i][j] = vector(i, j);
        }
    }
}

void matrixS(MatrixXd lambda, double sigma[][4], int row, int col) {
    int k = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (i != j) {
                sigma[i][j] = 0;
            } else {
                sigma[i][j] = sqrt(lambda(k, 0));
                k++;
            }
        }
    }
}
