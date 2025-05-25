#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <limits>
using namespace std;

int main() {
    long long result = 1;
    int n;
    int count = 1;
    vector<long long> result1;
    string line;
    getline(cin, line);
    stringstream ss(line);
    long long k;
    while (ss >> k) {
        if (k >= 0 && k <= 10) {
            result1.push_back(k);
        }
    }
    count = result1.size()-1;
    for (size_t i = 0; i < result1.size(); i++) {
        if (count != result1[i]) {
            result = result*result1[i];
        } else {
            count = numeric_limits<int>::max();
        }
    }
    cout << result << endl;
    return 0;
}
