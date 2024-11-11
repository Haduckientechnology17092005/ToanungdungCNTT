#include <iostream>
#include <cmath>
#include <functional>
#include <vector>
#include <algorithm>

using namespace std;

// Hàm Golden Section Search để tối ưu hóa dọc theo một hướng
double goldenSection(const function<double(double)> &func, double a, double b, double tol = 1e-6) {
    const double gr = (sqrt(5) + 1) / 2;  // Tỷ lệ vàng
    double c = b - (b - a) / gr;
    double d = a + (b - a) / gr;

    while (fabs(c - d) > tol) {
        if (func(c) < func(d))
            b = d;
        else
            a = c;

        // Tính lại c và d
        c = b - (b - a) / gr;
        d = a + (b - a) / gr;
    }

    return (b + a) / 2;
}

// Hàm Powell để tìm cực tiểu của hàm số `func` với điểm bắt đầu `iniGuess`
vector<double> powellMethod(const function<double(double, double)> &func, vector<double> iniGuess, double tol) {
    int count = 1;
    double searchRange[] = {-1, 1};  // Vùng tìm kiếm cho Golden Section từ -1 đến 1
    vector<vector<double>> directions = {{1, 0}, {0, 1}};  // Các hướng tìm kiếm ban đầu
    vector<double> X = iniGuess;  // Điểm bắt đầu
    vector<double> Y = X;
    int n = directions.size();
    bool doLoop = true;

    while (doLoop) {
        for (int q = 0; q < n; ++q) {
            // Hàm func_gS cho Golden Section
            auto func_gS = [&](double alphaValue) {
                return func(X[0] + alphaValue * directions[q][0], X[1] + alphaValue * directions[q][1]);
            };

            // Tìm giá trị alpha tối ưu theo hướng directions[q]
            double alphaOpti = goldenSection(func_gS, searchRange[0], searchRange[1]);
            X[0] += alphaOpti * directions[q][0];
            X[1] += alphaOpti * directions[q][1];

            // Nếu là hướng cuối cùng, cập nhật hướng và kiểm tra hội tụ
            if (q == n - 1) {
                count++;
                vector<double> newDir = {X[0] - Y[0], X[1] - Y[1]};
                double normNewDir = sqrt(newDir[0] * newDir[0] + newDir[1] * newDir[1]);
                
                if (normNewDir > 0) {
                    directions.push_back({newDir[0] / normNewDir, newDir[1] / normNewDir});  // Cập nhật hướng mới
                    directions.erase(directions.begin());  // Xóa hướng đầu tiên
                }
                
                Y = X;
                
                // Tìm alpha tối ưu theo hướng mới
                alphaOpti = goldenSection(func_gS, searchRange[0], searchRange[1]);
                X[0] += alphaOpti * directions[q][0];
                X[1] += alphaOpti * directions[q][1];

                // Kiểm tra hội tụ
                double diffNorm = sqrt(pow(Y[0] - X[0], 2) + pow(Y[1] - X[1], 2));
                if (diffNorm < tol) {
                    doLoop = false;  // Dừng vòng lặp nếu hội tụ
                }
            }

            // Kiểm soát số lần lặp
            if (count == 100) {
                directions = {{1, 0}, {0, 1}};  // Đặt lại hướng ban đầu
                count = 1;
                break;
            }
        }
    }

    return X;  // Trả về điểm tối ưu
}

// Hàm Augmented Lagrangian với các ràng buộc
pair<vector<double>, double> augmentedLagrangian(
    const function<double(double, double)> &Ffunc,            // Hàm mục tiêu
    const vector<function<double(double, double)>> &gFuncs,   // Các ràng buộc bất đẳng thức
    const vector<function<double(double, double)>> &HFuncs,   // Các ràng buộc đẳng thức
    vector<double> iniGuess, double tol) {
    
    vector<double> lagrangeMultipliers(gFuncs.size(), 1.0);  // Nhân tử Lagrange cho các ràng buộc bất đẳng thức
    vector<double> lagrangeMultipliersH(HFuncs.size(), 1.0); // Nhân tử Lagrange cho các ràng buộc đẳng thức
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

            for (size_t i = 0; i < gFuncs.size(); ++i) {
                penalty += lagrangeMultipliers[i] * max(gFuncs[i](x1, x2), -lagrangeMultipliers[i] / (2 * penaltyParameter))
                          + penaltyParameter * max(gFuncs[i](x1, x2), -lagrangeMultipliers[i] / (2 * penaltyParameter));
            }

            for (size_t j = 0; j < HFuncs.size(); ++j) {
                penalty += lagrangeMultipliersH[j] * HFuncs[j](x1, x2) 
                          + penaltyParameter * pow(HFuncs[j](x1, x2), 2);
            }
            return penalty;
        };

        minX = powellMethod(Afunc, x0, 1e-6);

        if (sqrt(pow(minX[0] - x0[0], 2) + pow(minX[1] - x0[1], 2)) < tol) {
            doLoop = false;
            minFuncValue = Afunc(minX[0], minX[1]);
        } else {
            x0 = minX;
        }
        for(size_t i = 0; i < gFuncs.size(); ++i) {
            cout << "Lambda[" << i << "]: " << lagrangeMultipliers[i]
                 << ", r: " << max(gFuncs[i](minX[0], minX[1]), 0.0)
                 << ", x1: " << minX[0]
                 << ", x2: " << minX[1]
                 << ", value of h: " << HFuncs[0](minX[0], minX[1]) << endl;
        }
        for (size_t j = 0; j < HFuncs.size(); ++j) {
            cout << "LambdaH[" << j << "]: " << lagrangeMultipliersH[j]
                 << ", r: " << HFuncs[j](minX[0], minX[1])
                 << ", x1: " << minX[0]
                 << ", x2: " << minX[1]
                 << ", value of h: " << HFuncs[0](minX[0], minX[1]) << endl;
        }

        cout << "----------------------------------------" << endl;
        for (size_t i = 0; i < gFuncs.size(); ++i) {
            lagrangeMultipliers[i] += 2 * penaltyParameter * max(gFuncs[i](minX[0], minX[1]), -lagrangeMultipliers[i] / (2 * penaltyParameter));
        }

        for (size_t j = 0; j < HFuncs.size(); ++j) {
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
    auto Ffunc = [](double x1, double x2) { return (2*x1 + x2 + 10); };
    // Hàm g(x1, x2) đại diện cho các ràng buộc bất đẳng thức có dạng 𝑔(𝑥1,𝑥2) ≤ 0
    vector<function<double(double, double)>> gFuncs = {
        // [](double x1, double x2) { return x1 + x2 + 1; } // Ví dụ: x1 + x2 ≤ 1
        // [](double x1, double x2) { return x1 * x2 - 2; }   // Ví dụ: x1 * x2 ≤ 2
    };
    // Hàm h(x1, x2) đại diện cho các ràng buộc đẳng thức có dạng h(x1, x2) = 0.
    vector<function<double(double, double)>> HFuncs = {
        [](double x1, double x2) { return x1*x1 + 2*x2*x2 - 3; }
    };

    vector<double> iniGuess = {1, 1};
    double tol = 1e-6;

    auto result = augmentedLagrangian(Ffunc, gFuncs, HFuncs, iniGuess, tol);

    cout << "Minimizing point: (" << result.first[0] << ", " << result.first[1] << ")\n";
    cout << "Minimum function value: " << result.second << endl;

    return 0;
}
