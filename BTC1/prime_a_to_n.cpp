#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
#include <iomanip>
using namespace std;

// Hàm sàng phân đoạn để tìm các số nguyên tố trong đoạn [L, R]
vector<bool> segmentedSieve(long long L, long long R) {
    long long lim = sqrt(R);
    vector<bool> mark(lim + 1, false);
    vector<long long> primes;
    for (long long i = 2; i <= lim; ++i) {
        if (!mark[i]) {
            primes.emplace_back(i);
            for (long long j = i * i; j <= lim; j += i)
                mark[j] = true;
        }
    }
    vector<bool> isPrime(R - L + 1, true);
    for (long long i : primes) {
        for (long long j = max(i * i, (L + i - 1) / i * i); j <= R; j += i) {
            isPrime[j - L] = false;
        }
    }
    if (L == 1) { 
        isPrime[0] = false;
    }
    return isPrime;
}

// Hàm liệt kê các số nguyên tố
void listPrimes(const vector<long long>& primes) {
    const int columnWidth = 5; // Độ rộng mỗi cột
    const int columnsPerRow = 10; // Số cột mỗi hàng
    int count = 0;

    for (long long prime : primes) {
        cout << setw(columnWidth) << prime << " ";
        count++;
        if (count % columnsPerRow == 0) { 
            cout << endl; 
        }
    }
    if (count % columnsPerRow != 0) {
        cout << endl; // Kết thúc dòng cuối cùng nếu còn sót
    }
}

// Hàm tìm các số nguyên tố gần target nhất
void findClosestPrimes(const vector<long long>& primes, long long target) {
    vector<pair<long long, long long>> distances; // Vector chứa số nguyên tố và khoảng cách của nó tới target
    // Tính khoảng cách và thêm vào vector
    for (long long prime : primes) {
        distances.push_back({prime, abs(prime - target)});
    }
    // Tìm khoảng cách nhỏ nhất
    long long minDistance = LLONG_MAX;
    for (const auto& p : distances) {
        if (p.second < minDistance) {
            minDistance = p.second;
        }
    }
    // In ra tất cả các số nguyên tố có khoảng cách nhỏ nhất
    cout << "Các số nguyên tố gần " << target << " nhất là: ";
    for (const auto& p : distances) {
        if (p.second == minDistance) {
            cout << p.first << " ";
        }
    }
    cout << endl;
}

int main() {
    long long L = 50, R = 500;
    vector<bool> isPrime = segmentedSieve(L, R);
    vector<long long> primes;  // Danh sách số nguyên tố
    for (long long i = 0; i < isPrime.size(); ++i) {
        if (isPrime[i]) {
            primes.push_back(L + i);
        }
    }
    // Gọi các hàm
    cout << "Danh sách các số nguyên tố từ " << L << " đến " << R << ":\n";
    listPrimes(primes);
    long long target = 237;
    findClosestPrimes(primes, target);
    return 0;
}
