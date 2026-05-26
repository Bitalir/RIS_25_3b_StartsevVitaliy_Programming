#include <iostream>
#include <clocale>
using namespace std;

int KMP_search(string str, string templ) {
    int strlen = str.length();
    int templlen = templ.length();

    // 1. Вычисление префикс-функции (массив d)
    int* d = new int[templlen];
    int i = 0, j = -1;
    d[0] = -1;

    while (i < templlen - 1) {
        while (j >= 0 && templ[j] != templ[i]) {
            j = d[j];
        }
        ++i;
        ++j;
        if (templ[i] == templ[j]) {
            d[i] = d[j];
        }
        else {
            d[i] = j;
        }
    }

    // 2. Поиск строки с использованием массива d
    i = 0;
    j = 0;
    for (i = 0, j = 0; (i < strlen) && (j < templlen); ++i) {
        while (j >= 0 && templ[j] != str[i]) {
            j = d[j];
        }
        ++j;
    }

    // 3. Проверка результата и освобождение памяти
    int result = (j == templlen) ? (i - j) : -1;
    delete[] d;
    return result;
}

int main() {
    setlocale(LC_ALL, "RU");
    string text;
    string pattern;
    cout << "Введите строку: ";
    cin >> text;
    cout << "Введите искомую подстроку: ";
    cin >> pattern;
    int pos = KMP_search(text, pattern);
    if (pos != -1) {
        cout << "Позиция(индекс) начала подстроки: " << pos << endl;
    }
    else {
        cout << "Подстрока не найдена";
    }
    return 0;
}