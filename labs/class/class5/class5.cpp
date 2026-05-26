#include <iostream>
#include <clocale>
#include <fstream>
#include <string>
using namespace std;

class Object {
public:
	Object() {}
	virtual ~Object() {}
	virtual void output() = 0;
};

class Person : public Object {
	friend istream& operator>>(istream& in, Person& p);
	friend ostream& operator<<(ostream& out, const Person& p);
protected:
	string name;
	int age;
public:
	~Person(){}
	Person() {
		name = "";
		age = 0;
	}
	Person(int nAge, string nName) {
		name = nName;
		age = nAge;
	}
	Person(const Person& p) {
		name = p.name;
		age = p.age;
	}
	string get_name() {
		return name;
	}
	int get_age() {
		return age;
	}
	void set_name(string nName) {
		name = nName;
	}
	void set_age(int nAge) {
		age = nAge;
	}
	Person& operator=(const Person& p) {
		age = p.age;
		name = p.name;
		return *this;
	}
	void output() override {
		cout << "\nName: " << name;
		cout << "\nAge: " << age << endl;
	}
};

class Teacher : public Person {
	friend istream& operator>>(istream& in, Teacher& t);
	friend ostream& operator<<(ostream& out, const Teacher& t);
protected:
	string subject;
	int hours;
public:
	~Teacher() {}
	Teacher() {
		subject = "";
		hours = 0;
	}
	Teacher(const Teacher& t) {
		subject = t.subject;
		hours = t.hours;
	}
	Teacher(string name, int age, string sub, int clocks) : Person(age, name) {
		this->set_subj(sub);
		this->set_hours(clocks);
	}
	void set_subj(string& subj) {
		subject = subj;
	}
	void set_hours(int& nHours) {
		hours = nHours;
	}
	string get_subject() {
		return subject;
	}
	int get_hours() {
		return hours;
	}
	Teacher operator-(const int& minus) const { 
		return Teacher(this->name, this->age, this->subject, this->hours - minus);
	}
	Teacher operator+(const int& plus) const { /
		return Teacher(this->name, this->age, this->subject, this->hours + plus);
	}
	void output() override { 
		cout << "\nName: " << name;
		cout << "\nAge: " << age;
		cout << "\nSubject: " << subject;
		cout << "\nHours: " << hours << endl;
	}
};

class Vector {
	friend ostream& operator<<(ostream& out, const Vector& v);
private:
	Object** beg;
	int size;
	int cur;
public:
	~Vector(){}
	Vector() {
		beg = 0;
		size = 0;
		cur = 0;
	}
	Vector(int lin) {
		beg = new Object * [lin];
		cur = 0;
		size = lin;
	}
	void add(Object* arr) {
		if (cur < size) {
			beg[cur] = arr;
			cur++;
		}
	}
};

istream& operator>>(istream& in, Person& p) { 
	cout << "Enter the name: ";
	getline(in, p.name);
	cout << "\nEnter the age: ";
	(in >> p.age).ignore();
	cout << endl << endl;
	return in;
}
ostream& operator<<(ostream& out, const Person& p) { 
	out << "Name: " << p.name;
	out << "\nAge: " << p.age;
	cout << endl << endl;
	return out;
}
istream& operator>>(istream& in, Teacher& t) { 
	cout << "Enter the name: ";
	getline(in, t.name);
	cout << "\nEnter the age: ";
	(in >> t.age).ignore();
	cout << "\nEnter the subject: ";
	in >> t.subject;
	cout << "\nEnter the hours: ";
	in >> t.hours;
	cout << endl << endl;
	return in;
}
ostream& operator<<(ostream& out, const Teacher& t) { 
	cout << "Name: " << t.name;
	cout << "\nAge: " << t.age;
	cout << "\nSubject: " << t.subject;
	cout << "\nHours: " << t.hours;
	cout << endl << endl;
	return out;
}
ostream& operator<<(ostream& out, const Vector& v) {
	if (v.size == 0) // проверяем вектор на пустоту
		out << "\nVector is empty";
	else {
		Object** ptr = v.beg; // создаём указатель на начало вектора
		for (int i = 0; i < v.cur; i++) { // проходимся по всем позициям вектора
			(*ptr)->output(); // вызываем функцию output() в зависимости от объекта класса, на который сейчас указывает указатель
			ptr++; // переходим к следующей позиции вектора (арифметика указателей)
		}
	}
	return out;
}

int main() {
	Vector vec(4);
	Person per;
	Teacher teach;
	cout << "Basic class: " << endl;
	cin >> per;
	cout << per;
	cout << "\nDerived class" << endl;
	cin >> teach;
	cout << teach;
	cout << "\n\nHours - 10" << endl << teach - 10;
	cout << "\n\nHours - 10" << endl << teach + 10;
	Object* p = &per;
	vec.add(p);
	p = &teach;
	vec.add(p);
	cout << "\nVector" << endl;
	cout << vec;
	return 0;
}