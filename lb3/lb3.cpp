#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>
#include <string>
using namespace std;

struct Element
{
    int index = -1;
    double coefficient = nan("");
    double x = nan("");
    Element() 
    {
        int index = -1;
        double coefficient = nan("");
        double x = nan("");
    }
    Element(int index, double coefficient) 
    {
        this->index = index;
        this->coefficient = coefficient;
    }
    Element(double coefficient)
    {//this is free member
         this->coefficient = coefficient;
         this->x = 1.0;
    }
};
void printMatrix(Element** matrix, int rows, int columns)
{
    for (int i = 0; i < rows; i++) 
    {
        for (int k = 0; k < columns; k++) 
        {
            cout << setw(8) << left << setprecision(3) << matrix[i][k].coefficient;
        }
        cout << endl;
    }
}

struct MainElement {
    int p = 0;
    int q = 0;
    int size = 0;
    double value = 0;
    Element* row = nullptr;
};
MainElement findMainElement(Element** matrix, int rows, int columns)
{
    double max = -DBL_MAX;
    MainElement mainElement;
    for (int i = 0; i < rows; i++)
    {
        for (int k = 0; k < columns-1; k++)
        {
            if (fabs(matrix[i][k].coefficient) > max)
            {
                max = fabs(matrix[i][k].coefficient);
                mainElement.p = i;
                mainElement.q = k;
                mainElement.value = matrix[i][k].coefficient;
                mainElement.row = matrix[i];
            }
        }
    }
    mainElement.size = columns;
    return mainElement;
}
double* calculateM(Element** a, int rows, int columns, MainElement main)
{
    double* m = new double[rows];
    for (int i = 0; i < rows; i++) 
    {
        if (i != main.p)
        {
            m[i] = -1 * a[i][main.q].coefficient / main.value;
        }
    }
    return m;
}
Element** createMatrix(int rows, int columns)
{
    Element** matrix;
    matrix = new Element * [rows];
    for (int i = 0; i < columns; i++)
    {
        matrix[i] = new Element[columns];
    }
    return matrix;
}
Element** decreaseMatrix(Element** a, int rows, int columns, MainElement main)
{
    Element** result = createMatrix(rows - 1, columns - 1);
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
Element** multiplyM(Element** a, int rows, int columns, MainElement main, double* m)
{
    Element** interimResult = createMatrix(rows, columns);
    for (int i = 0; i < rows; i++)
    {
        if (i != main.p)
        {
            for (int j = 0; j < columns; j++)
            {
                interimResult[i][j].coefficient = a[i][j].coefficient + a[main.p][j].coefficient * m[i];
                interimResult[i][j].index = a[i][j].index;
                interimResult[i][j].x = a[i][j].x;
            }
        }
    }
    Element** result = decreaseMatrix(interimResult, rows, columns, main);
    delete[] * interimResult;
    return result;
}
void calculateRoot(MainElement & elem)
{
    double sum = 0;
    //getting summ of all known members
    for (int i = 0; i < elem.size - 1; i++) 
    {
        if (!isnan(elem.row[i].x))
        {
            sum = sum + elem.row[i].x * elem.row[i].coefficient;
        }
    }
    //find first coefficient with unknown x
    Element toFind;
    int resultIndex = -1;
    for (int i = 0; i < elem.size - 1; i++) 
    {
        if (isnan(elem.row[i].x)) 
        {
            toFind = elem.row[i];
            resultIndex = i;
            break;
        }
    }
    double freeMember = elem.row[elem.size - 1].coefficient;
    double res = (freeMember - sum) / toFind.coefficient;
    elem.row[resultIndex].x = res;
}
void printMainElement(MainElement elem)
{
    cout << "main element" << endl;
    for (int i = 0; i < elem.size; i++) 
    {
        cout << setw(8) << setprecision(3) <<elem.row[i].coefficient;
    }
    cout << endl;
}
vector<MainElement> getAllMainElements(Element** matrix, int rows, int cols)
{
    vector<MainElement> mainElements;
    Element** matr = matrix;
    int currentRow = rows;
    int currentColumn = cols;
    while (currentRow > 0)
    {
        MainElement mainElement = findMainElement(matr, currentRow, currentColumn);
        printMainElement(mainElement);
        mainElements.push_back(mainElement);
        cout << endl;
        double* m = calculateM(matr, rows, cols, mainElement);
        Element** newMatrix = multiplyM(matr, rows, cols, mainElement, m);
        currentRow--;
        currentColumn--;
        printMatrix(newMatrix, currentRow, currentColumn);
        matr = newMatrix;
    }
    return mainElements;
}
void populateResolved(MainElement & toPopulate, Element root) 
{
    Element* singleRow = toPopulate.row;
    for (int i = 0; i < toPopulate.size; i++)
    {
        if (root.index == singleRow[i].index) 
        {
            singleRow[i].x = root.x;
            break;
        }
    }
}
void populateResolved(vector<MainElement> allmainElements, MainElement resolved) 
{
    for (MainElement toPopulate : allmainElements)
    {
        Element* results = resolved.row;
        for (int i = 0; i < resolved.size; i++)
        {
            if (!isnan(results[i].x))
            {
                populateResolved(toPopulate, results[i]);
            }
        }
    }
}
int main()
{
    const int ROWS = 3;
    const int COLUMNS = 4;
    Element** initialMatrix;

    initialMatrix = new Element * [ROWS];
    initialMatrix[0] = new Element[COLUMNS] { Element(0,6), Element(1,10), Element(2,12), Element(50), };
    initialMatrix[1] = new Element[COLUMNS] { Element(0,0), Element(1,4),  Element(0,8),  Element(24) };
    initialMatrix[2] = new Element[COLUMNS] { Element(0,2), Element(1,1),  Element(0,1),  Element(6) };

    printMatrix(initialMatrix, ROWS, COLUMNS);

    vector<MainElement> mainElements = getAllMainElements(initialMatrix, ROWS, COLUMNS);
 
    for (int i = mainElements.size() - 1; i >= 0; i--)
    {
        MainElement toResolve = mainElements.at(i);
        calculateRoot(toResolve);
        populateResolved(mainElements, toResolve);
    }
    //top first  main element contains all roots
    Element *result = mainElements.at(0).row;
    for (unsigned int i = 0; i < mainElements.size(); i++)
    {
       cout << "x" + to_string(result[i].index) + " = " << setw(3) << result[i].x << endl;
    }
}