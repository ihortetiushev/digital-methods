#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

using namespace std;

double fx(double x, double y) {
	//(1-x^2)/xy
	return (1 - pow(x, 2)) / (x * y);
}
string numToStrFxied(double num) {
	ostringstream strStream;
	strStream << fixed << setprecision(3);
	strStream << num;
	return strStream.str();
}
double calcMethod3(double x, double y, double h) {
	//Модифікований метод Эйлера (варіант 2)
	double fxPrev = fx(x, y);
	y = y + (fxPrev + fx(x + h, y + h * fxPrev)) * h / 2;
	return y;
}
double calcMethod4(double x, double y, double h) {
	//Метод Рунге - Кутта третього порядку
	double k1 = fx(x, y);
	double k2 = fx(x + h / 2.0, y + h * k1 / 2.0);
	double k3 = fx(x + h / 2.0, y + h * k2 / 2.0);
	double k4 = fx(x + h, y + h * k3);
	y = y + (h / 6.0) * (k1 + k2 + k3 + k4);
	return y;
}
void calculate(double a, double b, double y0, double h) {
	double x = a;
	double yMethod1 = y0;
	double yMethod2 = y0;
	string xStr;
	const string END_STR = numToStrFxied(b + h);
	do
	{
		yMethod1 = calcMethod3(x, yMethod1, h);
		yMethod2 = calcMethod4(x, yMethod2, h);

		cout << "x = " << fixed << setprecision(3) << x <<
		"   y = " << fixed << setprecision(8) << yMethod1 <<
		"   y = " << setprecision(8) << yMethod2 << endl;

		x = x + h;

		xStr = numToStrFxied(x);//to avoid double presicion confution in <= operation
	} while (xStr != END_STR);
}
int main()
{
	const double a = 1.0;
	const double b = 2.0;
	double y0 = 4.0;// x0 = a = 1.0
	const double h = 0.001;
	cout << setw(9) << "x" << setw(17) << "Method 3" << setw(17) << "Method 4" << endl;
	calculate(a, b, y0, h);
}
