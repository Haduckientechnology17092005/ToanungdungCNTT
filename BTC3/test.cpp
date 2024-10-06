#include<iostream>
#include<string>
using namespace std;

int x =4;
int &Func(){
    static int x =5;
    return x;
}
int Func1(){
    int x = 5;
    return x;
}
int main(){
    cout<<x;
    cout<<Func();
    Func() = 8;
    cout<<x;
    cout<<Func();
    return 0;
}