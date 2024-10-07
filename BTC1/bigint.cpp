#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

void removeZero(vector<int>& v){
    while (v.size() > 1 && v.back() == 0){
        v.pop_back();
    }
}

void init(string s1, vector<int>& v1){
    for(int i = s1.size() - 1; i >= 0; i--){
        v1.push_back(s1[i] - '0');
    }
    removeZero(v1);
}

void print(const vector<int>& v){
    for(int i = v.size() - 1; i >= 0; i--){
        cout << v[i];
    }
    cout << endl;
}

void add(vector<int>& v1, vector<int>& v2, vector<int>& v3){
    v3.clear();
    int length = max(v1.size(), v2.size());
    v1.resize(length, 0);  
    v2.resize(length, 0);  
    int extra = 0;
    int temp;
    for(int i = 0; i < length; i++){
        temp = v1[i] + v2[i] + extra;
        v3.push_back(temp % 10);
        extra = temp / 10;
    }
    if(extra > 0){
        v3.push_back(extra);
    }
}

void mul(vector<int>& v1, vector<int>& v2, vector<int>& v3){
    v3.clear();
    v3.resize(v1.size() + v2.size(), 0); 

    for(int i = 0; i < v1.size(); i++){
        int extra = 0;
        for(int j = 0; j < v2.size(); j++){
            int temp = v3[i + j] + v1[i] * v2[j] + extra;
            v3[i + j] = temp % 10;
            extra = temp / 10;
        }
        v3[i + v2.size()] += extra;  
    }
    removeZero(v3); 
}

int main(){
    string s1 = "122020393930838939393";
    string s2 = "12202039393003003";
    vector<int> v1, v2, v3;
    init(s1, v1);
    init(s2, v2);
    mul(v1, v2, v3);
    print(v3);
    return 0;
}
