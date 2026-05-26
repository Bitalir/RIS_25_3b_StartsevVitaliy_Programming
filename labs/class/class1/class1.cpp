#include <iostream>
#include <clocale>
using namespace std;

class Pair {
private:
    int first;
    double second;
    bool isValid;
    double total;
public:
    void Init(int f, double s) {
        if (s < 0 || s > 1) {
            cout << "Ошибка: введено неверное значение second" << endl;
            isValid = false;
        }
        first = f;
        second = s;
        isValid = true;
    }
    
    void Read() {
        cout << "Введите значение first: ";
        cin >> first;
        cout << "Введите значение second: ";
        cin >> second;
        while (second < 0 || second >= 1) {
            cout << "Ошибка: введено неверное значение second. Введите другое значение: ";
            cin >> second;
        }
        isValid = true;
    }

    void Show() {
        if (!isValid) {
            cout << "Объект содержит некорректные данные" << endl;
            return;
        }
        double total = first + second;
        cout << "Число: " << total << endl;
    }

    long double multiply(int k) {
        if (!isValid) {
            cout << "Оишбка";
            return 0;
        }
        return total * k;
    }

};
Pair make_pair(int f, double s) {
    Pair p;
    p.Init(f, s);
    return p;
}

int main() {
    setlocale(LC_ALL, "RU");
    cout << "Init: " << endl;
    Pair p1;
    p1.Init(2, 0.06);
    p1.Show();
    cout << "Read: " << endl;
    Pair p2;
    p2.Read();
    p2.Show();
    cout << "make_pair: " << endl;
    Pair p3 = make_pair(5, 0.66);
    p3.Show();
    return 0;
}
