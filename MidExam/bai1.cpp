#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

// Hàm kiểm tra số hoàn hảo
bool isPerfectNumber(int num) {
    int sum = 1;
    for (int i = 2; i <= sqrt(num); i++) {
        if (num % i == 0) {
            sum += i;
            if (i != num / i) {
                sum += num / i;
            }
        }
    }
    return sum == num;
}

// Hàm kiểm tra số nguyên tố
bool isPrime(int num) {
    if (num <= 1) return false;
    for (int i = 2; i <= sqrt(num); i++) {
        if (num % i == 0) return false;
    }
    return true;
}

// Hàm tìm số hoàn hảo nhỏ hơn N
int findNearestPerfectNumber(int N) {
    for (int i = N - 1; i > 1; i--) {
        if (isPerfectNumber(i)) {
            return i;
        }
    }
    return -1; // Không tìm thấy số hoàn hảo
}

// Hàm tìm các số nguyên tố nhỏ hơn một số M
vector<int> findPrimesBelow(int M) {
    vector<int> primes;
    for (int i = 2; i < M; i++) {
        if (isPrime(i)) {
            primes.push_back(i);
        }
    }
    return primes;
}

// Hàm tính tổng của một vector số nguyên
int sumOfVector(const vector<int>& nums) {
    int sum = 0;
    for (int num : nums) {
        sum += num;
    }
    return sum;
}

// Hàm in các số nguyên tố với định dạng đẹp
void printPrimes(const vector<int>& primes) {
    const int columnsPerRow = 16; // Số cột mỗi hàng
    for (size_t i = 0; i < primes.size(); i++) {
        cout << primes[i] << " ";
        if ((i + 1) % columnsPerRow == 0) {
            cout << endl;
        }
    }
    cout << endl;
}

int main() {
    int N = 3000; // Số giới hạn

    // Tìm số hoàn hảo gần nhất nhỏ hơn N
    int M = findNearestPerfectNumber(N);
    if (M != -1) {
        cout << "Perfect number nearest and lower than " << N << " is: " << M << endl;

        // Tìm các số nguyên tố nhỏ hơn M
        vector<int> primes = findPrimesBelow(M);
        cout << "Primenumber lower than " << M << " are: \n";
        printPrimes(primes);

        // Tính tổng các số nguyên tố
        int sumPrimes = sumOfVector(primes);
        cout << "Sum of primenumber lower than " << M << " is: " << sumPrimes << endl;
    } else {
        cout << "No perfect number lower than " << N << endl;
    }

    return 0;
}
