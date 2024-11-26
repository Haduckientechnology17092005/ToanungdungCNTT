#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

// Hàm mục tiêu
double objectiveFunction(const VectorXd& x) {
    double x1 = x[0];
    double x2 = x[1];
    return 5 * x1 + 10 * x2 + 5 * x1 * x2 - 4 * x1 * x1 - 6 * x2 * x2;
}

// Gradient của hàm mục tiêu
VectorXd gradient(const VectorXd& x) {
    VectorXd grad(2);
    grad[0] = 5 + 5 * x[1] - 8 * x[0]; // ∂f/∂x
    grad[1] = 10 + 5 * x[0] - 12 * x[1]; // ∂f/∂y
    return grad;
}

// Hessian của hàm mục tiêu
MatrixXd hessian(const VectorXd& x) {
    MatrixXd hess(2, 2);
    hess(0, 0) = -8; // ∂²f/∂x²
    hess(0, 1) = 5;  // ∂²f/∂x∂y
    hess(1, 0) = 5;  // ∂²f/∂y∂x
    hess(1, 1) = -12; // ∂²f/∂y²
    return hess;
}

// Hàm tối ưu hóa Newton-Raphson
VectorXd optimize(const VectorXd& initialGuess, int maxIter = 100, double tol = 1e-6) {
    VectorXd x = initialGuess;
    for (int iter = 0; iter < maxIter; ++iter) {
        VectorXd grad = gradient(x);
        MatrixXd hess = hessian(x);
        
        if (grad.norm() < tol) {
            cout << "Đạt hội tụ sau " << iter << " lần lặp." << endl;
            return x;
        }
        
        VectorXd deltaX = hess.ldlt().solve(-grad); // Giải hệ phương trình Hessian * deltaX = -Gradient
        x += deltaX;
    }
    cout << "Không hội tụ sau " << maxIter << " lần lặp." << endl;
    return x;
}

int main() {
    VectorXd initialGuess(2);
    initialGuess << 1.0, 1.0; // Giá trị khởi tạo
    
    VectorXd result = optimize(initialGuess);
    
    cout << "Điểm tối ưu: " << result.transpose() << endl;
    cout << "Giá trị hàm tại điểm tối ưu: " << objectiveFunction(result) << endl;
    
    return 0;
}
