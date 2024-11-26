#include <iostream>
#include <cmath>
#include <limits>

using namespace std;

// Hàm mục tiêu
double objective(double x, double y) {
    return 5 * x + 10 * y + 5 * x * y - 4 * x * x - 6 * y * y;
}

// Đạo hàm riêng theo x và y
double dfdx(double x, double y) {
    return 5 + 5 * y - 8 * x;
}

double dfdy(double x, double y) {
    return 10 + 5 * x - 12 * y;
}

// Đạo hàm của hàm Lagrange theo lambda
double dfdlambda1(double x, double y) {
    return x + 3 * y - 35;
}

double dfdlambda2(double x) {
    return -x;
}

double dfdlambda3(double y) {
    return -y;
}

// Hàm Lagrange mở rộng
void lagrangeOptimization(double init_x, double init_y) {
    double x = init_x;
    double y = init_y;
    double lambda1 = 0.0;  // Khởi tạo lambda1
    double lambda2 = 0.0;  // Khởi tạo lambda2
    double lambda3 = 0.0;  // Khởi tạo lambda3
    double learningRate = 0.001;  // Hệ số học
    int maxIter = 10000;  // Số vòng lặp tối đa

    // Lặp cho tới khi hội tụ
    for (int iter = 0; iter < maxIter; iter++) {
        // Tính các đạo hàm
        double grad_x = dfdx(x, y) + lambda1;  // Đạo hàm theo x với điều kiện Lagrange
        double grad_y = dfdy(x, y) + lambda1 * 3;  // Đạo hàm theo y với điều kiện Lagrange
        double grad_lambda1 = dfdlambda1(x, y);
        double grad_lambda2 = dfdlambda2(x);
        double grad_lambda3 = dfdlambda3(y);
        
        // Cập nhật giá trị của x, y và lambda
        x -= learningRate * grad_x;
        y -= learningRate * grad_y;
        lambda1 -= learningRate * grad_lambda1;
        lambda2 -= learningRate * grad_lambda2;
        lambda3 -= learningRate * grad_lambda3;

        // Điều kiện KKT: Kiểm tra xem nhân tử Lagrange có bị âm hay không
        lambda1 = max(lambda1, 0.0);
        lambda2 = max(lambda2, 0.0);
        lambda3 = max(lambda3, 0.0);

        // Kiểm tra điều kiện hội tụ
        if (abs(grad_x) < 1e-6 && abs(grad_y) < 1e-6 && abs(grad_lambda1) < 1e-6 && abs(grad_lambda2) < 1e-6 && abs(grad_lambda3) < 1e-6)
            break;
    }

    // In kết quả
    cout << "Gia tri nho nhat tai x = " << x << ", y = " << y << endl;
    cout << "Gia tri nho nhat cua ham muc tieu la: " << objective(x, y) << endl;
}

int main() {
    // Thử nghiệm với các giá trị khởi tạo
    lagrangeOptimization(35, 0);  // Khởi tạo tại x = 10, y = 5

    return 0;
}
