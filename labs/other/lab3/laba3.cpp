#include <iostream>
using namespace std;
float e = 2.718281828;

double f(double& x, int& n, int i, double a) {
	if (i == n) {
		return a;
	}
	return a + f(x, n, i + 1, a * ((2 * x) / (n + 1)));
}

double f1(double& x) {
	return pow(e, 2 * x);
}

int main() {
	int n = 20;
	double x;
	cin >> x;
	cout << "X = " << x << endl << f(x, n, 1, 2 * x) << endl << f1(x);
	return 0;
}