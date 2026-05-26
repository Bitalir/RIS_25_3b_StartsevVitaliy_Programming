#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <limits>

using namespace std;

class Pair {
private:
    int first;
    double second;
public:
    Pair() : first(0), second(0.0) {}
    Pair(int f, double s) : first(f), second(s) {}

    int getFirst() const { return first; }
    double getSecond() const { return second; }
    void setFirst(int f) { first = f; }
    void setSecond(double s) { second = s; }

    bool operator<(const Pair& other) const {
        return (first < other.first) || (first == other.first && second < other.second);
    }
    bool operator>(const Pair& other) const { return other < *this; }
    bool operator==(const Pair& other) const { return first == other.first && second == other.second; }

    Pair operator/(double div) const {
        if (div == 0) return *this;
        return Pair(static_cast<int>(first / div), second / div);
    }

    friend istream& operator>>(istream& in, Pair& p) {
        cout << "  first (int): "; in >> p.first;
        cout << "  second (double): "; in >> p.second;
        return in;
    }
    friend ostream& operator<<(ostream& out, const Pair& p) {
        out << p.first << ":" << p.second;
        return out;
    }
};

void fillContainer(vector<float>& v, int n) {
    cout << "Введите " << n << " элементов float:\n";
    for (int i = 0; i < n; ++i) {
        float x;
        cin >> x;
        v.push_back(x);
    }
}

void addElements(vector<float>& v) {
    cout << "Добавление 3 элементов в конец:\n";
    for (int i = 0; i < 3; ++i) {
        float x;
        cin >> x;
        v.push_back(x);
    }
}

void removeElements(vector<float>& v) {
    if (v.size() >= 2) {
        cout << "Удаление второго элемента (индекс 1): " << v[1] << endl;
        v.erase(v.begin() + 1);
    }
}

void task1() {
    cout << "\n========== ЗАДАЧА 1 (vector<float>) ==========\n";
    vector<float> vec;
    fillContainer(vec, 4);
    cout << "Исходный вектор: ";
    for (float f : vec) cout << f << " "; cout << endl;

    addElements(vec);
    cout << "После добавления: ";
    for (float f : vec) cout << f << " "; cout << endl;

    removeElements(vec);
    cout << "После удаления: ";
    for (float f : vec) cout << f << " "; cout << endl;
}

void fillContainer(vector<Pair>& v, int n) {
    cout << "Введите " << n << " элементов Pair:\n";
    for (int i = 0; i < n; ++i) {
        Pair p;
        cin >> p;
        v.push_back(p);
    }
}

void addElements(vector<Pair>& v) {
    cout << "Добавление 2 элементов Pair в конец:\n";
    for (int i = 0; i < 2; ++i) {
        Pair p;
        cin >> p;
        v.push_back(p);
    }
}

void removeElements(vector<Pair>& v) {
    if (v.size() >= 3) {
        cout << "Удаление третьего элемента (индекс 2): " << v[2] << endl;
        v.erase(v.begin() + 2);
    }
}

void task2() {
    cout << "\n========== ЗАДАЧА 2 (vector<Pair>) ==========\n";
    vector<Pair> vec;
    fillContainer(vec, 3);
    cout << "Исходный вектор: ";
    for (const auto& p : vec) cout << p << " "; cout << endl;

    addElements(vec);
    cout << "После добавления: ";
    for (const auto& p : vec) cout << p << " "; cout << endl;

    removeElements(vec);
    cout << "После удаления: ";
    for (const auto& p : vec) cout << p << " "; cout << endl;
}

template<typename T>
class List {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& val = T(), Node* p = nullptr, Node* n = nullptr)
            : data(val), prev(p), next(n) {
        }
    };
    Node* head;
    Node* tail;
    int sz;

public:
    List() : head(nullptr), tail(nullptr), sz(0) {}
    ~List() { clear(); }

    List(const List& other) : head(nullptr), tail(nullptr), sz(0) {
        Node* cur = other.head;
        while (cur) {
            pushBack(cur->data);
            cur = cur->next;
        }
    }
    List& operator=(const List& other) {
        if (this != &other) {
            clear();
            Node* cur = other.head;
            while (cur) {
                pushBack(cur->data);
                cur = cur->next;
            }
        }
        return *this;
    }

    void pushBack(const T& val) {
        Node* newNode = new Node(val, tail, nullptr);
        if (!head) head = tail = newNode;
        else {
            tail->next = newNode;
            tail = newNode;
        }
        ++sz;
    }

    void pushFront(const T& val) {
        Node* newNode = new Node(val, nullptr, head);
        if (!head) head = tail = newNode;
        else {
            head->prev = newNode;
            head = newNode;
        }
        ++sz;
    }

    void popFront() {
        if (!head) return;
        Node* temp = head;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
        delete temp;
        --sz;
    }

    void popBack() {
        if (!tail) return;
        Node* temp = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete temp;
        --sz;
    }

    int size() const { return sz; }
    bool empty() const { return sz == 0; }

    T& operator[](int index) {
        if (index < 0 || index >= sz) throw out_of_range("Index out of range");
        Node* cur = head;
        for (int i = 0; i < index; ++i) cur = cur->next;
        return cur->data;
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= sz) throw out_of_range("Index out of range");
        Node* cur = head;
        for (int i = 0; i < index; ++i) cur = cur->next;
        return cur->data;
    }

    void insertAt(int pos, const T& val) {
        if (pos < 0 || pos > sz) throw out_of_range("Insert position out of range");
        if (pos == 0) { pushFront(val); return; }
        if (pos == sz) { pushBack(val); return; }
        Node* cur = head;
        for (int i = 0; i < pos; ++i) cur = cur->next;
        Node* newNode = new Node(val, cur->prev, cur);
        cur->prev->next = newNode;
        cur->prev = newNode;
        ++sz;
    }

    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        sz = 0;
    }

    void addMinToPosition(int pos) {
        if (sz == 0) return;
        T minElem = (*this)[0];
        for (int i = 1; i < sz; ++i)
            if ((*this)[i] < minElem) minElem = (*this)[i];
        insertAt(pos, minElem);
    }

    void print() const {
        Node* cur = head;
        while (cur) {
            cout << cur->data << " ";
            cur = cur->next;
        }
        cout << endl;
    }
};

void task3() {
    cout << "\n========== ЗАДАЧА 3 (параметризированный List, тип float) ==========\n";
    List<float> lst;
    cout << "Заполнение списка 5 элементами:\n";
    for (int i = 0; i < 5; ++i) {
        float x;
        cin >> x;
        lst.pushBack(x);
    }
    cout << "Список: "; lst.print();

    cout << "Добавление 2 элементов в конец:\n";
    float a, b;
    cin >> a >> b;
    lst.pushBack(a);
    lst.pushBack(b);
    cout << "После добавления: "; lst.print();

    cout << "Удаление первого элемента:\n";
    lst.popFront();
    cout << "После удаления: "; lst.print();

    int pos = 2;
    cout << "Находим минимальный элемент и добавляем его на позицию " << pos << endl;
    lst.addMinToPosition(pos);
    cout << "Результат: "; lst.print();
}

void fillQueue(queue<Pair>& q, int n) {
    cout << "Введите " << n << " элементов Pair для очереди:\n";
    for (int i = 0; i < n; ++i) {
        Pair p;
        cin >> p;
        q.push(p);
    }
}

void addElements(queue<Pair>& q) {
    cout << "Добавление 2 элементов в очередь (push):\n";
    for (int i = 0; i < 2; ++i) {
        Pair p;
        cin >> p;
        q.push(p);
    }
}

void removeElements(queue<Pair>& q) {
    if (!q.empty()) {
        cout << "Удаление одного элемента из очереди (pop): " << q.front() << endl;
        q.pop();
    }
}

void removeLessThanAverage(queue<Pair>& q) {
    if (q.empty()) return;
    double sum = 0;
    int count = 0;
    queue<Pair> temp = q;
    while (!temp.empty()) {
        Pair p = temp.front();
        sum += p.getFirst() + p.getSecond();
        ++count;
        temp.pop();
    }
    double average = sum / count;
    cout << "Среднее арифметическое (first+second): " << average << endl;

    queue<Pair> newQ;
    while (!q.empty()) {
        Pair p = q.front();
        q.pop();
        if ((p.getFirst() + p.getSecond()) >= average) {
            newQ.push(p);
        }
        else {
            cout << "Удалён элемент: " << p << " (меньше среднего)\n";
        }
    }
    q = newQ;
}

void task4() {
    cout << "\n========== ЗАДАЧА 4 (адаптер queue<Pair>) ==========\n";
    queue<Pair> q;
    fillQueue(q, 3);
    cout << "Содержимое очереди (через копию): ";
    queue<Pair> temp = q;
    while (!temp.empty()) { cout << temp.front() << " "; temp.pop(); } cout << endl;

    addElements(q);
    cout << "После добавления: ";
    temp = q;
    while (!temp.empty()) { cout << temp.front() << " "; temp.pop(); } cout << endl;

    removeElements(q);
    cout << "После удаления одного элемента: ";
    temp = q;
    while (!temp.empty()) { cout << temp.front() << " "; temp.pop(); } cout << endl;

    removeLessThanAverage(q);
    cout << "Очередь после удаления: ";
    temp = q;
    while (!temp.empty()) { cout << temp.front() << " "; temp.pop(); } cout << endl;
}

template<typename T>
class ListAsQueue {
private:
    queue<T> q;
public:
    void push(const T& val) { q.push(val); }
    void pop() { if (!q.empty()) q.pop(); }
    T& front() { return q.front(); }
    const T& front() const { return q.front(); }
    int size() const { return q.size(); }
    bool empty() const { return q.empty(); }

    void addAtIndex(int index, const T& val) {
        if (index < 0 || index >(int)q.size()) return;
        queue<T> temp;
        int i = 0;
        while (!q.empty()) {
            if (i == index) temp.push(val);
            temp.push(q.front());
            q.pop();
            ++i;
        }
        if (i == index) temp.push(val);
        q = temp;
    }

    void removeAtIndex(int index) {
        if (index < 0 || index >= (int)q.size()) return;
        queue<T> temp;
        int i = 0;
        while (!q.empty()) {
            if (i != index) temp.push(q.front());
            q.pop();
            ++i;
        }
        q = temp;
    }

    void divideByMax() {
        if (q.empty()) return;
        T maxElem = q.front();
        queue<T> temp = q;
        while (!temp.empty()) {
            if (temp.front() > maxElem) maxElem = temp.front();
            temp.pop();
        }
        queue<T> newQ;
        while (!q.empty()) {
            T val = q.front();
            q.pop();
            newQ.push(val / (double)(maxElem.getFirst() + maxElem.getSecond()));
        }
        q = newQ;
    }

    void print() const {
        queue<T> temp = q;
        while (!temp.empty()) {
            cout << temp.front() << " ";
            temp.pop();
        }
        cout << endl;
    }
};

void task5() {
    cout << "\n========== ЗАДАЧА 5 (параметризированный класс с queue, тип Pair) ==========\n";
    ListAsQueue<Pair> lq;
    cout << "Заполнение 3 элементами Pair:\n";
    for (int i = 0; i < 3; ++i) {
        Pair p;
        cin >> p;
        lq.push(p);
    }
    cout << "Очередь: "; lq.print();

    cout << "Добавление элемента в конец (позиция size):\n";
    Pair extra(10, 20.5);
    lq.addAtIndex(lq.size(), extra);
    cout << "После добавления: "; lq.print();

    cout << "Удаление элемента с индексом 1:\n";
    lq.removeAtIndex(1);
    cout << "После удаления: "; lq.print();

    cout << "Выполнение задания: каждый элемент разделить на максимальный\n";
    lq.divideByMax();
    cout << "Результат: "; lq.print();
}

int main() {
    setlocale(LC_ALL, "Russian");

    task1();
    task2();
    task3();
    task4();
    task5();

    return 0;
}