#include <iostream>
#include <cstdarg>
#include <string>
using namespace std;

string binaryToTernary(const char* binStr) {
    unsigned long long value = 0;
    for (const char* p = binStr; *p; ++p) {
        if (*p != '0' && *p != '1') {
            return "ERROR: invalid binary digit";
        }
        value = value * 2 + (*p - '0');
    }
    if (value == 0) return "0";
    string ternary;
    while (value > 0) {
        ternary = char('0' + (value % 3)) + ternary;
        value /= 3;
    }
    return ternary;
}

void convertFromBinaryToTernary(int count, ...) {
    va_list args;
    va_start(args, count);

    for (int i = 0; i < count; ++i) {
        const char* binary = va_arg(args, const char*);
        string ternary = binaryToTernary(binary);
        cout << binary << " (binary) = " << ternary << " (ternary)" << endl;
    }

    va_end(args);
}

int main() {
    cout << "Call with 3 arguments:\n";
    convertFromBinaryToTernary(3, "1010", "111", "1");

    cout << "\nCall with 6 arguments:\n";
    convertFromBinaryToTernary(6, "0", "10", "1101", "1000", "10101", "11111");

    cout << "\nCall with 7 arguments:\n";
    convertFromBinaryToTernary(7, "1001", "1100", "101", "11", "100", "10000", "111000");

    return 0;
}