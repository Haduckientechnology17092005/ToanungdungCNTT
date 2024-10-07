#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<long long> coprime;
vector<long long> perfectNumbers;

long long gcd(long long a, long long b);
void findCoprime(long long n);
void printCoprime();
bool isPrime(long long n);
void findPerfectNumbers(long long limit);
void printPerfectNumbers(const vector<long long>& perfectNumbers);

int main() {
    long long n = 102230194;
    findCoprime(n);
    printCoprime();
    cout << "Count coprime: " << coprime.size() << "\n";
    findPerfectNumbers(n);
    cout << "Count perfect numbers: " << perfectNumbers.size() << "\n";
    return 0;
}

long long gcd(long long a, long long b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

void findCoprime(long long n) {
    for (long long m = 1; m <= n; m++) {
        if (gcd(m, n) == 1) {
            coprime.push_back(m);
        }
    }
}

void printCoprime() {
    for (long long i = 0; i < coprime.size(); i++) {
        cout << coprime[i] << " ";
    }
    cout << "\n";
}

bool isPrime(long long n) {
    if (n <= 1)
        return false;
    for (long long i = 2; i <= sqrt(n); i++) {
        if (n % i == 0)
            return false;
    }
    return true;
}

void findPerfectNumbers(long long limit) {
    for (long long p = 2; p <= limit; p++) {
        if (isPrime(p)) {
            long long mersennePrime = pow(2, p) - 1;
            if (isPrime(mersennePrime)) {
                long long perfectNumber = pow(2, p - 1) * mersennePrime;
                if (perfectNumber <= limit) {
                    perfectNumbers.push_back(perfectNumber);
                }
            }
        }
    }
    printPerfectNumbers(perfectNumbers);
}

void printPerfectNumbers(const vector<long long>& perfectNumbers) {
    cout << "Perfect numbers found:\n";
    for (long long num : perfectNumbers) {
        cout << num << " ";
    }
    cout << "\n";
}
