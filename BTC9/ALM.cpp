#include <iostream>
#include <cmath>
#include <functional>
#include <vector>
#include <algorithm>

using namespace std;

// Phương pháp Golden Section để tối ưu hóa hàm 1 biến
double goldenSection(const function<double(double)> &func, double a, double b, double tol = 1e-6) {
    const double gr = (sqrt(5) + 1) / 2; // tỷ lệ vàng
    double c = b - (b - a) / gr;
    double d = a + (b - a) / gr;

    while (fabs(c - d) > tol) {
        if (func(c) < func(d))
            b = d;
        else
            a = c;

        c = b - (b - a) / gr;
        d = a + (b - a) / gr;
    }

    return (b + a) / 2;
}

// Phương pháp Powell để tối ưu hóa hàm nhiều biến
vector<double> powellMethod(const function<double(double, double)> &func, vector<double> iniGuess, double tol, int maxIter = 100) {
    int count = 1;
    double searchRange[] = {-1, 1};
    vector<vector<double>> directions = {{1, 0}, {0, 1}};
    vector<double> X = iniGuess;  // Vị trí bắt đầu
    vector<double> Y = X;
    int n = directions.size();
    bool doLoop = true;

    while (doLoop && count <= maxIter) {
        for (int q = 0; q < n; ++q) {
            auto func_gS = [&](double alphaValue) {
                return func(X[0] + alphaValue * directions[q][0], X[1] + alphaValue * directions[q][1]);
            };

            double alphaOpti = goldenSection(func_gS, searchRange[0], searchRange[1]);
            X[0] += alphaOpti * directions[q][0];
            X[1] += alphaOpti * directions[q][1];

            if (q == n - 1) {
                count++;
                vector<double> newDir = {X[0] - Y[0], X[1] - Y[1]};
                double normNewDir = sqrt(newDir[0] * newDir[0] + newDir[1] * newDir[1]);

                if (normNewDir > 0) {
                    directions.push_back({newDir[0] / normNewDir, newDir[1] / normNewDir});
                    directions.erase(directions.begin());
                }

                Y = X;

                alphaOpti = goldenSection(func_gS, searchRange[0], searchRange[1]);
                X[0] += alphaOpti * directions[q][0];
                X[1] += alphaOpti * directions[q][1];

                double diffNorm = sqrt(pow(Y[0] - X[0], 2) + pow(Y[1] - X[1], 2));
                if (diffNorm < tol) {
                    doLoop = false;
                }
            }

            if (count == maxIter) {
                directions = {{1, 0}, {0, 1}};
                count = 1;
                break;
            }
        }
    }

    if (count > maxIter) {
        cout << "Không tìm thấy nghiệm sau " << maxIter << " vòng lặp" << endl;
        return {};
    }

    return X;
}

// Phương pháp Augmented Lagrangian để tối ưu hóa hàm với ràng buộc
pair<vector<double>, double> augmentedLagrangian(
    const function<double(double, double)> &Ffunc,
    const vector<function<double(double, double)>> &gFuncs,
    const vector<function<double(double, double)>> &HFuncs,
    vector<double> iniGuess, double tol) {

    vector<double> lagrangeMultipliers(gFuncs.size(), 1.0); // Các số nhân Lagrange cho các ràng buộc
    vector<double> lagrangeMultipliersH(HFuncs.size(), 1.0); // Các số nhân Lagrange cho các ràng buộc h
    double penaltyParameter = 1.0;
    double gamma = 1.5;
    double penaltyMax = 10.0;
    vector<double> x0 = iniGuess;
    bool doLoop = true;

    vector<double> minX;
    double minFuncValue = 0.0;

    while (doLoop) {
        auto Afunc = [&](double x1, double x2) {
            double penalty = Ffunc(x1, x2);

            for (int i = 0; i < gFuncs.size(); ++i) {
                penalty += lagrangeMultipliers[i] * max(gFuncs[i](x1, x2), -lagrangeMultipliers[i] / (2 * penaltyParameter))
                          + penaltyParameter * max(gFuncs[i](x1, x2), -lagrangeMultipliers[i] / (2 * penaltyParameter));
            }

            for (int j = 0; j < HFuncs.size(); ++j) {
                penalty += lagrangeMultipliersH[j] * HFuncs[j](x1, x2)
                          + penaltyParameter * pow(HFuncs[j](x1, x2), 2);
            }
            return penalty;
        };

        minX = powellMethod(Afunc, x0, 1e-6);

        if (minX.empty()) {
            return {{}, 0.0};
        }

        cout << "Vòng lặp: " << "\n";
        cout << "x1: " << minX[0] << ", x2: " << minX[1] << "\n";
        cout << "Số nhân Lagrange (ràng buộc g): ";
        for (double lambda : lagrangeMultipliers) {
            cout << lambda << " ";
        }
        cout << "\nSố nhân Lagrange (ràng buộc h): ";
        for (double h_lambda : lagrangeMultipliersH) {
            cout << h_lambda << " ";
        }
        cout << "\nTham số hình phạt: " << penaltyParameter << "\n\n";

        if (sqrt(pow(minX[0] - x0[0], 2) + pow(minX[1] - x0[1], 2)) < tol) {
            doLoop = false;
            minFuncValue = Afunc(minX[0], minX[1]);
        } else {
            x0 = minX;
        }

        for (int i = 0; i < gFuncs.size(); ++i) {
            lagrangeMultipliers[i] += 2 * penaltyParameter * max(gFuncs[i](minX[0], minX[1]), -lagrangeMultipliers[i] / (2 * penaltyParameter));
        }

        for (int j = 0; j < HFuncs.size(); ++j) {
            lagrangeMultipliersH[j] += 2 * penaltyParameter * HFuncs[j](minX[0], minX[1]);
        }

        penaltyParameter *= gamma;
        if (penaltyParameter > penaltyMax) {
            penaltyParameter = penaltyMax;
        }
    }

    return {minX, minFuncValue};
}

int main() {
    // Định nghĩa hàm mục tiêu Ffunc
    auto Ffunc = [](double x1, double x2) {
        return 5 * x1 + 10 * x2 + 5 * x1 * x2 - 4 * x1 * x1 - 6 * x2 * x2;
    };

    // Định nghĩa các ràng buộc g(x1, x2)
    vector<function<double(double, double)>> gFuncs = {
        [](double x1, double x2) {
            return x1 + 3 * x2 - 35; // g1(x1, x2) = x1 + 3x2 - 35
        },
        [](double x1, double x2) {
            return -x1; // g2(x1, x2) = -x1
        },
        [](double x1, double x2) {
            return -x2; // g3(x1, x2) = -x2
        }
    };

    // Ràng buộc h(x1, x2) (trong ví dụ này không có)
    vector<function<double(double, double)>> HFuncs = {};

    // Vị trí bắt đầu
    vector<double> iniGuess = {35, 0};
    double tol = 1e-6;

    // Tìm nghiệm bằng phương pháp Augmented Lagrangian
    auto result = augmentedLagrangian(Ffunc, gFuncs, HFuncs, iniGuess, tol);

    if (result.first.empty()) {
        cout << "Không có nghiệm." << endl;
    } else {
        cout << "Điểm tối ưu: (" << result.first[0] << ", " << result.first[1] << ")\n";
        cout << "Giá trị hàm mục tiêu tại điểm tối ưu: " << result.second << endl;
    }

    return 0;
}
