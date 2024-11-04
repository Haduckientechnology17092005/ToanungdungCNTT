#include <iostream>
#include <cmath>
#include<vector>
using namespace std;

vector<int> primenumber;

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
bool isPrime(int num) {
    if (num <= 1) return false;
    for (int i = 2; i <= sqrt(num); i++) {
        if (num % i == 0) return false;
    }
    return true;
}
int main() {
    int N = 3000;
    int M = -1;
    int j = 1;
    for (int i = N - 1; i > 1; i--) {
        if (isPerfectNumber(i)) {
            M = i;
            break;
        }
    }
    if (M != -1) {
        cout << "Perfect number nearest and lower than " << N << " is: " << M << endl;
        int sumPrimes = 0;
        cout << "Primenumer lower than " << M << " are: \n";
        for (int i = 2; i < M; i++) {
            if (isPrime(i)) {
                primenumber.push_back(i);
                sumPrimes += i;
            }
        }
        for(int i = 0; i<primenumber.size(); i++){
            cout<<primenumber[i]<<" ";
            if(i%16 == 0 && i!=0) 
                cout<<endl;
        }
        cout << endl;
        cout << "Sum of primenumber lower than " << M << " la: " << sumPrimes << endl;
    } else {
        cout << "No perfect number lower than " << N << endl;
    }
    return 0;
}
