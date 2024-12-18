#include <iostream>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

// Ham tim nghich dao cua ma tran Q
MatrixXd inverseMatrix(const MatrixXd& matrix) {
    // Kiểm tra ma trận có vuông hay không
    if (matrix.rows() != matrix.cols()) {
        throw std::invalid_argument("Matrix must be square.");
    }
    // Tạo ma trận mở rộng (matrix | identity)
    int n = matrix.rows();
    MatrixXd augmented = MatrixXd::Zero(n, 2 * n);  // Ma trận mở rộng
    augmented.block(0, 0, n, n) = matrix;           // Phần bên trái là ma trận ban đầu
    augmented.block(0, n, n, n) = MatrixXd::Identity(n, n);  // Phần bên phải là ma trận đơn vị
    // Áp dụng phương pháp Gauss-Jordan
    for (int i = 0; i < n; ++i) {
        // Tìm phần tử không bằng 0 ở cột i
        if (augmented(i, i) == 0) {
            bool swapped = false;
            for (int j = i + 1; j < n; ++j) {
                if (augmented(j, i) != 0) {
                    augmented.row(i).swap(augmented.row(j));
                    swapped = true;
                    break;
                }
            }
            if (!swapped) {
                throw std::invalid_argument("Matrix is singular and cannot be inverted.");
            }
        }
        // Chuẩn hóa hàng i sao cho phần tử trên đường chéo bằng 1
        double pivot = augmented(i, i);
        augmented.row(i) /= pivot;
        // Thực hiện biến đổi hàng để làm các phần tử ngoài đường chéo bằng 0
        for (int j = 0; j < n; ++j) {
            if (j != i) {
                double factor = augmented(j, i);
                augmented.row(j) -= factor * augmented.row(i);
            }
        }
    }
    // Phần bên phải của ma trận mở rộng là ma trận nghịch đảo
    return augmented.block(0, n, n, n);
}
// Hàm tính toán xác suất sau một số bước nhất định
double calculateProbability(const MatrixXd& P, const VectorXd& initialState, int steps) {
    // Chéo hóa ma trận P
    EigenSolver<MatrixXd> solver(P);
    MatrixXd Q = solver.eigenvectors().real();         // Ma trận vector riêng (thực)
    MatrixXd Q_inv = inverseMatrix(Q);                  // Nghịch đảo ma trận Q
    // Lấy giá trị riêng (phần thực) từ solver.eigenvalues()
    VectorXd realEigenvalues = solver.eigenvalues().real(); // Giá trị riêng (phần thực)
    // Tạo ma trận đường chéo Lambda từ giá trị riêng thực
    MatrixXd Lambda(realEigenvalues.size(), realEigenvalues.size());
    for(int i = 0; i < realEigenvalues.size(); ++i) {
        for(int j = 0; j < realEigenvalues.size(); ++j) {
            if(i == j) {
                Lambda(i, j) = realEigenvalues(i);
            } else {
                Lambda(i, j) = 0;
            }
        }
    }
    // Lũy thừa ma trận đường chéo Lambda^n
    MatrixXd Lambda_n = Lambda;
    for (int i = 1; i < steps; ++i) {
        for(int j = 0; j < Lambda_n.rows(); ++j) {
            for(int k = 0; k < Lambda_n.cols(); ++k) {
                Lambda_n(j, k) = Lambda_n(j, k) * Lambda(j, k);
            }
        }
    }
    // Tính P^n = Q * Lambda^n * Q^(-1)
    MatrixXd P_n_temp(Q.rows(), Q.cols());
    //Nhan Q và Lambda_n
    for(int i = 0; i < Q.rows(); ++i) {
        for(int j = 0; j < Lambda_n.cols(); ++j) {
            P_n_temp(i, j) = 0;
            for(int k = 0; k < Q.cols(); ++k) {
                P_n_temp(i, j) += Q(i, k) * Lambda_n(k, j);
            }
        }
    }
    MatrixXd P_n(Q.rows(), Q.cols());
    //Nhan P_n_temp và Q_inv
    for(int i = 0; i < P_n.rows(); ++i) {
        for(int j = 0; j < P_n.cols(); ++j) {
            P_n(i, j) = 0;
            for(int k = 0; k < P_n_temp.cols(); ++k) {
                P_n(i, j) += P_n_temp(i, k) * Q_inv(k, j);
            }
        }
    }
    // cout << "P^n = " << endl << P_n << endl;
    // Xác suất từ "Trung bình" lên "Giàu"
    double probability = P_n(1, 0); 
    for(int i = 0; i < P_n.rows(); ++i){
        for(int j = 0; j < P_n.cols(); ++j){
            if(i==1){
                cout << "P(" << i << "|" << j << ") = " << P_n(i, j) << "\t";
            }
        }
    }
    cout << endl;
    return probability;
}

int main() {
    // Ma trận chuyển đổi trạng thái
    MatrixXd P(4, 4);
    P << 0.0, 0.75, 0.2, 0.05,  // Giàu
         0.05, 0.2, 0.3, 0.45,  // Trung bình
         0.1, 0.4, 0.3, 0.2,    // Nghèo
         0.0, 0.15, 0.3, 0.55;  // Nợ
    // Trạng thái ban đầu
    VectorXd initialState(4);
    initialState << 0.0, 1.0, 0.0, 0.0;
    // Số bước cần tính
    int steps = 5;
    cout << "Xác suất từ bình dân lên giàu: " << endl;
    for(int i = 1; i <= steps; ++i) {
        double probability = calculateProbability(P, initialState, i);
        cout << "Xác suất sau " << i << " bước: " << probability << endl;
    }
    return 0;
}