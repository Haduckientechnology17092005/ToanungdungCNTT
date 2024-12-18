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

void optimize(double learningRate, double momentum, double &xStart, double &yStart) {
    double x = xStart;
    double y = yStart;
    double velocityX = 0.0, velocityY = 0.0;
    int iterationCount = 0;
    while (iterationCount < 1000) {
        iterationCount++;
        double xPrev = x, yPrev = y;
        // Calculate momentum and update the values of x and y
        velocityX = momentum * velocityX + (1 - momentum) * derivativeX(x, y);
        velocityY = momentum * velocityY + (1 - momentum) * derivativeY(x, y);
        x = x - learningRate * velocityX;
        y = y - learningRate * velocityY; 
        // Print the values of x, y, and momentum (lambda) at each step
        cout << "Iteration " << iterationCount << ": x = " << x << ", y = " << y
             << ", momentum_x = " << velocityX << ", momentum_y = " << velocityY
             << ", Objective function value = " << objectiveFunction(x, y) << endl;

        // Check convergence condition
        if (fabs(x - xPrev) < 1e-5 && fabs(y - yPrev) < 1e-5) {
            cout << "Optimization completed successfully." << endl;
            break;
        }
    }
    //check for maximum number of iterations
    if (iterationCount == 1000) {
        cout << "Reached maximum iterations without convergence." << endl;
    }
    cout << "Minimum value of the objective function: f(" << x << "," << y << ") = " << objectiveFunction(x, y) << endl;
}

int main() {
    double alpha = 0.01;   
    double beta = 0.9;        
    double xStart = 1.0;         
    double yStart = 1.0;         
    cout << "Optimizing the objective function using Gradient Descent with Momentum:" << endl;
    optimize(alpha, beta, xStart, yStart);
    cout << "Goodbye!" << endl;
    return 0;
}
