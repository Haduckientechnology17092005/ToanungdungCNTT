#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <map>
#include <random>
#include <string>
#include <iomanip>
#include <set>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

void readCSV(const string& filename, vector<string>& data) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Không thể mở file " << filename << endl;
        exit(1);
    }

    string line;
    while (getline(file, line)) {
        data.push_back(line);
    }
    file.close();
}

int main() {
    vector<string> data;
    readCSV("breakfast.csv", data);

    // In ra 5 món ăn cuối cùng
    cout << "5 món ăn cuối cùng: ";
    for (size_t i = max(size_t(0), data.size() - 5); i < data.size(); ++i) {
        cout << data[i] << " ";
    }
    cout << endl;

    // Lấy danh sách các món ăn duy nhất
    set<string> uniqueFoods(data.begin(), data.end());
    vector<string> Q(uniqueFoods.begin(), uniqueFoods.end());
    cout << "Danh sách các món ăn: ";
    for (const auto& food : Q) {
        cout << food << " ";
    }
    cout << endl;

    // Tạo nơi lưu trữ giá trị
    unordered_map<string, int> foodCount;
    unordered_map<string, unordered_map<string, double>> foodPairCount;

    // Đếm số lần xuất hiện của các món ăn và cặp món ăn
    for (size_t i = 0; i < data.size(); ++i) {
        foodCount[data[i]]++;
        if (i < data.size() - 1) {
            foodPairCount[data[i]][data[i + 1]]++;
        } else {
            // Cặp cuối cùng trỏ về chính nó
            foodPairCount[data[i]][data[i]]++;
        }
    }

    // Chuẩn hóa ma trận chuyển trạng thái
    for (auto& [current, futureMap] : foodPairCount) {
        double total = foodCount[current];
        for (auto& [future, count] : futureMap) {
            futureMap[future] /= total;
        }
    }

    // Tạo từ điển ánh xạ món ăn sang chỉ số
    map<string, int> keyToIdx;
    for (size_t i = 0; i < Q.size(); ++i) {
        keyToIdx[Q[i]] = i;
    }

    // Tạo ma trận chuyển trạng thái P
    MatrixXd P(Q.size(), Q.size());
    for (size_t i = 0; i < Q.size(); ++i) {
        for (size_t j = 0; j < Q.size(); ++j) {
            P(i, j) = foodPairCount[Q[i]][Q[j]];
        }
    }

    // In ma trận chuyển trạng thái
    cout << "Ma trận chuyển trạng thái P:" << endl;
    cout << fixed << setprecision(2) << P << endl;

    // Tổng hàng của ma trận phải bằng 1
    cout << "Tổng hàng của ma trận P:" << endl;
    for (int i = 0; i < P.rows(); ++i) {
        cout << "Hàng " << i << ": " << P.row(i).sum() << endl;
    }

    // Dự đoán món ăn tiếp theo
    string currFood = data.back();
    // Tạo phân phối xác suất từ hàng của ma trận P
    VectorXd currDistribution = P.row(keyToIdx[currFood]).eval(); // Đảm bảo là một bản sao

    // Đảm bảo phân phối xác suất hợp lệ (tổng bằng 1)
    double sum = currDistribution.sum();
    if (sum > 0) {
        currDistribution /= sum; // Chuẩn hóa nếu tổng không phải là 1
    }

    // Sử dụng phân phối xác suất để chọn món ăn tiếp theo
    random_device rd;
    mt19937 gen(rd());
    discrete_distribution<> dist(currDistribution.data(), currDistribution.data() + currDistribution.size());

    int predictedIdx = dist(gen);
    string predictedFood = Q[predictedIdx];
    double predictedProbability = currDistribution(predictedIdx);

    cout << "Món ăn hôm trước: " << currFood << endl;
    cout << "Món ăn nên ăn hôm nay là \"" << predictedFood
         << "\" với xác suất xảy ra là " << round(predictedProbability * 100) << "%" << endl;

    cout << "Hello world" << endl;
    return 0;
}
