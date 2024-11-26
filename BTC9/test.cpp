#include <iostream>
#include <Eigen/Dense>
#include <limits>

using namespace std;
using namespace Eigen;

// Hàm mục tiêu f(x, y) = 5x + 10y + 5xy - 4x^2 - 6y^2
double objectiveFunction(double x, double y) {
    return 5 * x + 10 * y + 5 * x * y - 4 * x * x - 6 * y * y;
}

// Gradient của hàm mục tiêu
Vector2d gradient(double x, double y) {
    Vector2d grad;
    grad(0) = 5 + 5 * y - 8 * x;
    grad(1) = 10 + 5 * x - 12 * y;
    return grad;
}

int main() {
    // Khởi tạo các giá trị ban đầu
    double x = 0.0, y = 0.0;  // Nghiệm bắt đầu
    double epsilon = 1e-6;     // Ngưỡng dừng
    double step_size = 0.01;   // Kích thước bước
    int max_iter = 10000;      // Số vòng lặp tối đa
    int iter = 0;

    // Cách tiếp cận đơn giản để tìm cực tiểu trong khi tuân thủ ràng buộc
    while (iter < max_iter) {
        // Tính gradient của hàm mục tiêu tại (x, y)
        Vector2d grad = gradient(x, y);

        // Cập nhật giá trị x, y bằng cách sử dụng gradient descent
        x -= step_size * grad(0);
        y -= step_size * grad(1);

        // Kiểm tra điều kiện ràng buộc x >= 0 và y >= 0
        if (x < 0) x = 0;
        if (y < 0) y = 0;

        // Kiểm tra ràng buộc x + 3y <= 35
        if (x + 3 * y > 35) {
            double lambda = (x + 3 * y - 35);
            x -= lambda;  // Cập nhật để thỏa mãn ràng buộc x + 3y <= 35
            y -= lambda / 3;
        }

        // Kiểm tra điều kiện dừng (khi gradient nhỏ)
        if (grad.norm() < epsilon) {
            break;
        }

        iter++;
    }

    // In kết quả
    cout << "Nghiệm tối ưu (x, y): (" << x << ", " << y << ")" << endl;
    cout << "Giá trị cực tiểu của hàm mục tiêu: " << objectiveFunction(x, y) << endl;

    return 0;
}
