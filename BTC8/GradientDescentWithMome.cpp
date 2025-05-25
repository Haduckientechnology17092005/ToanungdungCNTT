#include <iostream>
#include <cmath>

using namespace std;

double function1(double x) {
    return (log10(2*x*x + exp(8*x)+14*x*x - 6*x))/(2*x*x+1) - 4*x*x;
}

double derivativeFunction1(double x) {
    return ((-4*x*(log10(2*x*x+1)+exp(8*x)+14*x*x-6*x))+(2*x*x+1)*(((4*x)/(log(10)*(2*x*x+1)))+8*exp(8*x)+28*x-6))/((2*x*x+1)*(2*x*x+1)) - 8*x;
}

void optimize(double gamma, double alpha, double x_init, double (*objFunc)(double), double (*gradFunc)(double)) {
    double x = x_init;
    double v = 0.0; 
    int iterations = 0;
    while (iterations < 3000) {
        iterations++;
        double x_prev = x;
        v = alpha * v + (1 - alpha) * gradFunc(x);
        x = x - gamma * v;
        cout << "Objective function value at iteration " << iterations << ": x = " << x << ", function value = " << objFunc(x) << endl;
        if (fabs(x - x_prev) < 1e-5) {
            cout << "Optimization of the objective function completed." << endl;
            cout << "Optimal value of x: " << objFunc(x) << endl;
            break;
        }
    }
    if (iterations == 3000) {
        cout << "Reached maximum iterations without convergence." << endl;
    }
}

int main() {
    double gamma = 0.001; 
    double alpha = 0.01;  
    double x_init = -2.0; 
    optimize(gamma, alpha, x_init, function1, derivativeFunction1);
    return 0;
}
