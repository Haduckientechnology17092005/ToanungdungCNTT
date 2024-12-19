#include <iostream>
#include <cmath>

using namespace std;

double objectiveFunction(double x, double y) {
    double result = 20*x*x + 14*x*y + 20*y*y - (4*x + 5*y);
    return result;
}

double derivativeX(double x, double y) {
    double dfx = 40*x + 14*y - 4;
    return dfx;
}

double derivativeY(double x, double y) {
    double dfy = 14*x + 40*y - 5;
    return dfy;
}

void optimize(double learningRate, double &xStart, double &yStart) {
    double x = xStart;
    double y = yStart;
    int iterationCount = 0;
    while (iterationCount < 1000) {
        iterationCount++;
        double xPrev = x, yPrev = y;
        x = x - learningRate * derivativeX(x, y);
        y = y - learningRate * derivativeY(x, y);
        cout << "Iteration " << iterationCount << ": x = " << x << ", y = " << y
             << ", Objective function value = " << objectiveFunction(x, y) << endl;
        if (fabs(x - xPrev) < 1e-5 && fabs(y - yPrev) < 1e-5) {
            cout << "Optimization completed successfully." << endl;
            break;
        }
    }
    if (iterationCount == 1000) {
        cout << "Reached maximum iterations without convergence." << endl;
    }
    cout << "Minimum value of the objective function: f(" << x << "," << y << ") = " << objectiveFunction(x, y) << endl;
}

int main() {
    double alpha = 0.01;
    double xStart = 1.0; 
    double yStart = 1.0;
    cout << "Optimizing the objective function using Gradient Descent without Momentum:" << endl;
    optimize(alpha, xStart, yStart);
    cout << "Goodbye!" << endl;
    return 0;
}
