#include<iostream>
#include<cmath>
#include<iomanip>
#include<vector>

using namespace std;

vector<long long> coprime;
vector<long long> perfectnumber;

bool isPrime(long long n);
long long nearestPrime(long long n);
long long gcd(long long a, long long b);
void findcoprime(long long n);
void printcoprime();
bool isPerfectNumber(long long n);
void findPerfectNumber(long long n);
void printPerfectNumber();
long long sumperfectnumber(long long n);

int main(){
    long long n;
    cout<<"Enter a number n = ";
    cin>>n;
    cout<<"Nearest prime number: "<<nearestPrime(n)<<"\n";
    findcoprime(n);
    cout<<"Count coprime: "<<coprime.size()<<"\n";
    cout<<"Find perfect number from 1 to 1000: "<<"\n";
    findPerfectNumber(n);
    printPerfectNumber();
    cout<<"Count perfect number: "<<perfectnumber.size()<<"\n";
    cout<<"Sum of perfect number: "<<sumperfectnumber(n)<<"\n";
    return 0;
}

bool isPrime(long long n){
    if(n<=1)
        return false;
    for(long long i = 2; i <= sqrt(n); i++){
        if(n%i==0){
            return false;
        }
    }
    return true;
}
long long nearestPrime(long long n){
    long long lower = n-1;
    long long upper = n+1;
    while(true){
        if(lower>1 && isPrime(lower)){
            return lower;
        }
        if(isPrime(upper)){
            return upper;
        }
        lower--;
        upper++;
    }
}

long long gcd(long long a, long long b){
    if(b == 0)
        return a;
    if(a == 0)
        return b;
    return gcd(b, a%b);
}
void findcoprime(long long n){
    for(int m = 1; m <= 1000; m++){
        if(gcd(m,n) == 1){
            coprime.push_back(m);
        }
    }
}
void printcoprime(){
    for(int i = 0; i<coprime.size(); i++){
        cout<<coprime[i]<<" ";
    }
    cout<<"\n";
}

bool isPerfectNumber(long long n){
    long long sum = 0;
    for(int i = 1; i<n; i++){
        if(n%i == 0){
            sum += i;
        }
    }
    if(sum == n)
        return true;
    return false;
}
void findPerfectNumber(long long n){
    for(int i = 0; i<coprime.size(); i++){
        if(isPerfectNumber(coprime[i])){
            perfectnumber.push_back(coprime[i]);
        }
    }
}
void printPerfectNumber(){
    for(int i = 0; i<perfectnumber.size(); i++){
        cout<<perfectnumber[i]<<" ";
    }
    cout<<"\n";
}

long long sumperfectnumber(long long n){
    long long sum = 0;
    for(int i = 0; i<perfectnumber.size(); i++){
        sum += perfectnumber[i];
    }
    return sum;
}