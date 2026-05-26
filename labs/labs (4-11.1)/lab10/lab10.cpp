#include <iostream>
#include <clocale>
#include <cstdlib>
#include <ctime>

using namespace std;

int** createMatrix(int rows, int cols) {
    int** matrix = new int* [rows];
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new int[cols];
    }
    return matrix;
}

void fillRandom(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = rand() % 100;
        }
    }
}

void printMatrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

void deleteMatrix(int** matrix, int rows) {
    for (int i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int main() {
    setlocale(LC_ALL, "RU");
    srand(time(nullptr));

    int rows, cols;
    cout << "Введите количество строк и столбцов матрицы: ";
    cin >> rows >> cols;

    if (rows < 2 || cols < 2) {
        cout << "Матрица должна иметь размер не менее 2x2 для удаления строки и столбца." << endl;
        return 1;
    }

    int** matrix = createMatrix(rows, cols);
    fillRandom(matrix, rows, cols);

    cout << "\nИсходная матрица:" << endl;
    printMatrix(matrix, rows, cols);

    int minVal = matrix[0][0];
    int minRow = 0, minCol = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (matrix[i][j] < minVal) {
                minVal = matrix[i][j];
                minRow = i;
                minCol = j;
            }
        }
    }
    cout << "\nМинимальный элемент: " << minVal << " (строка " << minRow + 1 << ", столбец " << minCol + 1 << ")" << endl;

    int newRows = rows - 1;
    int newCols = cols - 1;
    int** newMatrix = createMatrix(newRows, newCols);

    for (int i = 0, ni = 0; i < rows; ++i) {
        if (i == minRow) continue;
        for (int j = 0, nj = 0; j < cols; ++j) {
            if (j == minCol) continue;
            newMatrix[ni][nj] = matrix[i][j];
            ++nj;
        }
        ++ni;
    }

    cout << "\nМатрица после удаления строки " << minRow + 1 << " и столбца " << minCol + 1 << ":" << endl;
    printMatrix(newMatrix, newRows, newCols);

    deleteMatrix(matrix, rows);
    deleteMatrix(newMatrix, newRows);

    return 0;
}