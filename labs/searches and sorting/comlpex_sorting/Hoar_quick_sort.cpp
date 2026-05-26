#include <iostream>
#include <clocale>
#include <algorithm>
using namespace std;

int Hoare(int arr[], int low, int high) {
	int pivot = arr[low + (high - low) / 2];
	int i = low - 1;
	int j = high + 1;
	while (true) {
		do { i++; } while (arr[i] < pivot);
		do { j--; } while (arr[j] > pivot);
		if (i >= j) return j;
		swap(arr[i], arr[j]);
	}
}

void quickHoare(int arr[], int low, int high) {
	if (low < high) {
		int pI = Hoare(arr, low, high);
		quickHoare(arr, low, pI);
		quickHoare(arr, pI+1, high);
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
	
	quickHoare(arr, 0, n - 1); // Теперь сортируем полностью!

	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";
	cout << endl;

	delete[] arr;
	return 0;
}