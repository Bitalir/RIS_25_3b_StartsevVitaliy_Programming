#include <iostream>
#include <clocale>
using namespace std;

void quick_sort(int* mas, int size) {
	int mid = mas[size-1];
	int i = 0;
	int j = size - 1;
	while (i <= j) {
		while (mas[i] < mid) i++;
		while (mas[j] > mid) j--;
		if (i <= j) {
			int temp = mas[i];
			mas[i] = mas[j];
			mas[j] = temp;
			i++;
			j--;

		}
	}
	if (j > 0) quick_sort(mas, j + 1);
	if (i < size) quick_sort(mas + i, size - i);
}

int main() {
	setlocale(LC_ALL, "Rus");
	int n;
	cout << "Размер массива: ";
	cin >> n;
	int* arr = new int[n];
	for (int i = 0; i < n; i++) {
		cout << i + 1 << " элемент: ";
		cin >> arr[i];
	}
	quick_sort(arr, n);
	cout << "Упорядоченный массив: ";
	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";
	delete[] arr;
	return 0;
}