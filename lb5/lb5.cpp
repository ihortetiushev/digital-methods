#include <iostream>
#include <functional>
#include <iomanip>

using namespace std;

double fx(double x) {
    return pow(x, 4) + 5 * pow(x, 3) + 3 * pow(x, 2) - 4 * x - 1;
}
double trapezoidMethod() {
    return 0;
}
double trapezoidMethod(double a, double b, int n, const function<double(double)>& f) {
    const double width = (b - a) / n;

    double result = 0;
    for (int step = 0; step < n; step++) {
        const double x1 = a + step * width;
        const double x2 = a + (step + 1) * width;

        result += 0.5 * (x2 - x1) * (f(x1) + f(x2));
    }

    return result;
}

double simpsonMethod(double a, double b, int n, const function<double(double)>& f) {
    const double width = (b - a) / n;

    double result = 0;
    for (int step = 0; step < n; step++) {
        const double x1 = a + step * width;
        const double x2 = a + (step + 1) * width;

        result += (x2 - x1) / 6.0 * (f(x1) + 4.0 * f(0.5 * (x1 + x2)) + f(x2));
    }

    return result;
}
int main()
{
    const double PRESICE_VALUE = 24.4;
    const double a = 0.0;
    const double b = 2.0;
    const int n = 200000;
    double result = trapezoidMethod(a, b, n, fx);
    cout << "trapezoidMethod = " << fixed <<  setprecision(12) << result << endl;
    result = simpsonMethod(a, b, n, fx);
    cout << "simpsonMethod = " << fixed << setprecision(12) << result << endl;
}
