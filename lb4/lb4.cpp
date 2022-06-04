#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;
const int SIZE = 10;
//5 y = (x - 1)^2 –e^-x  [1.0, 1.5]

double fx(double x) 
{
    return pow(x - 1.0, 2) - pow(M_E, -x);
}
double pi(double xi[], double x, int i) 
{
    //numerator
    double difference[SIZE+1];
    for (int k = 0; k <= SIZE; k++) 
    {
        if (k != i) 
        {
            difference[k] = x - xi[k];
        }
        else 
        {
            difference[k] = 1;
        }
     }
    double numerator = 1.0;
    for (int k = 0; k <= SIZE; k++)
    {
        numerator = numerator * difference[k];
    }
    //denominator
    for (int k = 0; k <= SIZE; k++)
    {
        if (k != i) 
        {
            difference[k] = xi[i] - xi[k];
        }
        else 
        {
            difference[k] = 1;
        }
    }
    double denominator = 1.0;
    for (int k = 0; k <= SIZE; k++)
    {
        denominator = denominator * difference[k];
    }
    return (double)(numerator / denominator);
}
double lagrange(double x, double xi[], double yi[])
{
    double ln = 0.0;
    for (int i=0; i<=SIZE; i++)
    {
        ln = ln + pi(xi, x, i) * yi[i];
    }
    return ln;
}
void printValues(double x, double y) 
{
    cout << "x = " << setw(6) << setprecision(5) << x << ", y = " << setw(16) << setprecision(16) << y << endl;
}
double fact(int n) 
{
    double f = 1.0;
    for (int i = 2; i <= n; i++) 
    {
        f *= i;
    }
    return f;
}
double u_cal(double u, int n) 
{
    double temp = u;
    for (int i = 1; i < n; i++) 
    {
        temp *= (u - i);
    }
    return temp;
}
void populateDeltaY(double delta[SIZE + 1][SIZE + 1], double yi[SIZE+1])
{
    for (int i = 0; i <= SIZE; i++)
    {
        delta[i][0] = yi[i];
    }


    for (int i = 1; i <= SIZE; i++)
    {
        for (int j = 0; j <= SIZE - i; j++)
        {
            delta[j][i] = delta[j + 1][i - 1] - delta[j][i - 1];
        }
    }
}
double newton(double x, double xi[], double yi[])
{
    double delta[SIZE + 1][SIZE + 1];
    populateDeltaY(delta, yi);

    double sum = delta[0][0];
    double u = (x - xi[0]) / (xi[1] - xi[0]);
    for (int i = 1; i <= SIZE; i++)
    {
        sum += (u_cal(u, i) * delta[0][i]) / fact(i);
    }
    return sum;
}
void calcAndPrintPrecise(double a, double h, double xi[], double yi[]) 
{
    for (int i = 0; i <= SIZE; i++)
    {
        double x = a + (double)i * h;
        xi[i] = x;
        double y = fx(xi[i]);
        yi[i] = y;
        printValues(x, y);
    }
}
void calcAndPrintLangrange(double a, double h, double xi[], double yi[]) 
{
    for (int i = 0; i <= SIZE; i++)
    {
        double x = a + (double)i * h;
        xi[i] = x;
        double y = lagrange(xi[i], xi, yi);
        yi[i] = y;
        printValues(x, y);
    }
}
void calcAndPrintNewton(double a, double h, double xi[], double yi[])
{
    for (int i = 0; i <= SIZE; i++)
    {
        double x = a + (double)i * h;
        xi[i] = x;
        double y = newton(xi[i], xi, yi);
        yi[i] = y;
        printValues(x, y);
    }
}
int main()
{
    //xi = a + i * h; i = 0, 1, 2, …, 10; h = (b - a) / 10.
    const double a = 1.0;
    const double b = 1.5;
    const double h = (b - a) / 10.0;
    double xi[SIZE + 1];
    double yi[SIZE + 1];

    cout << "--------------------------------------------------------" << endl;
    cout << "Direct funsction calculations" << endl;
    calcAndPrintPrecise(a, h, xi, yi);

    double x1ForInterpollation = xi[4] + 0.021;  //(õ4 + 0,021)
    double x2ForInterpollation = xi[7] - 0.0146; //(õ7 - 0,0146)

    cout << "--------------------------------------------------------" << endl;
    cout << "Precise values:" << endl;
    cout << setw(15) << "(x4 + 0,021) ";
    printValues(x1ForInterpollation, fx(x1ForInterpollation));
    cout << setw(15) << "(x7 - 0,0146) ";
    printValues(x2ForInterpollation, fx(x2ForInterpollation));
    cout << "--------------------------------------------------------" << endl;
    cout << "Lagrange :" << endl;
    calcAndPrintLangrange(a, h, xi, yi);
    cout << endl;
    cout << setw(15) << "(x4 + 0,021) ";
    printValues(x1ForInterpollation, lagrange(x1ForInterpollation, xi, yi));
    cout << setw(15) << "(x7 - 0,0146) ";
    printValues(x2ForInterpollation, lagrange(x2ForInterpollation, xi, yi));
    cout << "--------------------------------------------------------" << endl;
    cout << "Newton :" << endl;
    calcAndPrintNewton(a, h, xi, yi );
    cout << endl;
    cout << setw(15) << "(x4 + 0,021) ";
    printValues(x1ForInterpollation, newton(x1ForInterpollation, xi, yi));
    cout << setw(15) << "(x7 - 0,0146) ";
    printValues(x2ForInterpollation, newton(x2ForInterpollation, xi, yi));
    cout << "--------------------------------------------------------" << endl;

 }