#include <Eigen/Dense>
#include <iostream>

using namespace std;
int main() {
    Eigen::MatrixXd A(2, 3);
    A << 1, 0,-1,
         1,1,1;

    Eigen::JacobiSVD<Eigen::MatrixXd> svd(A, Eigen::ComputeThinU | Eigen::ComputeThinV);
    Eigen::MatrixXd U = svd.matrixU();
    Eigen::MatrixXd S = svd.singularValues().asDiagonal();
    Eigen::MatrixXd V = svd.matrixV();

    std::cout << "U:\n" << U << std::endl;
    std::cout << "S:\n" << S << std::endl;
    std::cout << "V transpose:\n" << V.transpose() << std::endl;
    return 0;
}
//g++ -I /usr/include/eigen3 /media/haduckien/E/Studying/HK3/Mathmetics\ for\ CS\ \(3\)/BTC5/test.cpp -o test
