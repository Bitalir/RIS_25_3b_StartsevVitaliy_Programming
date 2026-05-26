#include <iostream>
#include <clocale>
#include <string>
#include <algorithm> // для max
using namespace std;

int CharTable[256]; // Сохраняем имя переменной из вашего кода

void prepare_shift(const string& pattern) {
    int patternLen = pattern.length();
    // Инициализируем таблицу: по умолчанию сдвиг на длину образца
    for (int i = 0; i < 256; i++) {
        CharTable[i] = patternLen;
    }
    // Заполняем таблицу для символов, встречающихся в образце
    for (int i = 0; i < patternLen - 1; i++) {
        CharTable[(unsigned char)pattern[i]] = patternLen - 1 - i;
    }
}

int boyerMooreSearch(const string& text, const string& pattern) {
    int textLen = text.length(); // Длины строк
    int patternLen = pattern.length();
    if (textLen == 0 || patternLen == 0)
        return -1; // Если одна из строк пустая
    if (patternLen > textLen)
        return -1; // Если образец длиннее текста
    // Подготавливаем таблицу сдвигов
    prepare_shift(pattern);
    int pos = 0; // Начальная позиция (в Хорспуле начинаем с 0)
    while (pos <= textLen - patternLen) {
        int i = patternLen - 1; // Начинаем сравнение с последнего символа образца
        // Сравниваем символы справа налево
        while (i >= 0 && pattern[i] == text[pos + i]) {
            i--;
        }
        // Если дошли до начала образца — нашли совпадение
        if (i == -1) {
            return pos; // Возвращаем индекс начала совпадения
        }
        // Сдвигаемся по таблице "плохих" символов,
        // используя последний символ текущего окна текста
        pos += CharTable[(unsigned char)text[pos + patternLen - 1]];
    }
    // Если ничего не нашли
    return -1;
}

    int main() {
        setlocale(LC_ALL, "RU");
        string text;
        string pattern;
        cout << "Введите строку: ";
        cin >> text;
        cout << "Введите искомую подстроку: ";
        cin >> pattern;
        int n = text.length();
        int m = pattern.length();
        prepare_shift(pattern); // Заполняем таблицу сдвигов для заданного образца
        int pos = boyerMooreSearch(text, pattern);
        if (pos != -1) {
            cout << "Позиция(индекс) начала подстроки: " << pos << endl;
        }
        else {
            cout << "Подстрока не найдена";
        }
        return 0;
    }