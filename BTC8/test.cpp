#include <iostream>
#include <cmath>

using namespace std;

// Define epsilon for convergence
constexpr double EPSILON = 1e-3;

// Function prototypes
float f(float x);
float fdh(float x);

int main() {
    float a, b;
    char continueChoice;

    while (true) {
        // Prompt user for initial guess
        cout << "\nEnter an initial guess: ";
        cin >> a;

        // Newton-Raphson method
        do {
            b = a; // Store the current value of a
            a = b - f(b) / fdh(b); // Update a using the Newton-Raphson formula
            cout << "\nPrevious value: " << b 
                 << ", f(b)/fdh(b): " << -f(b) / fdh(b) 
                 << ", Updated value: " << a;
        } while (fabs(a - b) >= EPSILON); // Check for convergence

        // Output the result
        cout << "\nRoot of the equation: " << a;

        // Ask the user if they want to continue
        cout << "\nContinue? (y/n): ";
        cin >> continueChoice;
        if (continueChoice == 'n' || continueChoice == 'N') {
            break; // Exit the loop if the user chooses not to continue
        }
    }

    return 0; // Return success
}

// Function definition for f(x)
float f(float x) {
    return (exp(3*x)+ 12*x*x + 5*x)/(12 - 2*x) - 25*x;
}

float fdh(float x){
    return ((3*exp(3*x) + 24*x + 5)*(12 - 2*x) + 2*(exp(3*x) + 12*x*x + 5*x))/((12 - 2*x)*(12 - 2*x)) - 25;
}
