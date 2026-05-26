#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
#include <numeric>
#include <clocale>

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

    double sum() const { return first + second; }

    bool operator<(const Pair& other) const {
        return sum() < other.sum();
    }
    bool operator>(const Pair& other) const {
        return other < *this;
    }
    bool operator==(const Pair& other) const {
        return first == other.first && second == other.second;
    }

    Pair operator/(double val) const {
        if (val == 0) return *this;
        return Pair(static_cast<int>(first / val), second / val);
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

void addMinToPosition(vector<Pair>& v, size_t pos) {
    if (v.empty()) return;
    auto it = min_element(v.begin(), v.end());
    Pair minVal = *it;
    if (pos > v.size()) pos = v.size();
    v.insert(v.begin() + pos, minVal);
}

void printPair(const Pair& p) {
    cout << p << " ";
}

void task1() {
    cout << "\n========== ЗАДАЧА 1 (vector<Pair>) ==========\n";
    vector<Pair> vec;
    int n;
    cout << "Введите количество элементов: ";
    cin >> n;
    cout << "Введите " << n << " пар:\n";
    for (int i = 0; i < n; ++i) {
        Pair p;
        cin >> p;
        vec.push_back(p);
    }

    cout << "Исходный вектор: ";
    for_each(vec.begin(), vec.end(), printPair);
    cout << endl;

    cout << "Замена элементов (сумма > 15) на (0:0)\n";
    replace_if(vec.begin(), vec.end(), [](const Pair& p) { return p.sum() > 15; }, Pair(0, 0));
    cout << "После замены: ";
    for_each(vec.begin(), vec.end(), printPair);
    cout << endl;

    cout << "Удаление элементов (first < 0)\n";
    vec.erase(remove_if(vec.begin(), vec.end(), [](const Pair& p) { return p.getFirst() < 0; }), vec.end());
    cout << "После удаления: ";
    for_each(vec.begin(), vec.end(), printPair);
    cout << endl;

    cout << "Сортировка по возрастанию суммы:\n";
    sort(vec.begin(), vec.end());
    for_each(vec.begin(), vec.end(), printPair);
    cout << endl;

    cout << "Сортировка по убыванию суммы:\n";
    sort(vec.begin(), vec.end(), greater<Pair>());
    for_each(vec.begin(), vec.end(), printPair);
    cout << endl;

    int searchFirst = 5;
    auto it = find_if(vec.begin(), vec.end(), [searchFirst](const Pair& p) { return p.getFirst() == searchFirst; });
    if (it != vec.end())
        cout << "Найден элемент с first = " << searchFirst << ": " << *it << endl;
    else
        cout << "Элемент с first = " << searchFirst << " не найден\n";

    int cnt = count_if(vec.begin(), vec.end(), [](const Pair& p) { return p.sum() > 10; });
    cout << "Количество элементов с суммой > 10: " << cnt << endl;

    size_t pos = 2;
    cout << "Добавление минимального элемента на позицию " << pos << endl;
    addMinToPosition(vec, pos);
    cout << "Результат: ";
    for_each(vec.begin(), vec.end(), printPair);
    cout << endl;
}

vector<Pair> queueToVector(queue<Pair> q) {
    vector<Pair> v;
    while (!q.empty()) {
        v.push_back(q.front());
        q.pop();
    }
    return v;
}

queue<Pair> vectorToQueue(const vector<Pair>& v) {
    queue<Pair> q;
    for (const auto& p : v)
        q.push(p);
    return q;
}

void removeLessThanAverage(queue<Pair>& q) {
    if (q.empty()) return;
    vector<Pair> v = queueToVector(q);
    double total = accumulate(v.begin(), v.end(), 0.0, [](double acc, const Pair& p) { return acc + p.sum(); });
    double avg = total / v.size();
    cout << "Среднее арифметическое суммы: " << avg << endl;
    v.erase(remove_if(v.begin(), v.end(), [avg](const Pair& p) { return p.sum() < avg; }), v.end());
    q = vectorToQueue(v);
}

void task2() {
    cout << "\n========== ЗАДАЧА 2 (queue<Pair>) ==========\n";
    queue<Pair> q;
    int n;
    cout << "Введите количество элементов: ";
    cin >> n;
    cout << "Введите " << n << " пар:\n";
    for (int i = 0; i < n; ++i) {
        Pair p;
        cin >> p;
        q.push(p);
    }

    auto printQueue = [](const queue<Pair>& q) {
        queue<Pair> temp = q;
        while (!temp.empty()) {
            cout << temp.front() << " ";
            temp.pop();
        }
        cout << endl;
        };
    cout << "Исходная очередь: ";
    printQueue(q);

    cout << "Замена элементов (сумма > 20) на (0:0)\n";
    vector<Pair> v = queueToVector(q);
    replace_if(v.begin(), v.end(), [](const Pair& p) { return p.sum() > 20; }, Pair(0, 0));
    q = vectorToQueue(v);
    cout << "После замены: ";
    printQueue(q);

    cout << "Удаление элементов (first == 0)\n";
    v = queueToVector(q);
    v.erase(remove_if(v.begin(), v.end(), [](const Pair& p) { return p.getFirst() == 0; }), v.end());
    q = vectorToQueue(v);
    cout << "После удаления: ";
    printQueue(q);

    cout << "Сортировка очереди по возрастанию суммы:\n";
    v = queueToVector(q);
    sort(v.begin(), v.end());
    q = vectorToQueue(v);
    printQueue(q);

    cout << "Сортировка очереди по убыванию суммы:\n";
    v = queueToVector(q);
    sort(v.begin(), v.end(), greater<Pair>());
    q = vectorToQueue(v);
    printQueue(q);

    int searchFirst = 3;
    v = queueToVector(q);
    auto it = find_if(v.begin(), v.end(), [searchFirst](const Pair& p) { return p.getFirst() == searchFirst; });
    if (it != v.end())
        cout << "Найден элемент с first = " << searchFirst << ": " << *it << endl;
    else
        cout << "Элемент с first = " << searchFirst << " не найден\n";

    int cnt = count_if(v.begin(), v.end(), [](const Pair& p) { return p.getFirst() > 2; });
    cout << "Количество элементов с first > 2: " << cnt << endl;

    cout << "Удаление элементов, меньших среднего арифметического:\n";
    removeLessThanAverage(q);
    cout << "Результат: ";
    printQueue(q);
}

void divideByMax(multiset<Pair>& ms) {
    if (ms.empty()) return;
    Pair maxElem = *max_element(ms.begin(), ms.end());
    double maxSum = maxElem.sum();
    cout << "Максимальный элемент: " << maxElem << " (сумма = " << maxSum << ")\n";
    multiset<Pair> newSet;
    for (const auto& p : ms) {
        newSet.insert(p / maxSum);
    }
    ms = newSet;
}

void task3() {
    cout << "\n========== ЗАДАЧА 3 (multiset<Pair>) ==========\n";
    multiset<Pair> ms;
    int n;
    cout << "Введите количество элементов: ";
    cin >> n;
    cout << "Введите " << n << " пар:\n";
    for (int i = 0; i < n; ++i) {
        Pair p;
        cin >> p;
        ms.insert(p);
    }

    cout << "Исходное множество: ";
    for (const auto& p : ms) cout << p << " ";
    cout << endl;

    cout << "Замена элементов (first > 100) на (0:0)\n";
    vector<Pair> v(ms.begin(), ms.end());
    replace_if(v.begin(), v.end(), [](const Pair& p) { return p.getFirst() > 100; }, Pair(0, 0));
    ms.clear();
    ms.insert(v.begin(), v.end());
    cout << "После замены: ";
    for (const auto& p : ms) cout << p << " ";
    cout << endl;

    cout << "Удаление элементов (first < 0)\n";
    v.assign(ms.begin(), ms.end());
    v.erase(remove_if(v.begin(), v.end(), [](const Pair& p) { return p.getFirst() < 0; }), v.end());
    ms.clear();
    ms.insert(v.begin(), v.end());
    cout << "После удаления: ";
    for (const auto& p : ms) cout << p << " ";
    cout << endl;

    cout << "Множество отсортировано по возрастанию суммы: ";
    for (const auto& p : ms) cout << p << " ";
    cout << endl;

    cout << "Вывод в порядке убывания (через reverse_iterator): ";
    for (auto it = ms.rbegin(); it != ms.rend(); ++it) cout << *it << " ";
    cout << endl;

    int searchFirst = 10;
    auto it = find_if(ms.begin(), ms.end(), [searchFirst](const Pair& p) { return p.getFirst() == searchFirst; });
    if (it != ms.end())
        cout << "Найден элемент с first = " << searchFirst << ": " << *it << endl;
    else
        cout << "Элемент с first = " << searchFirst << " не найден\n";

    int cnt = count_if(ms.begin(), ms.end(), [](const Pair& p) { return p.sum() > 50; });
    cout << "Количество элементов с суммой > 50: " << cnt << endl;

    cout << "Деление каждого элемента на максимальный элемент:\n";
    divideByMax(ms);
    cout << "Результат: ";
    for (const auto& p : ms) cout << p << " ";
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    task1();
    task2();
    task3();
    return 0;
}