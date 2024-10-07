#include <iostream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

vector<int>* PrimeFactorize(int n) {
    vector<int> p, e;
    for (int i = 2; i <= n; i++) {
        if (isPrime(i)) {
            if (n % i == 0) {
                int count = 0;
                while (n % i == 0) {
                    n /= i;
                    count++;
                }
                p.push_back(i);
                e.push_back(count);
            }
        }
    }
    vector<int>* result = new std::vector<int>[2];
    result[0] = p;
    result[1] = e;
    return result;
}

int numFactors(const vector<int>& expo) {
    int numOfFactors = 1;
    for (int i = 0; i < expo.size(); i++) {
        numOfFactors *= expo[i] + 1;
    }
    return numOfFactors;
}

string multiplyBigInt(string num1, string num2) {
    int len1 = num1.size();
    int len2 = num2.size();
    vector<int> result(len1 + len2, 0);

    for (int i = len1 - 1; i >= 0; i--) {
        for (int j = len2 - 1; j >= 0; j--) {
            int mul = (num1[i] - '0') * (num2[j] - '0');
            int sum = mul + result[i + j + 1];
            result[i + j] += sum / 10;
            result[i + j + 1] = sum % 10;
        }
    }

    string product = "";
    bool foundNonZero = false;
    for (int i = 0; i < result.size(); i++) {
        if (result[i] != 0)
            foundNonZero = true;
        if (foundNonZero)
            product += to_string(result[i]);
    }

    return product.empty() ? "0" : product;
}

string powBigInt(string base, int exp) {
    string result = "1";
    for (int i = 0; i < exp; i++) {
        result = multiplyBigInt(result, base);
    }
    return result;
}

string computeProductOfDivisors(int N, vector<int> p, vector<int> e) {
    int numOfFactors = numFactors(e);
    
    string N_str = to_string(N);
    string exponent = to_string(numOfFactors / 2);
    
    string productOfDivisors = powBigInt(N_str, numOfFactors / 2);
    
    return productOfDivisors;
}

int main() {
    int N;
    cout << "Vui long nhap ma so sinh vien cua ban (N): ";
    cin >> N;

    vector<int>* result = PrimeFactorize(N);
    vector<int> p = result[0];
    vector<int> e = result[1];

    string productOfFactors = computeProductOfDivisors(N, p, e);

    cout << "Tich cac uoc cua " << N << " la: " << productOfFactors << endl;

    delete[] result;
    return 0;
}