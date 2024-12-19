#include <iostream>
#include <cmath>

using namespace std;

float grad(float x) {
    return -1/(x*x);
}

float giatriham(float x) {
    return 1/x; 
}

float GD_momentum(float x, float gamma, float alpha, int N) {
    float deltax = 0;
    float x_new;

    for (int i = 1; i <= N; ++i) {
        float deltax_new = alpha * deltax - gamma * grad(x);
        x_new = x + deltax_new;

         cout << "Vòng lặp thứ " << i 
                  << ": giá trị x = " << x 
                  << ", giá trị của hàm là: " << giatriham(x) <<  endl;

        if ( fabs(x - x_new) < 1e-5) {
            break;
        } else {
            deltax = deltax_new;
            x = x_new;
        }
    }
    return giatriham(x);
}

float GD(float x, float gamma, int N) {
    float x_new;
    for (int i = 1; i <= N; ++i) {
        x_new = x - gamma * grad(x);
         cout << "Vòng lặp thứ " << i << ": giá trị x = " << x << ", giá trị của hàm là: " << giatriham(x) <<  endl;
        if ( fabs(x - x_new) < 1e-5) {
            break;
        } else {
            x = x_new;
        }
    }
    return giatriham(x);
}

int main() {
    float x_initial = -1.0;
    float gamma = 0.001;    
    float alpha = 0.1;    
    int N = 1000;            
    cout << "Kết quả của GD_momentum: " << GD_momentum(x_initial, gamma, alpha, N) <<  endl;
    cout << "Kết quả của GD: " << GD(x_initial, gamma, N) <<  endl;
    return 0;
}
