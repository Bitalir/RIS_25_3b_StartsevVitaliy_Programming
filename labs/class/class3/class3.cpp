#include <clocale>
#include <iostream>
using namespace std;

class Pair {
private:
	int first;
	double second;
public:
	Pair() {
		this->first = 0;
		this->second = 0;
	}
	Pair(const int& f, const double& s) {
		this->first = f;
		this->second = s;
	}
	Pair operator-(const int& constVal) const {
		return Pair(this->first - constVal, this->second);
	}
	Pair operator-(const double& constVal) const {
		return Pair(this->first, this->second - constVal);
	}
	bool operator==(const Pair& other) const {
		return (this->first == other.first) && (this->second == other.second);
	}
	bool operator!=(const Pair& other) const {
		return !(*this == other);
	}
	void print() const {
		cout << first << ":" << second << endl;
	}
	int getFirst() const { return first; }
	double getSecond() const { return second; }
	void setFirst(int f) { first = f; }
	void setSecond(double s) { second = s; }
};

int main(){
	setlocale(LC_ALL, "RU");
	Pair p1(5, 3.14);
	Pair p2(5, 3.14);
	Pair p3(10, 2.71);

	cout << "Пара p1: ";
	p1.print();

	cout << "Пара p2: ";
	p2.print();

	cout << "Пара p3: ";
	p3.print();

	if (p1 == p2) {
		cout << "p1 == p2" << endl;
	}
	else {
		cout << "p1 != p2" << endl;
	}

	if (p1 != p3) {
		cout << "p1 != p3" << endl;
	}
	else {
		cout << "p1 == p3" << endl;
	}
	Pair result1 = p1 - 2;
	cout << "p1 - 2 = ";
	result1.print();
	Pair result2 = p1 - 1.14;
	cout << "p1 - 1.14 = ";
	result2.print();
	return 0;
}
