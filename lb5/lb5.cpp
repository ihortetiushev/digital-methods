#include <iostream>
#include <functional>
#include <iomanip>

using namespace std;

double fx(double x) {
	//y=x^4 + 5x^3 +3x^2 -4x - 1
	return pow(x, 4) + 5 * pow(x, 3) + 3 * pow(x, 2) - 4 * x - 1;
}
double secondDerivative(double x) {
	//12x^2 + 30x + 6
	return 12 * x * pow(x, 2) + 30 * x + 6;
}
double fourthDerivative(double x) {
	//24;
	return 24;
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
struct IntergationResult {
	string name;
	double result;
	double absError;
	double calcError;
};
void printRow(int n, IntergationResult resutlst) {
	cout << setw(10) << left << resutlst.name <<
		setw(5) << right << n << setprecision(10) << fixed <<
		setw(15) << resutlst.result <<
		setw(15) << resutlst.absError <<
		setw(15) << resutlst.calcError << endl;
}
double getMax(double a, double b, int n, const function<double(double)>& f) {
	const double width = (b - a) / n;
	double max = -DBL_MAX;
	for (int step = 0; step < n; step++) {
		const double x = a + step * width;
		double tmp = f(x);
		if (tmp > max) {
			max = tmp;
		}
	}
	return max;
}
double getCalculatedErrorTrapezoid(double a, double b, int n) {
  double max = getMax(a, b, n, secondDerivative);
  double error = max * pow((b - a), 3) / (12 * pow(n, 2));
  return fabs(error);
}
double getCalculatedErrorSimpson(double a, double b, int n) {
	double max = getMax(a, b, n, fourthDerivative);
	double error = (max * pow((b - a), 5)) / (2480 * pow(n, 4));
	return fabs(error);
}
int main()
{
	const double PRESICE_VALUE = 24.4;
	const double a = 0.0;
	const double b = 2.0;
	cout << setw(10) << left << "Method" << right <<
		setw(5) << "n" <<
		setw(15) << "result" << 
		setw(15) << "abs error" << 
		setw(15) << "calc error" << endl;
	cout << "------------------------------------------------------------" << endl;
	for (int i = 2; i <= 50; i += 2) {
		const int n = i;
		double resultTrapezoid = trapezoidMethod(a, b, n, fx);
		double absErrorTrapezoid = fabs(PRESICE_VALUE - resultTrapezoid);
		double simpsonResult = simpsonMethod(a, b, n, fx);
		double absErrorsimson = fabs(PRESICE_VALUE - simpsonResult);
		double calErrorTrapezoid = getCalculatedErrorTrapezoid(a, b, n);
		double calcErrorSimpson = getCalculatedErrorSimpson(a, b, n);
		printRow(n, { "Trapezoid",resultTrapezoid ,absErrorTrapezoid , calErrorTrapezoid });
		printRow(n, { "Simpson",simpsonResult ,absErrorsimson , calcErrorSimpson });
		cout << "------------------------------------------------------------" << endl;
	}
}
