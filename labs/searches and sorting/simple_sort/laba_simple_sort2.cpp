#include <iostream>
#include <clocale>
using namespace std;

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
	int minVal = arr[0], maxVal = arr[0];
	for (int i = 1; i < n; i++) {
		if (arr[i] < minVal) minVal = arr[i];
		if (arr[i] > maxVal) maxVal = arr[i];
	}
	int size = maxVal - minVal + 1;
	int* count = new int[size]();
	for (int i = 0; i < n; i++) {
		count[arr[i] - minVal]++;
	}
	int index = 0;
	for (int i = 0; i < size; i++) {
		while (count[i] > 0) {
			arr[index] = i + minVal;
			index++;
			count[i]--;
		}
	}
	cout << "Упорядоченный массив: ";
	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";
	delete[] arr;
	delete[] count;
	return 0;
}