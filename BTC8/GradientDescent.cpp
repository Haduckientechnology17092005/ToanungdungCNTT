#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

// Gradient of f(x) = 1/x
 float function( float x) {
    return 2*log(2*x*x + 1) + 9*x + 3*exp(x*x) - 5;
}

 float derivativeFunction( float x) {
    return (8*x)/(2*x*x + 1) + 9 + 6*x*exp(x*x);
}

 float function1( float x) {
    return (exp(3*x)+ 12*x*x + 5*x)/(12 - 2*x) - 25*x;
}

 float derivativeFunction1( float x) {
    return ((3*exp(3*x) + 24*x + 5)*(12 - 2*x) + 2*(exp(3*x) + 12*x*x + 5*x))/((12 - 2*x)*(12 - 2*x)) - 25;
}

// SGD function with function pointers for gradient and objective function
float SGD(float x_init, float learning_rate, int epochs, float (*gradFunc)(float), float (*objFunc)(float)) {
    float x = x_init;

    for (int i = 1; i <= epochs; ++i) {
        float x_prev = x;
        
        // Stochastic gradient update
        x = x - learning_rate * gradFunc(x);
        
        // Output the current status
        cout << "Iteration " << i << ": x = " << x << ", function value = " << objFunc(x) << endl;
        
        // Check for convergence
        if (fabs(x - x_prev) < 1e-5) {
            cout << "Convergence reached after " << i << " iterations." << endl;
            break;
        }
        
        // Prevent divergence by ensuring x does not approach zero
        if (x <= 0) {
            cout << "x approached non-positive value, stopping." << endl;
            break;
        }
    }
    return objFunc(x);
}

int main() {
    float x_initial = 0.1; 
    float learning_rate = 0.001; 
    int epochs = 1000;  
    cout << "Result of SGD: " << SGD(x_initial, learning_rate, epochs, derivativeFunction1, function1) << endl;
    return 0;
}
