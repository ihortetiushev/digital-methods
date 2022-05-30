#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>
#include <string>
using namespace std;

void printMatrix(double** matrix, int rows, int columns)
{
    for (int i = 0; i < rows; i++) 
    {
        for (int k = 0; k < columns; k++) 
        {
            cout << setw(10) << left << matrix[i][k];
        }
        cout << endl;
    }
}
struct MainElement {
    int p=0;
    int q=0;
    int size = 0;
    double value=0;
    double* row;
};
MainElement findMainElement(double** matrix, int rows, int columns)
{
    double max = -DBL_MAX;
    MainElement mainElement;
    for (int i = 0; i < rows; i++)
    {
        for (int k = 0; k < columns-1; k++)
        {
            if (fabs(matrix[i][k]) > max)
            {
                max = fabs(matrix[i][k]);
                mainElement.p = i;
                mainElement.q = k;
                mainElement.value = matrix[i][k];
                mainElement.row = matrix[i];
            }
        }
    }
    mainElement.size = columns;
    return mainElement;
}
double* calculateM(double** a, int rows, int columns, MainElement main)
{
    double* m = new double[rows];
    for (int i = 0; i < rows; i++) 
    {
        if (i != main.p)
        {
            m[i] = -1 * a[i][main.q] / main.value;
        }
    }
    return m;
}
double** createMatrix(int rows, int columns)
{
    double** matrix;
    matrix = new double* [rows];
    for (int i = 0; i < columns; i++)
    {
        matrix[i] = new double[columns];
    }
    return matrix;
}
double** decreaseMatrix(double** a, int rows, int columns, MainElement main)
{
    double** result = createMatrix(rows - 1, columns - 1);
    int newRow = 0;
    for (int i = 0; i < rows; i++)
    {
        if (i != main.p)
        {
            int newCol = 0;
            for (int j = 0; j < columns; j++)
            {
                if (j != main.q)
                {
                    result[newRow][newCol] = a[i][j];
                    newCol++;
                }
            }
            newRow++;
        }
    }
    return result;
}
double** multiplyM(double** a, int rows, int columns, MainElement main, double* m)
{
    double** interimResult = createMatrix(rows, columns);
    for (int i = 0; i < rows; i++)
    {
        if (i != main.p)
        {
            for (int j = 0; j < columns; j++)
            {
                interimResult[i][j] = a[i][j] + a[main.p][j] * m[i];
            }
        }
    }
    double** result = decreaseMatrix(interimResult, rows, columns, main);
    delete[] * interimResult;
    return result;
}
double calculateRoot(MainElement elem, double results[], int resultIndex, int toFindIndex) 
{
    double sum = 0;
    for (int i = 0; i < elem.size - 1; i++) 
    {
        if (!isnan(results[i])) 
        {
            sum = sum + elem.row[i] * results[i];
        }
    }
    double res = (elem.row[elem.size - 1] - sum) / elem.row[toFindIndex];
    results[resultIndex] = res;
    return res;
}
void printMainElement(MainElement elem)
{
    cout << "main element" << endl;
    for (int i = 0; i < elem.size; i++) 
    {
        cout << setw(8) << elem.row[i];
    }
    cout << endl;
}
vector<MainElement> getAllMainElements(double** matrix, int rows, int cols)
{
    vector<MainElement> mainElements;
    double** matr = matrix;
    int currentRow = rows;
    int currentColumn = cols;
    while (currentRow > 0)
    {
        MainElement mainElement = findMainElement(matr, currentRow, currentColumn);
        printMainElement(mainElement);
        mainElements.push_back(mainElement);
        cout << endl;
        double* m = calculateM(matr, rows, cols, mainElement);
        double** newMatrix = multiplyM(matr, rows, cols, mainElement, m);
        currentRow--;
        currentColumn--;
        printMatrix(newMatrix, currentRow, currentColumn);
        matr = newMatrix;
    }
    return mainElements;
}
int *main()
{
    const int ROWS = 3;
    const int COLUMNS = 4;
    double** initialMatrix;

    initialMatrix = new double* [ROWS];
    initialMatrix[0] = new double[COLUMNS] { 6, 10, 12, 50 };
    initialMatrix[1] = new double[COLUMNS] { 0, 4,  8,  24 };
    initialMatrix[2] = new double[COLUMNS] { 2, 1,  1,  6 };

    printMatrix(initialMatrix, ROWS, COLUMNS);

    vector<MainElement> mainElements = getAllMainElements(initialMatrix, ROWS, COLUMNS);
 
    double result[ROWS] = {nan(""),nan(""), nan("")};

    double x1 = calculateRoot(mainElements.at(2), result, 1, 0);
    double x0 = calculateRoot(mainElements.at(1), result, 0, 0);
    double x2 = calculateRoot(mainElements.at(0), result, 2, 2);
    cout << "x0 = " << setw(3) << x0 << endl;
    cout << "x1 = " << setw(3) << x1 << endl;
    cout << "x2 = " << setw(3) << x2 << endl;
}