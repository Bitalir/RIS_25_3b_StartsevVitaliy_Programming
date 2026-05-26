#include <iostream>
#include <string>
using namespace std;

bool isDigit(char ch) {
    return ch >= '0' && ch <= '9';
}

void sortDigitsDesc(string& digits) {
    size_t n = digits.length();
    for (size_t i = 0; i < n - 1; ++i) {
        for (size_t j = 0; j < n - i - 1; ++j) {
            if (digits[j] < digits[j + 1]) {
                char temp = digits[j];
                digits[j] = digits[j + 1];
                digits[j + 1] = temp;
            }
        }
    }
}

string processWord(const string& word) {
    string digits;
    for (char ch : word) {
        if (isDigit(ch)) {
            digits += ch;
        }
    }
    if (digits.empty()) {
        return word;
    }
    sortDigitsDesc(digits);
    string result;
    size_t digitIndex = 0;
    for (char ch : word) {
        if (isDigit(ch)) {
            result += digits[digitIndex++];
        }
        else {
            result += ch;
        }
    }
    return result;
}

int main() {
    string input;
    getline(cin, input);
    string output;
    string currentWord;
    for (char ch : input) {
        if (ch == ' ') {
            if (!currentWord.empty()) {
                output += processWord(currentWord);
                currentWord.clear();
            }
            output += ch;
        }
        else {
            currentWord += ch;
        }
    }
    if (!currentWord.empty()) {
        output += processWord(currentWord);
    }
    cout << output << endl;
    return 0;
}