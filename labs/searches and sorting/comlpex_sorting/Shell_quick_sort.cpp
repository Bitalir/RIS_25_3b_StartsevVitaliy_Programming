#include <iostream>
#include <clocale>
#include <algorithm>
using namespace std;

void Shell(int arr[], int size) {
	for (int step = size / 2; step > 0; step /= 2) {
		for (int i = step; i < size; i++) {
			int temp = arr[i];
			int j;
			for (j = i; j >= step && arr[j - step] > temp; j -= step) {
				arr[j] = arr[j - step];
			}
			arr[j] = temp;
		}
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

	Shell(arr, n);
	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";
	cout << endl;
	delete[] arr;
	return 0;
}