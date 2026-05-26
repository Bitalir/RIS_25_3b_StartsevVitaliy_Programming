#include <iostream>
#include <clocale>
#include <string>
using namespace std;

void lin(int* mas, int n, int z)
{
	int x = 0;
	int count = 0;
	int i1 = 0;
	for (int i = 0; i < n; i++) {
		if (mas[i] == z) {
			x = z;
			count += 1;
			i1 = i;
		}
	}
	if (x == z) {
		cout << "Линейный: Искомое число - " << z << " есть в последовательности. " << "Его количество: " << count << " Его номер: " << i1 + 1 << endl;
	}
	else {
		cout << "Линейный: Искомого числа нет" << endl;
	}
}

void bin(int* mas, int n, int z) {
	int low = 0;
	int high = n - 1;
	int mid;
	while (low <= high) {
		mid = (low + high) / 2;
		if (z < mas[mid]) {
			high = mid - 1;
		}
		else if (z > mas[mid]) {
			low = mid + 1;
		}
		else {
			cout << "Бинарный: Искомое число " << z << " есть в последовательности" << endl;
			return;
		}
	}
	cout << "Бинарный: Искомого числа " << z << " нет в последовательности" << endl;
}


void inter(int* mas, int n, int z) {
	int mid;
	int low = 0;
	int high = n - 1;
	while (low <= high && z >= mas[low] && z <= mas[high]) {
		if (low == high) {
			if (mas[low] == z) {
				cout << "Искомое число " << z << " найдено на позиции " << low << endl;
			}
			else {
				cout << "Искомого числа " << z << " нет в последовательности" << endl;
			}
			return;
		}

		int pos = low + static_cast<int>(
			((static_cast<double>(z - mas[low]) * (high - low)) /
				(mas[high] - mas[low]))
			);

		if (pos < low || pos > high) {
			break;
		}

		if (mas[pos] == z) {
			cout << "Интерполяционный: Искомое число " << z << " найдено на позиции " << pos+1 << endl;
			return;
		}

		if (mas[pos] < z) {
			low = pos + 1;
		}
		else {
			high = pos - 1;
		}
	}

	cout << "Интерполяционный: Искомого числа " << z << " нет в последовательности" << endl;
}

void strok(string& text, string& pattern) {
	int textLen = text.length();
	int patternLen = pattern.length();
	if (patternLen == 0) {
		cout << "Построка пуста";
		return;
	}
	bool f = false;
	for (int i = 0; i <= textLen - patternLen; ++i) {
		bool match = true;
		for (int j = 0; j < patternLen; ++j) {
			if (text[i + j] != pattern[j]) {
				match = false;
				break;
			}
		}
		if (match) {
			cout << "Подстрока найдена на позиции " << i+1 << endl;
			f = true;
		}
	}

	if (!f) {
		cout << "Подстрока не найдена" << endl;
	}
}

int main() {
	setlocale(LC_ALL, "RU");
	string text, pattern;
	cout << "Введите строку: ";
	cin >> text;
	cout << "Введите искомую подстроку: ";
	cin >> pattern;
	strok(text, pattern);
	int n;
	int z;
	int* mas = new int[n];
	cout << "Введите размер массива: ";
	cin >> n;
	cout << "Введите искомое число: ";
	cin >> z;
	cout << "Введите элементы массива: ";
	for (int i = 0; i < n; i++) {
		cin >> mas[i];
	}
	lin(mas, n, z);
	bin(mas, n, z);
	inter(mas, n, z);
	delete[] mas;
	return 0;
}