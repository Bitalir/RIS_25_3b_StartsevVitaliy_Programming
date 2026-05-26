#include <iostream>
#include <fstream>

using namespace std;

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
    Pair& operator*=(int n) {
        first *= n;
        second *= n;
        return *this;
    }
    bool operator==(const Pair& other) const {
        return first == other.first && second == other.second;
    }
    bool operator!=(const Pair& other) const {
        return !(*this == other);
    }
    bool operator<(const Pair& other) const {
        if (first != other.first) return first < other.first;
        return second < other.second;
    }
    bool operator>(const Pair& other) const {
        return other < *this;
    }
    bool operator<=(const Pair& other) const {
        return !(*this > other);
    }
    bool operator>=(const Pair& other) const {
        return !(*this < other);
    }
    friend istream& operator>>(istream& in, Pair& p) {
        cout << "Введите первое число (int): ";
        in >> p.first;
        cout << "Введите второе число (double): ";
        in >> p.second;
        return in;
    }
    friend ostream& operator<<(ostream& out, const Pair& p) {
        out << p.first << ":" << p.second;
        return out;
    }
    int getFirst() const { return first; }
    double getSecond() const { return second; }
    void setFirst(int f) { first = f; }
    void setSecond(double s) { second = s; }
};

const char* FILENAME = "pairs.dat";

int getFileSize() {
    ifstream in(FILENAME, ios::binary);
    if (!in) return 0;
    in.seekg(0, ios::end);
    int size = in.tellg();
    in.close();
    return size;
}

Pair* readFromFile(int& count) {
    int fileSize = getFileSize();
    count = fileSize / sizeof(Pair);
    if (count == 0) return nullptr;
    ifstream in(FILENAME, ios::binary);
    Pair* data = new Pair[count];
    in.read(reinterpret_cast<char*>(data), fileSize);
    in.close();
    return data;
}

void writeToFile(Pair* data, int count) {
    ofstream out(FILENAME, ios::binary);
    out.write(reinterpret_cast<char*>(data), count * sizeof(Pair));
    out.close();
}

void createFile() {
    int n;
    cout << "Введите количество записей: ";
    cin >> n;
    Pair* data = new Pair[n];
    for (int i = 0; i < n; ++i) {
        cout << "\nЗапись " << i + 1 << ":\n";
        cin >> data[i];
    }
    writeToFile(data, n);
    delete[] data;
    cout << "Файл создан, записано " << n << " записей.\n";
}

void viewFile() {
    int count;
    Pair* data = readFromFile(count);
    if (count == 0) {
        cout << "Файл пуст.\n";
        return;
    }
    cout << "\nСодержимое файла:\n";
    for (int i = 0; i < count; ++i) {
        cout << i + 1 << ". " << data[i] << endl;
    }
    delete[] data;
}

void deleteInRange() {
    Pair k1, k2;
    cout << "Введите левую границу интервала k1:\n";
    cin >> k1;
    cout << "Введите правую границу интервала k2:\n";
    cin >> k2;
    if (k2 < k1) {
        cout << "Ошибка: k2 должна быть не меньше k1.\n";
        return;
    }
    int count;
    Pair* data = readFromFile(count);
    if (count == 0) {
        cout << "Файл пуст.\n";
        return;
    }
    int newCount = 0;
    for (int i = 0; i < count; ++i) {
        if (!(data[i] >= k1 && data[i] <= k2)) {
            ++newCount;
        }
    }
    Pair* newData = new Pair[newCount];
    int idx = 0;
    for (int i = 0; i < count; ++i) {
        if (!(data[i] >= k1 && data[i] <= k2)) {
            newData[idx++] = data[i];
        }
    }
    writeToFile(newData, newCount);
    delete[] data;
    delete[] newData;
    cout << "Удалено " << count - newCount << " записей.\n";
}

void multiplyByTwo() {
    Pair target;
    cout << "Введите значение для поиска:\n";
    cin >> target;
    int count;
    Pair* data = readFromFile(count);
    if (count == 0) {
        cout << "Файл пуст.\n";
        return;
    }
    int changed = 0;
    for (int i = 0; i < count; ++i) {
        if (data[i] == target) {
            data[i] *= 2;
            ++changed;
        }
    }
    writeToFile(data, count);
    delete[] data;
    cout << "Увеличено " << changed << " записей.\n";
}

void prependRecords() {
    int K;
    cout << "Введите K (количество записей для добавления в начало): ";
    cin >> K;
    Pair* newRecords = new Pair[K];
    for (int i = 0; i < K; ++i) {
        cout << "\nНовая запись " << i + 1 << ":\n";
        cin >> newRecords[i];
    }
    int oldCount;
    Pair* oldData = readFromFile(oldCount);
    int newCount = K + oldCount;
    Pair* newData = new Pair[newCount];
    for (int i = 0; i < K; ++i) {
        newData[i] = newRecords[i];
    }
    for (int i = 0; i < oldCount; ++i) {
        newData[K + i] = oldData[i];
    }
    writeToFile(newData, newCount);
    delete[] newRecords;
    delete[] oldData;
    delete[] newData;
    cout << "Добавлено " << K << " записей в начало.\n";
}

void showMenu() {
    cout << "\n========== МЕНЮ ==========\n";
    cout << "1. Создать файл (запись с клавиатуры)\n";
    cout << "2. Просмотреть файл\n";
    cout << "3. Удалить записи из интервала [k1, k2]\n";
    cout << "4. Увеличить в 2 раза записи с заданным значением\n";
    cout << "5. Добавить K записей в начало файла\n";
    cout << "0. Выход\n";
    cout << "Ваш выбор: ";
}

int main() {
    setlocale(LC_ALL, "Russian");
    int choice;
    do {
        showMenu();
        cin >> choice;
        switch (choice) {
        case 1: createFile(); break;
        case 2: viewFile(); break;
        case 3: deleteInRange(); break;
        case 4: multiplyByTwo(); break;
        case 5: prependRecords(); break;
        case 0: cout << "Программа завершена.\n"; break;
        default: cout << "Неверный выбор, попробуйте снова.\n";
        }
    } while (choice != 0);
    return 0;
}