#include <iostream>
#include <Eigen/Dense>
#include <iomanip>
#include <cmath>

using namespace std;
using namespace Eigen; 

// g++ -I C:/Users/Loc/eigen "SVD.cpp" -o "SVD"

// Function declarations
void inputMatrix(double matrix[][10], int &rows, int &cols);
void displayMatrix(double matrix[][10], int row, int col);
void transposeMatrix(double source[][10], double destination[][10], int rows, int cols);
void matrixMultiplication(MatrixXd &result, double A[][10], double B[][10], int rowA, int colA, int colB);
void computeEigen(MatrixXd S, MatrixXd &eigenValues, MatrixXd &eigenVectors);
void computetSigma(MatrixXd eigenValues, double sigma[][10], int rows, int cols);
void computeU(MatrixXd eigenValues, MatrixXd eigenVectors, double U[][10], double A[][10], int rows, int cols);
void gramSchmidt(double U[][10], int rows, int cols);
void computetV(MatrixXd eigenVectors, double V[][10]);
// void orthogonalize(double U[][10], int rows, int cols);
void computeSVD(double A[][10], int rows, int cols);
void verifySVD(double A[][10], double U[][10], double sigma[][10], double Vt[][10], int rows, int cols);

int main() {
    double A[10][10];
    int rows, cols;

    inputMatrix(A, rows, cols);

    computeSVD(A, rows, cols);

    return 0;
}

void inputMatrix(double matrix[][10], int &rows, int &cols) {
    cout << "Nhap kich thuoc cua ma tran:" << endl;
    cout << "So hang: "; cin >> rows;
    cout << "So cot: "; cin >> cols;

    cout << "Enter matrix A values: " << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << "A[" << i+1 << "][" << j+1 << "] = ";
            cin >> matrix[i][j];
        }
    }
}

void displayMatrix(double matrix[][10], int row, int col) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cout << setw(9) << setprecision(4) << matrix[i][j];
        }
        cout << endl;
    }
}

void transposeMatrix(double source[][10], double destination[][10], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            destination[j][i] = source[i][j];
        }
    }
}

// Matrix multiplication
void matrixMultiplication(MatrixXd &result, double A[][10], double B[][10], int rowA, int colA, int colB) {
    for (int i = 0; i < rowA; i++) {
        for (int j = 0; j < colB; j++) {
            result(i, j) = 0;
            for (int k = 0; k < colA; k++) {
                result(i, j) += A[i][k] * B[k][j];
            }
        }
    }
}
void computeEigen(MatrixXd S, MatrixXd &eigenValues, MatrixXd &eigenVectors) {
    SelfAdjointEigenSolver<MatrixXd> eigensolver(S);
    eigenVectors = eigensolver.eigenvectors();
    eigenValues = eigensolver.eigenvalues();

    for (int i = 0; i < eigenValues.rows(); i++) {
        if (eigenValues(i, 0) < 1e-6) eigenValues(i, 0) = 0;
    }
    for (int i = 0; i < eigenValues.rows(); i++) {
        for (int j = i + 1; j < eigenValues.rows(); j++) {
            if (eigenValues(j, 0) > eigenValues(i, 0)) {
                swap(eigenValues(j, 0), eigenValues(i, 0));
                for (int h = 0; h < eigenVectors.rows(); h++) {
                    swap(eigenVectors(h, i), eigenVectors(h, j));
                }
            }
        }
    }
}

void computetSigma(MatrixXd eigenValues, double sigma[][10], int rows, int cols) {
    int k = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            sigma[i][j] = (i == j && k < eigenValues.rows()) ? sqrt(eigenValues(k++, 0)) : 0;
        }
    }
}

void computeU(MatrixXd eigenValues, MatrixXd eigenVectors, double U[][10], double A[][10], int rows, int cols) {
    MatrixXd ui(rows, 1);
    double Vi[10][10];

    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < cols; j++) {
            Vi[j][0] = eigenVectors(j, i);
        }
        matrixMultiplication(ui, A, Vi, rows, cols, 1);

        for (int k = 0; k < rows; k++) {
            U[k][i] = (eigenValues(i, 0) != 0) ? ui(k, 0) / sqrt(eigenValues(i, 0)) : 0;
        }
    }

    if(rows > cols) {
        if (rows > cols) {
		MatrixXd U_matrix(rows, cols); 
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				U_matrix(i, j) = U[i][j];
			}
		}
		
		MatrixXd orthogonal_basis = U_matrix.householderQr().householderQ();  
		for (int j = cols; j < rows; j++) {
			for (int i = 0; i < rows; i++) {
				U[i][j] = orthogonal_basis(i, j);
		    	}
	    	}
    	}
    } else {
        gramSchmidt(U, rows, cols);
    }
}

void gramSchmidt(double U[][10], int rows, int cols) {
	for (int i = 0; i < cols; i++) {
        for (int j = 0; j < i; j++) {
            double dot_product = 0;
            for (int k = 0; k < rows; k++) {
                dot_product += U[k][i] * U[k][j];
            }
            for (int k = 0; k < rows; k++) {
                U[k][i] -= dot_product * U[k][j];
            }
        }
        double norm = 0;
        for (int k = 0; k < rows; k++) {
            norm += U[k][i] * U[k][i];
        }
        norm = sqrt(norm);
        if (norm > 1e-10) { 
            for (int k = 0; k < rows; k++) {
                U[k][i] /= norm;
            }
        } else {
            MatrixXd random_vector = MatrixXd::Random(rows, 1);
            for (int j = 0; j < i; j++) {
                double dot_product = 0;
                for (int k = 0; k < rows; k++) {
                    dot_product += random_vector(k, 0) * U[k][j];
                }
                for (int k = 0; k < rows; k++) {
                    random_vector(k, 0) -= dot_product * U[k][j];
                }
            }
            double random_norm = random_vector.norm();
            for (int k = 0; k < rows; k++) {
                U[k][i] = random_vector(k, 0) / random_norm;
            }
        }
    }
}

// void orthogonalize(double U[][10], int rows, int cols) {
//     for (int i = cols; i < rows; i++) {
//         for (int j = 0; j < rows; j++) {
//             U[j][i] = (i == j) ? 1 : 0;
//         }
//     }
// }

void computetV(MatrixXd eigenVectors, double V[][10]) {
    for (int i = 0; i < eigenVectors.rows(); i++) {
        for (int j = 0; j < eigenVectors.cols(); j++) {
            V[i][j] = eigenVectors(i, j);
        }
    }
}

void computeSVD(double A[][10], int rows, int cols) {
    double At[10][10];
    MatrixXd S(cols, cols), eigenValues(cols, 1), eigenVectors(cols, cols);
    double sigma[10][10], U[10][10], V[10][10];

    transposeMatrix(A, At, rows, cols);
    matrixMultiplication(S, At, A, cols, rows, cols);

    computeEigen(S, eigenValues, eigenVectors);

    computeU(eigenValues, eigenVectors, U, A, rows, cols);
    computetSigma(eigenValues, sigma, rows, cols);
    computetV(eigenVectors, V);

    cout << "Matrix U:" << endl;
    displayMatrix(U, rows, rows);
    
    cout << "Matrix Sigma:" << endl;
    displayMatrix(sigma, rows, cols);
    
    cout << "Matrix V Transposed:" << endl;
    double Vt[10][10];
    transposeMatrix(V, Vt, cols, cols);
    displayMatrix(Vt, cols, cols);

    verifySVD(A, U, sigma, Vt, rows, cols);
}

void verifySVD(double A[][10], double U[][10], double sigma[][10], double Vt[][10], int rows, int cols) {
    MatrixXd Usigma(rows, cols);
    MatrixXd A_computed(rows, cols);
    MatrixXd Vt_mat(cols, cols);

    matrixMultiplication(Usigma, U, sigma, rows, rows, cols);

    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < cols; j++) {
            Vt_mat(i, j) = Vt[i][j];
        }
    }

    A_computed = Usigma * Vt_mat;

    // cout << "Reconstructed matrix A from SVD:" << endl;
    // for (int i = 0; i < rows; i++) {
    //     for (int j = 0; j < cols; j++) {
    //         cout << setw(9) << setprecision(4) << A_computed(i, j);
    //     }
    //     cout << endl;
    // }

    bool isClose = true;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (fabs(A[i][j] - A_computed(i, j)) > 1e-6) {
                isClose = false;
                break;
            }
        }
    }

    if (isClose) {
        cout << "Phan tich SVD chinh xac. " << endl;
    } else {
        cout << "Phan tich SVD khong chinh xac." << endl;
    }
}
