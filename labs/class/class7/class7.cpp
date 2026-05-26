#include <iostream>
#include <clocale>
using namespace std;

template<typename T>
class List {
private:
    template<typename U>
    struct Node {
        U data;
        Node* prev;
        Node* next;
        Node(const U& val = U(), Node* p = nullptr, Node* n = nullptr)
            : data(val), prev(p), next(n) {
        }
    };

    Node<T>* head;
    Node<T>* tail;
    int size;

public:
    List() : head(nullptr), tail(nullptr), size(0) {}

    List(int s, const T& k = T()) : head(nullptr), tail(nullptr), size(0) {
        if (s <= 0) return;
        for (int i = 0; i < s; ++i) {
            push_back(k);
        }
    }

    List(const List& other) : head(nullptr), tail(nullptr), size(0) {
        Node<T>* cur = other.head;
        while (cur) {
            push_back(cur->data);
            cur = cur->next;
        }
    }

    ~List() {
        clear();
    }

    List& operator=(const List& other) {
        if (this != &other) {
            clear();
            Node<T>* cur = other.head;
            while (cur) {
                push_back(cur->data);
                cur = cur->next;
            }
        }
        return *this;
    }

    T& operator[](int index) {
        if (index < 0 || index >= size) {
            cerr << "Ошибка: индекс вне диапазона!" << endl;
            exit(1);
        }
        Node<T>* cur = head;
        for (int i = 0; i < index; ++i) cur = cur->next;
        return cur->data;
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= size) {
            cerr << "Ошибка: индекс вне диапазона!" << endl;
            exit(1);
        }
        Node<T>* cur = head;
        for (int i = 0; i < index; ++i) cur = cur->next;
        return cur->data;
    }

    int operator()() const {
        return size;
    }

    List operator*(int n) const {
        List result;
        Node<T>* cur = head;
        while (cur) {
            result.push_back(cur->data * n);
            cur = cur->next;
        }
        return result;
    }

    void push_back(const T& val) {
        Node<T>* newNode = new Node<T>(val, tail, nullptr);
        if (!head) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
        ++size;
    }

    void push_front(const T& val) {
        Node<T>* newNode = new Node<T>(val, nullptr, head);
        if (!head) {
            head = tail = newNode;
        }
        else {
            head->prev = newNode;
            head = newNode;
        }
        ++size;
    }

    void pop_back() {
        if (!head) return;
        if (head == tail) {
            delete head;
            head = tail = nullptr;
            size = 0;
            return;
        }
        Node<T>* temp = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete temp;
        --size;
    }

    void pop_front() {
        if (!head) return;
        if (head == tail) {
            delete head;
            head = tail = nullptr;
            size = 0;
            return;
        }
        Node<T>* temp = head;
        head = head->next;
        head->prev = nullptr;
        delete temp;
        --size;
    }

    T& front() {
        if (!head) {
            cerr << "Ошибка: список пуст!" << endl;
            exit(1);
        }
        return head->data;
    }

    T& back() {
        if (!tail) {
            cerr << "Ошибка: список пуст!" << endl;
            exit(1);
        }
        return tail->data;
    }

    bool empty() const {
        return size == 0;
    }

    void clear() {
        Node<T>* cur = head;
        while (cur) {
            Node<T>* next = cur->next;
            delete cur;
            cur = next;
        }
        head = tail = nullptr;
        size = 0;
    }

    friend ostream& operator<<(ostream& out, const List<T>& lst) {
        out << endl << "---Вывод элементов списка---" << endl;
        Node<T>* cur = lst.head;
        while (cur) {
            out << cur->data << " ";
            cur = cur->next;
        }
        out << endl << "---Вывод элементов списка завершён---" << endl;
        return out;
    }

    friend istream& operator>>(istream& in, List<T>& lst) {
        cout << endl << "---Ввод элементов списка---" << endl;
        Node<T>* cur = lst.head;
        while (cur) {
            in >> cur->data;
            cur = cur->next;
        }
        cout << endl << "---Ввод элементов списка завершён---" << endl;
        return in;
    }
};

class Pair {
private:
    int first;
    double second;
public:
    Pair() : first(0), second(0.0) {}

    Pair(int f, double s) : first(f), second(s) {}

    Pair operator-(int val) const {
        return Pair(first - val, second);
    }

    Pair operator-(double val) const {
        return Pair(first, second - val);
    }

    Pair operator*(int n) const {
        return Pair(first * n, second * n);
    }

    bool operator==(const Pair& other) const {
        return (first == other.first) && (second == other.second);
    }

    bool operator!=(const Pair& other) const {
        return !(*this == other);
    }

    int getFirst() const { return first; }
    double getSecond() const { return second; }
    void setFirst(int f) { first = f; }
    void setSecond(double s) { second = s; }

    friend ostream& operator<<(ostream& out, const Pair& p) {
        out << p.first << ":" << p.second;
        return out;
    }

    friend istream& operator>>(istream& in, Pair& p) {
        cout << "Введите первое число (int): ";
        in >> p.first;
        cout << "Введите второе число (double): ";
        in >> p.second;
        return in;
    }
};

int main() {
    setlocale(LC_ALL, "Rus");

    cout << "=== ТЕСТ ДЛЯ int ===" << endl;
    List<int> listInt(5, 10);
    cout << listInt;
    cout << "Размер: " << listInt() << endl;
    for (int i = 0; i < listInt(); ++i)
        listInt[i] = i * 5;
    cout << listInt;
    List<int> listInt2 = listInt * 3;
    cout << "Умножение на 3:" << listInt2;

    cout << "\n=== ТЕСТ ДЛЯ float ===" << endl;
    List<float> listFloat(4, 1.1f);
    cout << listFloat;
    listFloat[2] = 9.9f;
    cout << listFloat;
    List<float> listFloat2 = listFloat * 2;
    cout << "Умножение на 2:" << listFloat2;

    cout << "\n=== ТЕСТ ДЛЯ double ===" << endl;
    List<double> listDouble;
    listDouble.push_back(1.11);
    listDouble.push_back(2.22);
    listDouble.push_back(3.33);
    cout << listDouble;
    listDouble.pop_front();
    cout << "После pop_front:" << listDouble;
    listDouble.pop_back();
    cout << "После pop_back:" << listDouble;
    List<double> listDouble2 = listDouble * 10;
    cout << "Умножение на 10:" << listDouble2;

    cout << "\n=== ТЕСТ ДЛЯ Pair ===" << endl;
    List<Pair> listPair;
    listPair.push_back(Pair(1, 2.5));
    listPair.push_back(Pair(3, 4.7));
    listPair.push_back(Pair(5, 6.9));
    cout << "Исходный список пар:" << listPair;

    List<Pair> listPair2 = listPair * 3;
    cout << "Умножение всех пар на 3:" << listPair2;

    cout << "\nДемонстрация вычитания для Pair:" << endl;
    Pair p(10, 20.5);
    cout << "Исходная пара: " << p << endl;
    Pair p1 = p - 3;      // вычитание из первого поля
    cout << "После вычитания 3 из первого: " << p1 << endl;
    Pair p2 = p - 2.5;    // вычитание из второго поля
    cout << "После вычитания 2.5 из второго: " << p2 << endl;

    cout << "\nВвод нового списка из 2 пар:" << endl;
    List<Pair> inputPair(2);
    cin >> inputPair;
    cout << "Введённый список:" << inputPair;
    cout << "Первый элемент: " << inputPair[0] << endl;
    inputPair[0] = Pair(99, 88.5);
    cout << "После изменения первого элемента: " << inputPair[0] << endl;

    return 0;
}