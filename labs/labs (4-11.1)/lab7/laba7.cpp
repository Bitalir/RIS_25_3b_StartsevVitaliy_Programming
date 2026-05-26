#include <iostream>
#include <clocale>
using namespace std;
int a = 10;
double b = 20.5;
float c = 30.0;

double nat_log(int x) {
	return log(x);
}

double nat_log(double x) {
	return log(x);
}

float nat_log(float x) {
	return logf(x);
}

double dec_log(int x) {
	return log10(x);
}

double dec_log(double x) {
	return log10(x);
}

float dec_log(float x) {
	return log10f(x);
}

int main() {
	setlocale(LC_ALL, "RU");
	cout << "Натуральный логарифм:\n";
	cout << "ln(" << a << ") = " << nat_log(a) << '\n';
	cout << "ln(" << b << ") = " << nat_log(b) << '\n';
	cout << "ln(" << c << ") = " << nat_log(c) << '\n';
	cout << "\nДесятичный логарифм:\n";
	cout << "log10(" << a << ") = " << dec_log(a) << '\n';
	cout << "log10(" << b << ") = " << dec_log(b) << '\n';
	cout << "log10(" << c << ") = " << dec_log(c) << '\n';
	return 0;
}