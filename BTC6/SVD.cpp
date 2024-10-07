#include<cmath>
#include<iostream>
#include<algorithm>
#include<vector>
#include<utility>
#include<string>
#include<math.h>
#include<numeric>
#include<iterator>
#include<Eigen/Eigenvalues>
#include<Eigen/Dense>
using namespace std;
using namespace Eigen;
void transpose(MatrixXd& V, MatrixXd& V1, int row, int col) {
    for (int i = 0; i < col; i++) {
        for (int j = 0; j < row; j++) {
            V1(i, j) = V(j, i);
        }
    }
}
void reverse_matrix(MatrixXd& matrix) {
    for (int j = 0; j < matrix.cols() / 2; ++j)
        for (int i = 0; i < matrix.rows(); ++i) {
            swap(matrix(i, j), matrix(i, matrix.cols() - 1 - j));
    }
}
double matrixMultiply(VectorXd v1, VectorXd v2, int n) {
    double ans = 0;
    if (v1.size() != v2.size()) return 1;
    else {
        for (int i = 0; i < n; ++i)
            ans = ans + (v1[i] * v2[i]);
    return ans;
    }
}
int main()
{
    int m, n;
    cout << "Number of rows: " << endl;
    cin >> m;
    cout << "Number of columns" << endl;
    cin >> n;
    MatrixXd A(m, n), At(n, m);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int x;
            cout << "A["<<i+1<<"]"<<"["<<j+1<<"]= ";
            cin >> x;
            A(i, j) = x;
        }
    }
    transpose(A, At, m, n);
    MatrixXd U(m, m), D(m, n), V(n, n), VT(n, n), ATA;
    U.setZero();
    VT.setZero();
    D.setZero();
    ATA = At * A;
    cout << ATA << '\n';
    SelfAdjointEigenSolver<MatrixXd> eigensolver(ATA);
    V = eigensolver.eigenvectors();
    reverse_matrix(V);
    MatrixXd hold1 = eigensolver.eigenvalues().matrix();
    vector<long double> a;
    for (int i = 0; i < hold1.size(); i++) {
        if (hold1(i, 0) > 10e-10) {
            a.push_back((hold1(i, 0)));
        }
    }
    sort(a.rbegin(), a.rend());
    int pos = a.size();
    for (int i = 0; i < a.size(); i++) {
        D(i, i) = sqrt(a[i]);
    }
    for (int i = 0; i < a.size(); i++) {
    MatrixXd Ui = (1.0 / D(i, i)) * A * V.col(i);
        for (int j = 0; j < m; j++) {
            U(j, i) = Ui(j, 0);
        }
    }
    while (pos < m) {
        MatrixXd e3(m, 1);
        for (int i = 0; i < m; i++) {
            e3(i, 0) = 0;   
        }
        e3(pos, 0) = 1;
        MatrixXd Ui = e3;
        for (int i = 0; i < pos; i++) {
        MatrixXd ui = U.col(i);
        ui = (matrixMultiply(e3, ui, m) / matrixMultiply(ui, ui, m)) * ui;
        Ui = Ui - ui;
        }
        cout << Ui << endl;
        long double chuanhoa = 0;
        for (int i = 0; i < Ui.rows(); i++) {
            chuanhoa += Ui(i, 0) * Ui(i, 0);
        }
        for (int j = 0; j < m; j++) {
        U(j, pos) = Ui(j, 0) / sqrt(chuanhoa);
        }
        pos++;
    }
    cout << "Matrix U: " << endl << U << endl;
    cout << "Matrix D: " << endl << D << endl;
    cout << "Matrix V: " << endl << V << endl;
    transpose(V, VT, n, n);
    cout << "Matrix VT: " << endl << VT << endl;
    MatrixXd AA = U * D * VT;
    cout << "Matrix A = U * D * VT : " << endl << AA << endl;
    AA = AA - A;
    cout << "Test secure A - (U * D * VT): " << endl << AA << endl;
}