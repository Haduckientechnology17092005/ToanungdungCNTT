#include <iostream>
#include <cmath>

using namespace std;

constexpr double EPSILON = 1e-5;
constexpr int MAX_ITERATIONS = 1000;

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

// Newton-Raphson method to find the root of the function
void newtonRaphson(double (*func)(double), double (*derivFunc)(double), double initial_guess) {
    double x = initial_guess;
    double h = func(x) / derivFunc(x);
    int iterations = 0;

    while (abs(h) >= EPSILON && iterations < MAX_ITERATIONS) {
        h = func(x) / derivFunc(x);
        x = x - h;
        iterations++;
        // Debug outputs
        cout << "Iteration " << iterations << ": x = " << x 
             << ", func(x) = " << func(x) 
             << ", derivFunc(x) = " << derivFunc(x) 
             << ", h = " << h << endl;
    }
    if (iterations < MAX_ITERATIONS) {
        cout << "The root of the function is approximately: " << x << endl;
    } else {
        cout << "The method did not converge within " << MAX_ITERATIONS << " iterations." << endl;
    }
}

int main() {
    double initial_guess2 = 0.0;
    newtonRaphson(function1, derivativeFunction1, initial_guess2);
    return 0;
}
