#include<iostream>
#include<math.h>
#include<vector>
#include<time.h>
#include<cmath>

using namespace std;

vector<long long> p;
vector<long long> alpha;

long long gcd(long long a, long long b){
    if(b == 0)
        return a;
    if(a == 0)
        return b;
    while(a!=b){
        if(a>b){
            a = a-b;
        }
        else {
            b = b-a;
        }
    }
    return a;
}

long long gcdv2(long long a, long long b){
    if(b == 0)
        return a;
    if(a == 0)
        return b;
    return gcdv2(b, a%b);
}

long long lcm(long a, long long b){
    if(a == 0 || b == 0)
        return 0;
    long long GCD = gcd(a,b);
    long long LCM = (a*b)/GCD;
    return LCM;
}

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

long long Euler_totient(long long n){
    find_prime(n);
    find_exponent(n);
    long long result = 1;
    for(long long i = 0; i<p.size(); i++){
        if (alpha[i] != 0)
            result = result*(pow(p[i],alpha[i]-1))*(p[i]-1);
        else 
            continue;
    }
    return result;
}

void print_coprime_from_m_to_n(long long m, long long n){
    for(long long i = m; i<=n; i++){
        if(gcd(i,n) == 1) cout<<i<<" ";
    }
    cout<<"\n";
    return;
}

void print_coprime(long long n){
    for(long long i = 1; i<n; i++){
        if(gcd(i,n) == 1) cout<<i<<" ";
    }
    cout<<"\n";
    return;
}

int main(){
    clock_t start, end;
    start = clock();
    long long a,b,n,m;
    cout<<"Enter two numbers to find GCD and LCM: \n";
    cout<<"a: ";
    cin>>a;
    cout<<"b: ";
    cin>>b;
    cout<<"GCD(cach 1): "<<gcd(a,b)<<endl;
    cout<<"GCD(cach 2): "<<gcdv2(a,b)<<endl;
    cout<<"LCM: "<<lcm(a,b)<<endl;
    cout<<"Enter a number to find coprime: ";
    cin>>n;
    cout<<"number of co-primes: ";
    cout<<Euler_totient(n)<<"\n";
    cout<<"Coprime numbers from 1 to "<<n<<" are: ";
    print_coprime(n);
    cout<<"Enter a number to find coprime: ";
    cin>>m;
    if(m>n)
        cout<<"Enter m <= n";
    cout<<"Coprime number from "<<m<<" to "<<n<<" : ";
    print_coprime_from_m_to_n(m,n);
    end = clock();
    cout<<"Time taken: "<<(double)(end-start)/CLOCKS_PER_SEC<<"s"<<endl;
    return 0;
}

