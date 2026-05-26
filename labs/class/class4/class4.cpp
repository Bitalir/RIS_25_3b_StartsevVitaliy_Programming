#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

class Person
{
protected:
    string name;
    int age;

public:
    Person() { this->name = ""; this->age = 0; }
    Person(const int& age, const string& name) { this->set_age(age); this->set_name(name); }
    Person(const string& name, const int& age) : Person(age, name) {};
    Person(const Person& p) { this->name = p.name; this->age = p.age; };

    void set_name(const string& name) { this->name = name; };

    void set_age(const int& age) {
        if (age < 0) {
            cerr << "Неверный возраст: " << age << endl;
            exit(3);
        }
        this->age = age;
    }

    int get_age() const { return this->age; };
    string get_name() const { return this->name; };
    Person& operator=(const Person& p)
    {
        this->name = p.name;
        this->age = p.age;
        return *this;
    };

    friend ostream& operator<<(ostream& stream, const Person& p)
    {
        stream << "Имя : " << p.name << endl;
        stream << "Возраст : " << p.age;
        return stream;
    };

    friend istream& operator>>(istream& stream, Person& p)
    {
        string tmp;
        int a;

        cout << "Имя : ";
        stream >> tmp;
        p.set_name(tmp);

        cout << "Возраст : ";
        stream >> a;
        p.set_age(a);

        cout << endl;
        return stream;
    };
};

class Teacher : public Person
{
protected:
    int hours;
    string subject;

public:
    Teacher() { this->hours = 0; this->subject = ""; };

    Teacher(const string& name, const int& age, const string& sub, const int& hours) : Person(age, name)
    {
        this->set_mark(hours);
        this->set_subject(sub);
    }

    Teacher(const int& age, const string& name, const string& sub, const int& hours) : Teacher(name, age, sub, hours) {};

    void set_mark(const int& hours)
    {
        if (hours <= 0)
        {
            cerr << "Неверное количество часов" << endl;
            exit(3);
        }
        this->hours = hours;
    }

    void set_subject(const string& sub) { this->subject = sub; };

    int get_mark() const { return this->hours; };

    string get_subject() const { return this->subject; };

    friend ostream& operator<<(ostream& stream, const Teacher& s)
    {
        const Person* p_s = &s;
        stream << *p_s << endl;
        stream << "Предмет : " << s.subject << endl;
        stream << "Количество часов : " << s.hours;

        return stream;
    }
    friend istream& operator>>(istream& stream, Teacher& s)
    {
        string tmp;
        int m;
        Person* const p_s = &s;
        stream >> *p_s;
        cout << "Предмет : ";
        stream >> tmp;
        s.set_subject(tmp);
        cout << "Количество часов : ";
        stream >> m;
        s.set_mark(m);
        cout << endl;
        return stream;
    }
};

template <class T>
int CountAgeGreater(T* persons, int count, int age)
{
    int counter = 0;
    for (int i = 0; i < count; i++)
    {
        if ((persons + i)->get_age() > age)
        {
            counter++;
        }
    }
    return counter;
};

void HelloHuman(const Person& p) {
    cout << "Hello, " << p.get_name() << endl;
}
Person* SetPerson(Person& p, string name, int age)
{
    p.set_name(name);
    p.set_age(age);
    return &p;
}

Person* persons;
Teacher* teachers;
int age;

int main()
{
    setlocale(LC_ALL, "RU");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int N;
    cout << "Введите количество человек: ";
    cin >> N;
    persons = new Person[N];
    for (int i = 0; i < N; i++)
    {
        cin >> persons[i];
    }
    cout << "Введите возраст: ";
    cin >> age;
    cout << "Количество человек, возраст которых больше указанного: " << CountAgeGreater(persons, N, age) << endl;
    delete[] persons;
    cout << "Введите количество учителей: ";
    cin >> N;

    teachers = new Teacher[N];

    for (int i = 0; i < N; i++)
    {
        cin >> teachers[i];
    }

    cout << "Введите возраст: ";
    cin >> age;

    cout << "Количество учителей, возраст которых больше указанного: " << CountAgeGreater(teachers, N, age) << endl;
    delete[] teachers;
    string name;
    string sub;
    int hours;

    cout << "Введите имя: ";
    cin >> name;
    cout << "Введите возраст: ";
    cin >> age;
    cout << "Введите предмет: ";
    cin >> sub;
    cout << "Введите количество часов: ";
    cin >> hours;

    Teacher p;
    p.set_subject(sub);
    p.set_mark(hours);
    Person* person_p = new Person(*SetPerson(p, name, age));
    person_p->set_age(person_p->get_age() + 1);
    cout << "Учитель: " << endl << p << endl;
    cout << "Тот же человек (возраст += 1): " << endl << *person_p << endl;
    delete person_p;
    HelloHuman(p);
}