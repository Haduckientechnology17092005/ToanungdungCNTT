#include <iostream>
#include <vector>
using namespace std;

// Hàm nhân hai ma trận vuông kích thước n x n
vector<vector<double>> multiplyMatrices(const vector<vector<double>>& A, const vector<vector<double>>& B) {
    int n = A.size();
    vector<vector<double>> result(n, vector<double>(n, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}

// Hàm Markov tính trạng thái từng bước đến k bước
void markovSteps(vector<double> initialState, vector<vector<double>> transitionMatrix, int k) {
    int n = transitionMatrix.size();

    // Khởi tạo trạng thái hiện tại là trạng thái ban đầu
    vector<double> currentState = initialState;

    // // In trạng thái ban đầu
    // cout << "Trang thai ban dau: ";
    // for (double state : currentState) {
    //     cout << state << " ";
    // }
    // cout << endl;

    // Tính trạng thái ở từng bước từ 1 đến k
    for (int step = 1; step <= k; ++step) {
        vector<double> nextState(n, 0);

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                nextState[i] += currentState[j] * transitionMatrix[j][i];
            }
        }

        // Cập nhật trạng thái hiện tại
        currentState = nextState;

        // In trạng thái ở bước hiện tại
        cout << "Buoc " << step << ": ";
        for (double state : currentState) {
            cout << state << " ";
        }
        cout << endl;
        cout << "Xac suat he thong lam viec o trang thai 1 sau " << step << " la " << currentState[0]<< endl;
    }
}

int main() {
    vector<vector<double>> transitionMatrix = {
        {0.0, 0.2, 0.5, 0.3},
        {0.05, 0.2, 0.3, 0.45},
        {0.4, 0.1, 0.3, 0.2},
        {0.0, 0.3, 0.15, 0.55}
    };

    int k = 3;// số lần lặp

    // Nhập trạng thái ban đầu
    vector<double> initialState = {0, 0, 1, 0};

    // Tính và in trạng thái từng bước
    markovSteps(initialState, transitionMatrix, k);

    return 0;
}
