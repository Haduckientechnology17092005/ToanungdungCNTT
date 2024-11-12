// #include <iostream>
// #include <Eigen/Dense>
// #include <cmath>
// #include <vector>

// using namespace std;
// using namespace Eigen;

// // Objective function: f(x) = 2 * x[0] + x[1] + 10 (example for two variables)
// double objective(const VectorXd& vars) {
//     return (2 * vars(0) + vars(1) + 10);
// }

// // Constraint function: g(x) = x[0]^2 + 2 * x[1]^2 - 3 = 0
// double constraint(const VectorXd& vars) {
//     return pow(vars(0), 2) + 2 * pow(vars(1), 2) - 3;
// }

// // Gradient of the Lagrangian function
// VectorXd lagrange_grad(const VectorXd& vars, const double lambda, const vector<double>& constraint_coeffs) {
//     VectorXd grad(vars.size() + 1);
//     grad.setZero();

//     // Gradient of the objective function components
//     grad(0) = 2 + lambda * 2 * vars(0);  // dL/dx1
//     grad(1) = 1 + lambda * 4 * vars(1);  // dL/dx2

//     // Constraint equation as a part of the gradient
//     grad(vars.size()) = constraint(vars);
//     return grad;
// }

// // Jacobian matrix of the gradient system (partial derivatives of grad vector)
// MatrixXd lagrange_jacobian(const VectorXd& vars, const double lambda, const vector<double>& constraint_coeffs) {
//     int n = vars.size();
//     MatrixXd jacobian(n + 1, n + 1);
//     jacobian.setZero();

//     jacobian(0, 0) = lambda * 2;           // ∂²L/∂x1²
//     jacobian(0, n) = 2 * vars(0);          // ∂²L/∂x1∂λ
//     jacobian(1, 1) = lambda * 4;           // ∂²L/∂x2²
//     jacobian(1, n) = 4 * vars(1);          // ∂²L/∂x2∂λ
//     jacobian(n, 0) = 2 * vars(0);          // ∂g/∂x1
//     jacobian(n, 1) = 4 * vars(1);          // ∂g/∂x2
//     return jacobian;
// }

// // Newton-Raphson solver for Lagrange multiplier system
// void solve_lagrange(VectorXd& vars, double& lambda) {
//     double tolerance = 1e-6;
//     int max_iterations = 1000;

//     vars = VectorXd::Constant(2, 2); // Initial guess for x variables
//     lambda = -0.5; // Initial guess for lambda

//     vector<double> constraint_coeffs(vars.size());  // Constraint coefficients, could extend for additional constraints

//     for (int iter = 0; iter < max_iterations; iter++) {
//         VectorXd grad = lagrange_grad(vars, lambda, constraint_coeffs);
//         MatrixXd jacobian = lagrange_jacobian(vars, lambda, constraint_coeffs);

//         if (grad.norm() < tolerance) {
//             break;
//         }

//         // Solve for the step update: J * delta = -grad
//         VectorXd delta = jacobian.colPivHouseholderQr().solve(-grad);

//         // Update variables
//         vars(0) += delta(0);
//         vars(1) += delta(1);
//         lambda += delta(2);

//         cout << "Iteration " << iter + 1 << ": x1 = " << vars(0) << ", x2 = " << vars(1)
//              << ", lambda = " << -lambda << endl;
//     }
// }
// void solve_lagrange1(VectorXd& vars, double& lambda) {
//     double tolerance = 1e-6;
//     int max_iterations = 1000;

//     vars = VectorXd::Constant(2, -2); // Initial guess for x variables
//     lambda = -0.5; // Initial guess for lambda

//     vector<double> constraint_coeffs(vars.size());  // Constraint coefficients, could extend for additional constraints

//     for (int iter = 0; iter < max_iterations; iter++) {
//         VectorXd grad = lagrange_grad(vars, lambda, constraint_coeffs);
//         MatrixXd jacobian = lagrange_jacobian(vars, lambda, constraint_coeffs);

//         if (grad.norm() < tolerance) {
//             break;
//         }

//         // Solve for the step update: J * delta = -grad
//         VectorXd delta = jacobian.colPivHouseholderQr().solve(-grad);

//         // Update variables
//         vars(0) += delta(0);
//         vars(1) += delta(1);
//         lambda += delta(2);

//         cout << "Iteration " << iter + 1 << ": x1 = " << vars(0) << ", x2 = " << vars(1)
//              << ", lambda = " << -lambda << endl;
//     }
// }
// int main() {
//     VectorXd vars(2); // Variables x1 and x2
//     double lambda;

//     // Solve the optimization problem
//     solve_lagrange(vars, lambda);

//     cout << "Optimal point: x1 = " << vars(0) << ", x2 = " << vars(1) << endl;
//     cout << "Maximum value of f(x1, x2): " << objective(vars) << endl;
//     cout << "Lagrange Multiplier (lambda): " << -lambda << endl;
//     solve_lagrange1(vars, lambda);

//     cout << "Optimal point: x1 = " << vars(0) << ", x2 = " << vars(1) << endl;
//     cout << "Minimum value of f(x1, x2): " << objective(vars) << endl;
//     cout << "Lagrange Multiplier (lambda): " << -lambda << endl;

//     return 0;
// }
// // g++ -I /usr/include/eigen3 /media/haduckien/E/Studying/HK3/Mathmetics\ for\ CS\ \(3\)/BTC9/LM.cpp -o LM
// #include <iostream>
// #include <Eigen/Dense>
// #include <cmath>
// #include <vector>

// using namespace std;
// using namespace Eigen;

// // Hàm mục tiêu: f(x) = 2 * x[0] + x[1] + 10
// double objective(const VectorXd& vars) {
//     return -(2 * vars(0) + vars(1) + 10);  // Cực tiểu hóa
// }

// // Hàm ràng buộc: g(x) = x[0]^2 + 2 * x[1]^2 - 3 = 0
// double constraint(const VectorXd& vars) {
//     return pow(vars(0), 2) + 2 * pow(vars(1), 2) - 3;
// }

// // Gradient của hàm Lagrange
// VectorXd lagrange_grad(const VectorXd& vars, const double lambda) {
//     VectorXd grad(vars.size() + 1);
//     grad.setZero();

//     // Gradient của các thành phần hàm mục tiêu
//     grad(0) = -2 - lambda * 2 * vars(0);  // dL/dx1
//     grad(1) = -1 - lambda * 4 * vars(1);  // dL/dx2

//     // Hàm ràng buộc như một phần của gradient
//     grad(vars.size()) = constraint(vars);
//     return grad;
// }

// // Gradient Descent with Momentum (GD with momentum)
// void solve_lagrange_with_momentum(VectorXd& vars, double& lambda) {
//     double tolerance = 1e-6;
//     int max_iterations = 10000;
//     double alpha = 0.01;   // Tỷ lệ học (learning rate)
//     double beta = 0.5;    // Hệ số động lượng (momentum)
    
//     // Khởi tạo giá trị ban đầu cho các biến và động lượng
//     vars = VectorXd::Constant(2, -2); // Giả thuyết ban đầu cho các biến x
//     lambda = -0.7; // Giả thuyết ban đầu cho lambda
//     VectorXd momentum(vars.size() + 1);
//     momentum.setZero(); // Khởi tạo động lượng bằng 0

//     for (int iter = 0; iter < max_iterations; iter++) {
//         VectorXd grad = lagrange_grad(vars, lambda);
        
//         // Cập nhật động lượng
//         momentum = beta * momentum + (1 - beta) * grad;
        
//         // Cập nhật các tham số (x1, x2, lambda)
//         vars -= alpha * momentum.head(2);  // Cập nhật các biến x1 và x2
//         lambda -= alpha * momentum(2);     // Cập nhật giá trị lambda

//         // Kiểm tra điều kiện dừng
//         if (grad.norm() < tolerance) {
//             break;
//         }

//         // In giá trị hiện tại của x và lambda mỗi vòng lặp để theo dõi
//         cout << "Iteration " << iter + 1 << ": x1 = " << vars(0) << ", x2 = " << vars(1)
//              << ", lambda = " << lambda << endl;
//     }
// }

// int main() {
//     VectorXd vars(2); // Các biến x1 và x2
//     double lambda;

//     // Giải bài toán tối tiểu hóa bằng GD with momentum
//     solve_lagrange_with_momentum(vars, lambda);

//     cout << "Optimal point: x1 = " << vars(0) << ", x2 = " << vars(1) << endl;
//     cout << "Minimum value of f(x1, x2): " << objective(vars) << endl;
//     cout << "Lagrange Multiplier (lambda): " << lambda << endl;

//     return 0;
// }
#include <iostream>
#include <Eigen/Dense>
#include <cmath>
#include <vector>

using namespace std;
using namespace Eigen;

// Hàm mục tiêu: f(x) = 2 * x[0] + x[1] + 10
double objective(const VectorXd& vars) {
    return (2 * vars(0) + vars(1) + 10);
}

// Hàm ràng buộc: g(x) = x[0]^2 + 2 * x[1]^2 - 3 = 0
double constraint(const VectorXd& vars) {
    return pow(vars(0), 2) + 2 * pow(vars(1), 2) - 3;
}

// Gradient của hàm Lagrangian
VectorXd lagrange_grad(const VectorXd& vars, const double lambda) {
    VectorXd grad(vars.size() + 1);
    grad.setZero();

    // Gradient của các thành phần hàm mục tiêu
    grad(0) = 2 + -lambda * 2 * vars(0);  // dL/dx1
    grad(1) = 1 + -lambda * 4 * vars(1);  // dL/dx2

    // Hàm ràng buộc như một phần của gradient
    grad(vars.size()) = constraint(vars);
    return grad;
}

// Ma trận Jacobian của hệ gradient (đạo hàm riêng phần của vector grad)
MatrixXd lagrange_jacobian(const VectorXd& vars, const double lambda) {
    int n = vars.size();
    MatrixXd jacobian(n + 1, n + 1);
    jacobian.setZero();
    jacobian(0, 0) = -lambda * 2;           // ∂²L/∂x1²
    jacobian(0, n) = -2 * vars(0);          // ∂²L/∂x1∂λ
    jacobian(1, 1) = -lambda * 4;           // ∂²L/∂x2²
    jacobian(1, n) = -4 * vars(1);          // ∂²L/∂x2∂λ
    jacobian(n, 0) = 2 * vars(0);          // ∂g/∂x1
    jacobian(n, 1) = 4 * vars(1);          // ∂g/∂x2
    return jacobian;
}

// Hàm kiểm tra điều kiện KKT (bao gồm λ ≥ 0 và λg(x) = 0)
bool check_KKT_conditions(const VectorXd& vars, double lambda) {
    double g = constraint(vars);
    // Kiểm tra điều kiện KKT: λ ≥ 0 và λg(x) = 0
    if (lambda >= 0 && fabs(lambda * g) < 1e-6) {
        return true;
    } else {
        return false;
    }
}

// Giải bài toán tối đa hóa với phương pháp Newton-Raphson cho nhân tử Lagrange
bool solve_lagrange(VectorXd& vars, double& lambda) {
    double tolerance = 1e-6;
    int max_iterations = 1000;

    vars = VectorXd::Constant(2, 2); // Giả thuyết ban đầu cho các biến
    lambda = 0.5; // Giả thuyết ban đầu cho λ

    for (int iter = 0; iter < max_iterations; iter++) {
        VectorXd grad = lagrange_grad(vars, lambda);
        cout<<"Gradient: \n"<<grad<<endl;
        MatrixXd jacobian = lagrange_jacobian(vars, lambda);
        cout<<"Jacobian: \n"<<jacobian<<endl;
        if (grad.norm() < tolerance) {
            break;
        }
        // Giải phương trình J * delta = -grad để tìm bước cập nhật
        VectorXd delta = jacobian.colPivHouseholderQr().solve(-grad);

        // Cập nhật các giá trị của các biến
        vars(0) += delta(0);
        vars(1) += delta(1);
        lambda += delta(2);
        cout << "Iteration " << iter + 1 << ": x1 = " << vars(0) << ", x2 = " << vars(1) << ", lambda = " << lambda << endl;
        // Kiểm tra điều kiện KKT sau mỗi lần cập nhật
        if (check_KKT_conditions(vars, lambda)) {
            cout << "Điều kiện KKT thỏa mãn tại bước lặp thứ " << iter + 1 << endl;
            break;
        } else if(lambda < 0) {
            cout << "Không thỏa điều kiện KKT";
            return false;
        }
    }
    return true;
}

int main() {
    VectorXd vars(2); // Các biến x1 và x2
    double lambda;
    // Giải bài toán tối đa hóa
    bool solved = solve_lagrange(vars, lambda);
    if(solved) {
        cout << "Optimal point: x1 = " << vars(0) << ", x2 = " << vars(1) << endl;
        cout << "Maximum value of f(x1, x2): " << objective(vars) << endl;
        cout << "Lagrange Multiplier (lambda): " << lambda << endl;
    } else {
        cout << "Nhập lại giá trị x1, x2, lambda" << endl;
    }
    return 0;
}
