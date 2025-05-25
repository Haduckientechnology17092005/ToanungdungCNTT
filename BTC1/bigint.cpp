#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1000007;

void removeZero(vector<int>& v) {
    while (v.size() > 1 && v.back() == 0) {
        v.pop_back();
    }
}

void init(int x, vector<int>& v) {
    v.clear();
    while (x > 0) {
        v.push_back(x % 10);
        x /= 10;
    }
    if (v.empty()) v.push_back(0);
}

void print(const vector<int>& v) {
    for (int i = v.size() - 1; i >= 0; i--) {
        cout << v[i];
    }
    cout << endl;
}

void mul(vector<int>& v1, int num, vector<int>& v3) {
    v3.clear();
    v3.resize(v1.size() + 10, 0);
    int carry = 0;
    for (int i = 0; i < v1.size(); i++) {
        int temp = v1[i] * num + carry;
        v3[i] = temp % 10;
        carry = temp / 10;
    }
    int idx = v1.size();
    while (carry > 0) {
        v3[idx++] = carry % 10;
        carry /= 10;
    }
    removeZero(v3);
}

int modBigInt(const vector<int>& v, int mod) {
    long long remainder = 0;
    for (int i = v.size() - 1; i >= 0; i--) {
        remainder = (remainder * 10 + v[i]) % mod;
    }
    return remainder;
}

int main() {
    int n;
    cin >> n;

    vector<int> factorial;
    init(1, factorial);

    for (int i = 2; i <= n; i++) {
        vector<int> temp;
        mul(factorial, i, temp);
        factorial = temp;
        int modResult = modBigInt(factorial, MOD); 
        init(modResult, factorial); 
    }

    print(factorial);
    return 0;
}
