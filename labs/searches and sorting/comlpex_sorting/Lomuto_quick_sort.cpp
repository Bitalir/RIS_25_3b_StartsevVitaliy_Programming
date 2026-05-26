#include <iostream>
#include <clocale>
#include <algorithm>
using namespace std;

int Lomuto(int arr[], int low, int high) {
	int pI = high;
	int pivot = arr[pI];
	for (int j = low; j < pI; j++) {
		if (arr[j] > pivot) {
			swap(arr[pI - 1], arr[j]);
			swap(arr[pI], arr[pI - 1]);
			pI--;
			j--;
		}
	}
	return pI;
}

void QuickSort(int arr[], int low, int high) {
    if (low < high) {
        int pivotIndex = Lomuto(arr, low, high);
        QuickSort(arr, low, pivotIndex - 1); // Рекурсия для левой части
        QuickSort(arr, pivotIndex + 1, high); // Рекурсия для правой части
    }
}

int main() {
    setlocale(LC_ALL, "RU");
    int n;
    cout << "Введите размер массива: ";
    cin >> n;
    cout << "Введите элементы массива: ";
    int* arr = new int[n];
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    QuickSort(arr, 0, n - 1); // Теперь сортируем полностью!

    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;

    delete[] arr;
    return 0;
}