#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

vector<long long> alpha, p, divisor, sieve;

bool isPrime(long long n) {
    if(n<=1)
        return false;
    for(long long i = 2; i <= sqrt(n); i++) {
        if(n%i==0){
            return false;
        }
    }
    return true;
}

void find_prime(long long n){
    for(long long i = 1; i<=n; i++){
        if(isPrime(i))
            p.push_back(i);
    }
    return;
}

void find_exponent(long long n){
    for(long long i = 0; i<p.size(); i++){
        long long exponent = 0;
        while(n!=1){
         if(n%p[i]) break;
         exponent++;
         n = n/p[i];   
        }
        alpha.push_back(exponent);
    }
    return;
}

void displayPrimeFactorization(long long n){
    long long i = 0;
    cout<<"Prime factors of "<<n<<" = ";
    for(i = 0; i<p.size(); i++){
        if(alpha[i] != 0){
            if(alpha[i] == 1)
                cout << p[i];
            else
                cout << p[i] <<"^"<<alpha[i];
            break;    
        }
    }
    for(i=++i;i<p.size(); i++){
        if(alpha[i] != 0){
            if(alpha[i] == 1)
                cout<<"*"<< p[i];
            else
                cout<<"*"<< p[i] <<"^"<<alpha[i];  
        }
    }
    cout<<"\n";
    return;
}
long long number_of_divisors(long long n){
    long long count = 1;
    for(long long i = 0; i<alpha.size(); i++){
        count = count*(alpha[i]+1);
    }
    cout<<"Number of divisors: "<<count<<"\n";
    return count;
}

void print_number_of_divisors(long long n){
    for(long long i = 1; i <= n; i++){
        if(n%i == 0){
            divisor.push_back(i);
        }
    }
    cout<<"Divisors: ";
    for(int i = 0; i<divisor.size(); i++){
        cout<<divisor[i]<<" ";
    }
    cout<<"\n";
    return;
}

long long sum_of_factors(long long n){
    long long sum = 1;
    for(long long i = 0; i<p.size(); i++){
        sum = sum*((long long)pow(p[i],alpha[i]+1)-1)/(p[i]-1);
    }
    cout<<"Sum of factors: "<<sum<<"\n";
    return sum;
}

long long product_of_factors(long long n){
    long long number_of_factors = number_of_divisors(n);
    long long product = pow(n, number_of_factors/2);
    cout<<"Product of factors: "<<product<<"\n";
    return product;
}

bool isPerfectNumber(long long n) {
    long long xichma = sum_of_factors(n);
    if(xichma==2*n){
        return true;
    } else {
        return false;
    }
}

bool isPerfectNumber_v2(long long n) {
    long long sum = 0;
    for (long long i = 1; i < n; i++) {
        if (n % i == 0) {
            sum += i;
        }
    }
    if (sum == n) {
        return true;
    } else {
        return false;
    }
}

void print_factors_of_perfect_numbers(long long n){
    long long temp = 0;
    if(isPerfectNumber_v2(n)){
        cout<<"Perfect numbers: ";
        cout<<n<<" = ";
        for(long long i = 0; i<divisor.size(); i++){
            temp = divisor[i];
            if(temp < n/2){
                cout<<divisor[i]<<"+";   
            } 
            else if (temp == n/2){
                cout<<divisor[i];
            }
            else{
                break;
            }
        }
    }
    cout<<"\n";
    return;
}

void density_of_prime_factors_v2(long long n){
    long long count = 0;
    for(long long i = 2; i<=n; i++){
        if(isPrime(i)){
            count++;
        }
    }
    cout<<"Density of prime factors (true): "<<count<<"\n";
    return;
}
void density_of_prime_factors(long long n){
    long long pi;
    pi = n/log(n);
    cout<<"Density of prime factors (approx): "<<pi<<"\n";
    return;
}

void SieveOfEratosthenes(long long n){
    for(long long i = 0; i<= n; i++){
        sieve.push_back(0);
    }
    for(long long i = 2; i<=n; i++){
        if(sieve[i]) continue;
        for(long long j = 2*i; j<=n; j+=i){
            sieve[j] = i;
        }
    }
    return;
}

void PrintSieveOfEratosthenes(long long n){
    cout<<"Number: ";
    for(long long i = 2; i<=n; i++){
        cout<<i<<" ";
    }
    cout<<"\nSieve: ";
    for(long long i = 2; i<sieve.size(); i++){
        cout<<sieve[i]<<" ";
    }
    cout<<"\n";
    cout<<"Prime numbers: ";
    for(long long i = 2; i<=n; i++){
        if(sieve[i] == 0){
            cout<<i<<" ";
        }
    }
    cout<<"\n";
    return;
}

vector<long long> SieveOfEratosthenes_a_to_n(long long a, long long n){
    vector<bool>prime(n+1, true);
    for (long long p = 2; p * p <= n; p++) {
        if (prime[p] == true) {
            for (long long i = p * p; i <= n; i += p)
                prime[i] = false;
        }
    }
    vector<long long>primes;
    for(long long p = a; p <= n; p++){
        if (prime[p])
            primes.push_back(p);
    }
    return primes;
}

void print_primes_a_to_n(long long a, long long n){
    vector<long long>primes = SieveOfEratosthenes_a_to_n(a, n);
    cout<<"Prime numbers from "<<a<<" to "<<n<<": ";
    for(long long i = 0; i<primes.size(); i++){
        cout<<primes[i]<<" ";
    }
    cout<<"\n";
    return;
}

void sum_primes_2_to_n(long long n){
    vector<long long>primes = SieveOfEratosthenes_a_to_n(2, n);
    long long sum = 0;
    for(long long i = 0; i<primes.size(); i++){
        sum += primes[i];
    }
    cout<<"Sum of prime numbers from 2 to "<<n<<": "<<sum<<"\n";
    return;
}

void product_primes_2_to_n(long long n){
    vector<long long>primes = SieveOfEratosthenes_a_to_n(2, n);
    long long product = 1;
    for(long long i = 0; i<primes.size(); i++){
        product *= primes[i];
    }
    cout<<"Product of prime numbers from 2 to "<<n<<": "<<product<<"\n";
    return;
}
void sum_primes_a_to_n(long long a, long long n){
    vector<long long>primes = SieveOfEratosthenes_a_to_n(a, n);
    long long sum = 0;
    for(long long i = 0; i<primes.size(); i++){
        sum += primes[i];
    }
    cout<<"Sum of prime numbers from "<<a<<" to "<<n<<": "<<sum<<"\n";
    return;
}

void product_primes_a_to_n(long long a, long long n){
    vector<long long>primes = SieveOfEratosthenes_a_to_n(a, n);
    long long product = 1;
    for(long long i = 0; i<primes.size(); i++){
        product *= primes[i];
    }
    if(product == 1)
        cout<<"Product of prime numbers from "<<a<<" to "<<n<<": 0\n";
    else
        cout<<"Product of prime numbers from "<<a<<" to "<<n<<": "<<product<<"\n";
    return;
}

int main(){
    long long n;
    long long a;
    cout<<"Enter a number n = ";
    cin>>n;
    cout<<"Enter a number a = ";
    cin>>a;
    if(isPrime(n)){
        cout<<n<<" is a prime number\n";
    } else {
        cout<<n<<" is not a prime number\n";
    }
    find_prime(n);
    find_exponent(n);
    displayPrimeFactorization(n);
    number_of_divisors(n);
    print_number_of_divisors(n);
    sum_of_factors(n);
    product_of_factors(n);
    if(isPerfectNumber(n)){
        cout<<n<<" is a perfect number c1\n";
    } else {
        cout<<n<<" is not a perfect number c1\n";
    }
    if(isPerfectNumber_v2(n)){
        cout<<n<<" is a perfect number c2\n";
    } else {
        cout<<n<<" is not a perfect number c2\n";
    }
    print_factors_of_perfect_numbers(n);
    density_of_prime_factors(n);
    density_of_prime_factors_v2(n);
    SieveOfEratosthenes(n);
    PrintSieveOfEratosthenes(n);
    print_primes_a_to_n(a, n);
    sum_primes_2_to_n(n);
    product_primes_2_to_n(n);
    sum_primes_a_to_n(a, n);
    product_primes_a_to_n(a, n);
    return 0;
}