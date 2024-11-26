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

double secondDerivativeXX(double x, double y) {
    return 40; 
}

double secondDerivativeYY(double x, double y) {
    return 40;
}

double secondDerivativeXY(double x, double y) {
    return 14;
}

void optimize(double xStart, double yStart) {
    double x = xStart;
    double y = yStart;
    int iterationCount = 0;
    
    while (iterationCount < 1000) {
        iterationCount++;
        double xPrev = x, yPrev = y;
        double gradX = derivativeX(x, y);
        double gradY = derivativeY(x, y);
        double hessianXX = secondDerivativeXX(x, y);
        double hessianYY = secondDerivativeYY(x, y);
        double hessianXY = secondDerivativeXY(x, y);
        double determinant = hessianXX * hessianYY - hessianXY * hessianXY;
        double inverseHessianXX = hessianYY / determinant;
        double inverseHessianYY = hessianXX / determinant;
        double inverseHessianXY = -hessianXY / determinant;
        double deltaX = inverseHessianXX * gradX + inverseHessianXY * gradY;
        double deltaY = inverseHessianXY * gradX + inverseHessianYY * gradY;
        x = x - deltaX;
        y = y - deltaY;
        cout << "Iteration " << iterationCount << ": x = " << x << ", y = " << y
             << ", Objective function value = " << objectiveFunction(x, y) << endl;
        if (fabs(x - xPrev) < 1e-5 && fabs(y - yPrev) < 1e-5) {
            cout << "Optimization completed successfully." << endl;
            break;
        }
    }

    // If the algorithm doesn't converge after 1000 iterations
    if (iterationCount == 1000) {
        cout << "Reached maximum iterations without convergence." << endl;
    }
    cout << "Minimum value of the objective function: f(" << x << "," << y << ") = " << objectiveFunction(x, y) << endl;
}

int main() {
    double xStart = 1.0;     
    double yStart = 1.0;         
    cout << "Optimizing the objective function using Newton's Method:" << endl;
    optimize(xStart, yStart);
    cout << "Goodbye!" << endl;
    return 0;
}
