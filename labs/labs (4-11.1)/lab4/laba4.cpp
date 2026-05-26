#include <iostream>
#include <clocale>
using namespace std;
int M[100];
int n, i, j;
int main() {
	setlocale(LC_ALL, "RU");
	cout << "Введите размер массива: ";
	cin >> n;
	cout << "Изначальный массив:    ";
	for (i = 0; i < n; i++) {
		M[i] = rand() % 100 - 50;
		cout << M[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < n / 2; i++) {
		int temp = M[i];
		M[i] = M[n - 1 - i];
		M[n - 1 - i] = temp;
	}
	if (n % 2 == 1) {
		for (i = n / 2; i < n - 1; i++) {
			M[i] = M[i + 1];
		}
		n--;
	}
	cout << "Перевёрнутый массив:   ";
	for (i = 0; i < n; i++) {
		cout << M[i] << " ";
	}
	cout << endl;
	int x = n + 3;
	for (j = 0; j < 3; j++) {
		for (i = x; i > 0; i--) {
			M[i] = M[i - 1];
		}
	}
	for (i = 0; i < 3; i++) {
		M[i] = M[i + 10] - 2;
	}
	cout << "Массив с новыми эл-ми: ";
	for (i = 0; i < x; i++) {
		cout << M[i] << " ";
	}
	return 0;
}