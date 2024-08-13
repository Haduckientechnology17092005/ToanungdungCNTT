#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<iostream>
#include<vector>
using namespace std;

vector<long long> alpha, p, divisor; 

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

void display(long long n){
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
    //cout<<"Sum of factors: "<<sum<<"\n";
    return sum;
}

void product_of_factors(long long n){
    long long number_of_factors = number_of_divisors(n);
    long long product = pow(n, number_of_factors/2);
    cout<<"Product of factors: "<<product<<"\n";
    return;
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
    cout<<"Perfect numbers: ";
    cout<<n<<" = ";
    if(isPerfectNumber_v2(n)){
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

void density_of_prime_factors(long long n){
    long long pi;
    pi = n/log(n);
    cout<<"Density of prime factors: "<<pi<<"\n";
    return;
}
int main(){
    long long n;
    cout<<"Enter a number: ";
    cin>>n;
    find_prime(n);
    find_exponent(n);
    display(n);
    number_of_divisors(n);
    print_number_of_divisors(n);
    sum_of_factors(n);
    product_of_factors(n);
    print_factors_of_perfect_numbers(n);
    density_of_prime_factors(n);
    return 0;
}