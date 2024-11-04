#include"Danhilepski.cpp"
int main() {
    matrix A, M, M1, B;
    double lambda[3] = {0,0,0};
    int n;
    cout<<"Enter n: ";
    cin>>n;
    inputMatrix(n, A);
    Danhilepski(A, M, M1, B, n);
    solution(1, -A[0][0], -A[0][1], -A[0][2], lambda);
    cout<<"Danhilepski's solution is: Eigen value:"<<endl;
    cout << setprecision(4) << fixed << lambda[0] << endl << lambda[1] << endl << lambda[2] << endl;
    double y[3][10], x[3][10];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 10; j++) {
            y[j][i] = pow(lambda[i], n-j-1);
        }
    }
    multiMatrix(B, y, x, 3, 3, 3);
    cout<<"S: "<<endl;
    for (int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++){
            cout<<x[i][j]<<"\t";
            if(j == 2)
                cout<<endl;
        }
    }
    matrix D;
    for(int i = 0; i<3; i++){
        for(int j = 0; j<3; j++){
            if(i == j)
                D[i][j] = lambda[i];
            else
                D[i][j] = 0;
        }
    }
    cout<<"Diagonalized matrix: "<<endl;
    for(int i = 0; i<3; i++){
        for(int j = 0; j<3; j++){
            cout<<D[i][j]<<"\t";
            if(j == 2)
                cout<<endl;
        }
    }
    matrix inverse;
    invertMatrix(x, inverse, 3);
    cout<<"S^-1: "<<endl;
    for(int i = 0; i<3; i++){
        for(int j = 0; j<3; j++){
            cout<<inverse[i][j]<<"\t";
            if(j == 2)
                cout<<endl;
        }
    }
    return 0;
}
