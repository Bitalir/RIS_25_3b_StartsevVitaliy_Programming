#include <iostream>
#include <clocale>
using namespace std;

void inputMatrix(int** matrix, int n) {
    cout << "Введите элементы матрицы " << n << "x" << n << ":" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> matrix[i][j];
        }
    }
}

void printMatrix(int** matrix, int n) {
    cout << "Матрица:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

bool checkColumn(int** matrix, int n, int col) {
    int first = matrix[0][col];
    int mainDiag = matrix[col][col];
    int secondaryDiag = matrix[n - 1 - col][col];
    return (first > mainDiag && first > secondaryDiag);
}

long long productOfColumn(int** matrix, int n, int col) {
    long long product = 1;
    for (int i = 0; i < n; ++i) {
        product *= matrix[i][col];
    }
    return product;
}

int main() {
    setlocale(LC_ALL, "RU");
    int n;
    cout << "Введите размер квадратной матрицы n: ";
    cin >> n;

    int** matrix = new int* [n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = new int[n];
    }

    inputMatrix(matrix, n);
    printMatrix(matrix, n);

    bool found = false;
    long long totalProduct = 1;

    cout << "Столбцы, удовлетворяющие условию, и произведения их элементов:" << endl;
    for (int j = 0; j < n; ++j) {
        if (checkColumn(matrix, n, j)) {
            found = true;
            long long colProd = productOfColumn(matrix, n, j);
            cout << "Столбец " << j + 1 << ": произведение = " << colProd << endl;
            totalProduct *= colProd;
        }
    }

    if (!found) {
        cout << "Нет столбцов, удовлетворяющих условию." << endl;
    }
    else {
        cout << "Общее произведение всех элементов этих столбцов: " << totalProduct << endl;
    }

    for (int i = 0; i < n; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;

    return 0;
}