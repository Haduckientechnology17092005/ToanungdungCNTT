#include<iostream>
#include<math.h>
#include<vector>
#include<time.h>

using namespace std;

int x,y, gcd;

void extendedEuclid(int a, int b){
    if(b == 0){
        x = 1;
        y = 0;
        gcd = a;
        return;
    }
    extendedEuclid(b, a % b);
    int x1 = y;
    int y1 = x - (a / b) * y;
    x = x1;
    y = y1;
    return;
}

long long modunlarInverse(int a, int m){
    extendedEuclid(a, m);
    return (x+m)%m;
}

void input(int n, vector<int> &A, vector<int> &M){
    cout<<"Nhap cac phuong trinh (a mod b): \n";
    for(int i = 0; i<n; i++){
        cout<<"Nhap phuong trinh so: "<<i+1<<": ";
        int a, m;
        cin>>a;
        cin>>m;
        A.push_back(a);
        M.push_back(m);
    }
}

long long ChineseRemainderTheorem(vector<int> A, vector<int> M){
    long long result = 0;
    long long prod = 1;
    for(int i = 0; i<A.size(); i++){
        prod *= M[i];
    }
    for(int i = 0; i<A.size(); i++){
        long long p = prod / M[i];
        result = (result + A[i] * modunlarInverse(p, M[i]) * p) % prod;
    }
    return result;
}

int main(){
    clock_t start, end;
    start = clock();
    int n;
    cout<<"Enter number of equations: ";
    cin>>n;
    vector<int> A, M;
    input(n, A, M);
    long long prod = 1;
    for(int i = 0; i<M.size(); i++){
        prod *= M[i];
    }
    long long result = ChineseRemainderTheorem(A, M);
    cout<<"Result: x = "<<result<<" + k"<<prod<<endl;
    end = clock();
    cout<<"Time taken: "<<(double)(end-start)/CLOCKS_PER_SEC<<"s\n";
    return 0;
}

