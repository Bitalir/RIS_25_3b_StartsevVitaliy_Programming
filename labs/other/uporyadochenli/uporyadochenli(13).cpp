#include <iostream>
#include <clocale>
using namespace std;
bool f = true;
int A[100];
int n, i, j;

int main() {
	setlocale(LC_ALL, "RU");
	cout << "Введите размер массива: ";
	cin >> n;
	for (i = 0; i < n; i++) {
		cin >> A[i];
	}
	cout << "Введённый массив: ";
	for (i = 0; i < n; i++) {
		cout << A[i];
	}
	cout << endl;
	for (i = 0; i < n - 1 && f; i++) {
		if (A[i] <= A[i + 1]) {
			f = true;
		}
		else {
			f = false;
		}
	}

	if (f) {
		cout << "Массив упорядочен по возрастанию";
	}
	else {
		cout << "Массив не упорядочен";
	}
	return 0;
}