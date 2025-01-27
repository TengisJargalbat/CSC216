#include <iostream>
#include <cmath>
#include <chrono>
using namespace std;
using namespace std::chrono;

int naivePower(int x, int n){
    if (x == 0) return 0;
    if (n == 0) return 1;
    return x * naivePower(x, n - 1);
}

int unoptimizedDCPower(int x, int n){
    if (x == 0) return 0;
    if (n == 0) return 1;
    if(n % 2 == 0){
        return unoptimizedDCPower(x, n / 2) * unoptimizedDCPower(x, n / 2);
    } else {
        return x * unoptimizedDCPower(x, n / 2) * unoptimizedDCPower(x, n / 2);
    }
}

int optimizedDCPower(int x, int n){
    if (x == 0) return 0;
    if (n == 0) return 1;

    int temp = optimizedDCPower(x, n / 2);

    if(n % 2 == 0){
        return temp * temp;
    } else {
        return x * temp * temp;
    }
}

int main(){
    // Example inputs
    int base = 2;
    int exponent = 10000;

    // --- Naive Power ---
    auto startNaive = high_resolution_clock::now();
    int resultNaive = naivePower(base, exponent);
    auto stopNaive = high_resolution_clock::now();
    auto durationNaive = duration_cast<nanoseconds>(stopNaive - startNaive);
    cout << "naivePower(" << base << ", " << exponent << ") = " 
         << resultNaive << "\n";
    cout << "Time (naive): " 
         << durationNaive.count() << " ns\n\n";

    // --- Unoptimized Divide and Conquer Power ---
    auto startUnopt = high_resolution_clock::now();
    int resultUnopt = unoptimizedDCPower(base, exponent);
    auto stopUnopt = high_resolution_clock::now();
    auto durationUnopt = duration_cast<nanoseconds>(stopUnopt - startUnopt);
    cout << "unoptimizedDCPower(" << base << ", " << exponent << ") = " 
         << resultUnopt << "\n";
    cout << "Time (unoptimized DC): " 
         << durationUnopt.count() << " ns\n\n";

    // --- Optimized Divide and Conquer Power ---
    auto startOpt = high_resolution_clock::now();
    int resultOpt = optimizedDCPower(base, exponent);
    auto stopOpt = high_resolution_clock::now();
    auto durationOpt = duration_cast<nanoseconds>(stopOpt - startOpt);
    cout << "optimizedDCPower(" << base << ", " << exponent << ") = " 
         << resultOpt << "\n";
    cout << "Time (optimized DC): " 
         << durationOpt.count() << " ns\n\n";

    // Pause at the end (optional)
    int x;
    cin >> x;

    return 0;
}
