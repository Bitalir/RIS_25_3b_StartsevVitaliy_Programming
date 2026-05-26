#include <iostream>
#include <clocale>
#include <string>
using namespace std;

int boyerMooreSearch(const string& text, const string& pattern) {
    int textLen = text.length(); // Длины строк
    int patternLen = pattern.length();

    if (textLen == 0 || patternLen == 0)
        return -1; // Если одна из строк пустая

    if (patternLen > textLen)
        return -1; // Если образец длиннее текста

    int CharTable[256];
    // Инициализируем таблицу: по умолчанию сдвиг на длину образца
    for (int i = 0; i < 256; i++)
        CharTable[i] = patternLen;
    // Заполняем таблицу для символов, встречающихся в образце
    // Для каждого символа запоминаем расстояние от его позиции до конца образца
    // (кроме последнего символа)
    for (int i = 0; i < patternLen - 1; i++)
        CharTable[(unsigned char)pattern[i]] = patternLen - 1 - i;

    int pos = patternLen - 1;

    while (pos < textLen) {
        int i = patternLen - 1; // Начинаем сравнение с последнего символа образца
        // Сравниваем символы справа налево
        while (i >= 0 && pattern[i] == text[pos - (patternLen - 1 - i)])
            i--;
        // Если дошли до начала образца – нашли совпадение
        if (i == -1) {
            return pos - patternLen + 1; // Возвращаем индекс начала совпадения
        }

        // Иначе – сдвигаемся по таблице "плохих" символов
        // Используем символ текста, на котором произошло несовпадение
        pos += CharTable[(unsigned char)text[pos - (patternLen - 1 - i)]];
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
    int pos = boyerMooreSearch(text, pattern);
    if (pos != -1) {
        cout << "Позиция(индекс) начала подстроки: " << pos << endl;
    }
    else {
        cout << "Подстрока не найдена";
    }
    return 0;
}