#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

int main() {
    long long result = 1;
    int n;
    cin >> n;

    if (n <= 0) {
        cout << "";
        return 0;
    }
    vector<long long> result1;
    string line;
    cin.ignore();
    getline(cin, line);
    stringstream ss(line);
    long long k;
    while (ss >> k) {
        if (k >= 0 && k <= 10) {
            result1.push_back(k);
        }
    }
    for (size_t i = 0; i < result1.size(); i++) {
        result *= result1[i];
    }
    cout << result;
    return 0;
}