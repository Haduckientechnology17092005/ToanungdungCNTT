#include <iostream>
#include <cmath>

using namespace std;

double function(double x) {
    return 2*log(2*x*x + 1) + 9*x + 3*exp(x*x) - 5;
}

double derivativeFunction(double x) {
    return (8*x)/(2*x*x + 1) + 9 + 6*x*exp(x*x);
}

double function1(double x) {
    return (exp(3*x)+ 12*x*x + 5*x)/(12 - 2*x) - 25*x;
}

double derivativeFunction1(double x) {
    return ((3*exp(3*x) + 24*x + 5)*(12 - 2*x) + 2*(exp(3*x) + 12*x*x + 5*x))/((12 - 2*x)*(12 - 2*x)) - 25;
}

void optimize(double alpha, double beta, double x_init, double (*objFunc)(double), double (*gradFunc)(double)) {
    double x = x_init;
    double v = 0.0; 
    int iterations = 0;

    while (iterations < 1000) {
        iterations++;
        double x_prev = x;
        
        v = beta * v + (1 - beta) * gradFunc(x);
        x = x - alpha * v;

        cout << "Objective function value at iteration " << iterations << ": x = " << x << ", function value = " << objFunc(x) << endl;
        
        if (fabs(x - x_prev) < 1e-5) {
            cout << "Optimization of the objective function completed." << endl;
            break;
        }
    }

    if (iterations == 1000) {
        cout << "Reached maximum iterations without convergence." << endl;
    }
}

int main() {
    double gamma = 0.001; 
    double alpha = 0.1;  
    double x_init = -1.0; 
    optimize(gamma, alpha, x_init, function1, derivativeFunction1);
    return 0;
}
