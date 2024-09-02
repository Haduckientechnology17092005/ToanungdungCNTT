#include<iostream>
#include<math.h>
#include<vector>
#include<time.h>

using namespace std;

bool check_formulas(long long x, long long y, long long m){
    return (x+y)%m == (x%m + y%m)%m;
}

bool check_formulas2(long long x, long long y, long long m){
    return (x-y)%m == (x%m - y%m)%m;
}

bool check_formulas3(long long x, long long y, long long m){
    return (x*y)%m == (x%m * y%m)%m;
}
 bool check_formulas4(long long x, long long n, long long m){
    long long a = pow(x,n);
    long long a1 = pow(x%m, n);
    return a%m == a1%m;
 }

int main(){
    clock_t start, end;
    start = clock();
    long long x,y,m,n;
    cout<<"Enter x, y, m, n: ";
    cin>>x>>y>>m>>n;
    cout<<"check_formulas: ";
    if(check_formulas(x,y,m)) cout<<"True\n";
    else cout<<"False\n";
    cout<<"check_formulas2: ";
    if(check_formulas2(x,y,m)) cout<<"True\n";
    else cout<<"False\n";
    cout<<"check_formulas3: ";
    if(check_formulas3(x,y,m)) cout<<"True\n";
    else cout<<"False\n";
    cout<<"check_formulas4: ";
    if(check_formulas4(x,n,m)) cout<<"True\n";
    else cout<<"False\n";
    end = clock();
    cout<<"Time taken: "<<(double)(end-start)/CLOCKS_PER_SEC<<"s\n";
    return 0;
}
