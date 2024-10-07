#include <iostream>
#include <Eigen/Dense>
#include <iomanip>
#include <math.h>

using namespace std;
using namespace Eigen; 

void swap(double &a, double &b);
void display(double A[][10], int row, int col);
void chuyenvi(double A[][10], double At[][10], int rows, int cols);
void NhanMaTran(MatrixXd &S, double A[][10], double B[][10], int row1, int col1, int col2);
void GetEigenValuesAndVector(MatrixXd S, MatrixXd &lambda, MatrixXd &vector);
void tinhMatranS(MatrixXd lambda, double sigma[][10], int rows, int cols);
void tinhMatranU(MatrixXd lambda, MatrixXd vector, double U[][10], double A[][10], int rows, int cols);
void tinhMatranV(MatrixXd vector, double V[][10]);
void gramSchmidt(double U[][10], int rows, int cols);

int main() {
	int rows, cols;
	double A[10][10], At[10][10];
	cout << "ENTER MATRIX " << endl;
	cout << "ROWS: ";	cin >> rows;
	cout << "COLUMNS: ";		cin >> cols;
	cout << "ENTER MATRIX ELEMENTS: " << endl;
	for (int i=0; i<rows; i++) 
	{
		for (int j=0; j<cols; j++) 
		{
			cout << "a[" << i+1 << "][" << j + 1 << "] = ";
			cin >> A[i][j];
		}
	}
	
	MatrixXd S(cols, cols), lambda(cols, 1), vector(cols, cols);
	chuyenvi(A, At, rows, cols);
	NhanMaTran(S, At, A, cols, rows, cols);
	GetEigenValuesAndVector(S, lambda, vector);
	double sigma[10][10], U[10][10], V[10][10];
	tinhMatranU(lambda, vector, U, A, rows, cols);
	//gramSchmidt(U, rows, cols);
	cout << "MATRIX U" << endl;
	display(U, rows, rows);  
	
	tinhMatranS(lambda, sigma, rows, cols);
	cout << "MATRIX SIGMA" << endl;
	display(sigma, rows, cols);  
	
	tinhMatranV(vector, V);
	cout << "MATRIX VT" << endl;
	double VT[10][10];
	chuyenvi(V, VT, cols, cols);
	display(VT, cols, cols);
	
	return 0;
}

void display(double A[][10], int row, int col) {
	for (int i = 0; i < row; i++) 
	{
        for (int j = 0; j < col; j++)
            cout << setw(9) << fixed << setprecision(3) << A[i][j];
        cout << endl;
    }
}
void swap(double &a, double &b) {
	double temp = a;
	a = b;
	b = temp;
}
void chuyenvi(double A[][10], double At[][10], int rows, int cols) {
	for (int i=0; i<rows; i++) 
		for (int j=0; j<cols; j++) {
			At[j][i] = A[i][j];
		}
}
void NhanMaTran(MatrixXd &S, double A[][10], double B[][10], int row1, int col1, int col2) {
	for (int i=0; i<row1; i++) {
		for (int j=0; j<col2; j++) {
			S(i,j) = 0;
			for (int k=0; k<col1; k++) {
				S(i,j) = S(i,j) + A[i][k] * B[k][j];
			}
		}
	}
}
void GetEigenValuesAndVector(MatrixXd S, MatrixXd &lambda, MatrixXd &vector) {
	SelfAdjointEigenSolver<Eigen::MatrixXd> eigensolver(S);
	vector = eigensolver.eigenvectors();
	lambda = eigensolver.eigenvalues();
	int k = lambda.rows();
	int l = vector.rows();
	for (int i=0; i<k; i++) 
	{
		if (lambda(i, 0) < 0.000001) 
			lambda(i, 0) = 0;
	}
    for (int i = 0; i < k; i++)
        for (int j = i + 1; j < k; j++)
        {
            if (lambda(j, 0) > lambda(i, 0))
            {
                swap(lambda(j, 0), lambda(i, 0));
                for (int h = 0; h < l; h++)
                    swap(vector(h, i), vector(h, j));
            }
        }
}
void tinhMatranU(MatrixXd lambda, MatrixXd vector, double U[][10], double A[][10], int rows, int cols) {
    MatrixXd ui(rows, 1);
    double Vi[cols][10];
    
    for (int i = 0; i < cols; i++) { 
        for (int j = 0; j < cols; j++) {
            Vi[j][0] = vector(j, i);  
        }   
        NhanMaTran(ui, A, Vi, rows, cols, 1);
        for (int k = 0; k < rows; k++) {
            if (lambda(i, 0) != 0) {
                U[k][i] = (1 / sqrt(lambda(i, 0))) * ui(k, 0);
            } else {
                U[k][i] = 0;
            }
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

void tinhMatranV(MatrixXd vector, double V[][10]) {
	int row = vector.rows(), col = vector.cols();
	for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            V[i][j] = vector(i, j);
        }
    }
}
void tinhMatranS(MatrixXd lambda, double sigma[][10], int rows, int cols){
    int k = 0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
        {
            sigma[i][j] = (i != j) ? 0 : sqrt(lambda(k, 0));
            if (i == j)
                k++;
        }
}
