#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Stadium {
    char name[50];
    char address[100];
    int capacity;
    char sports[100];
};

void clearInput() {
    cin.ignore(10000, '\n');
}

void createFile(const char* filename) {
    ofstream fout(filename, ios::binary);
    if (!fout) { cerr << "Ошибка создания файла!\n"; return; }
    int n;
    cout << "Количество стадионов: ";
    cin >> n;
    clearInput();
    Stadium s;
    for (int i = 0; i < n; ++i) {
        cout << "\nСтадион #" << i + 1 << ":\n";
        cout << "Название: "; cin.getline(s.name, 50);
        cout << "Адрес: "; cin.getline(s.address, 100);
        cout << "Вместимость: "; cin >> s.capacity;
        clearInput();
        cout << "Виды спорта: "; cin.getline(s.sports, 100);
        fout.write((char*)&s, sizeof(Stadium));
    }
    fout.close();
    cout << "Файл создан.\n";
}

void printFile(const char* filename) {
    ifstream fin(filename, ios::binary);
    if (!fin) { cerr << "Ошибка открытия файла!\n"; return; }
    Stadium s;
    int cnt = 0;
    cout << "\nСодержимое:\n";
    while (fin.read((char*)&s, sizeof(Stadium))) {
        cout << ++cnt << ": " << s.name << ", " << s.address
            << ", " << s.capacity << ", " << s.sports << "\n";
    }
    fin.close();
    if (cnt == 0) cout << "Файл пуст.\n";
}

void deleteByName(const char* filename, const char* target) {
    ifstream fin(filename, ios::binary);
    if (!fin) { cerr << "Ошибка открытия файла!\n"; return; }
    ofstream fout("temp.dat", ios::binary);
    if (!fout) { cerr << "Ошибка создания временного файла!\n"; fin.close(); return; }
    Stadium s;
    bool found = false;
    while (fin.read((char*)&s, sizeof(Stadium))) {
        if (!found && strcmp(s.name, target) == 0) {
            found = true; // пропускаем эту запись
            continue;
        }
        fout.write((char*)&s, sizeof(Stadium));
    }
    fin.close();
    fout.close();
    if (!found) {
        cout << "Запись \"" << target << "\" не найдена.\n";
        remove("temp.dat");
        return;
    }
    remove(filename);
    rename("temp.dat", filename);
    cout << "Запись удалена.\n";
}

void insertAfter(const char* filename, int pos) {
    ifstream fin(filename, ios::binary);
    if (!fin) { cerr << "Ошибка открытия файла!\n"; return; }
    fin.seekg(0, ios::end);
    int count = fin.tellg() / sizeof(Stadium);
    fin.seekg(0, ios::beg);
    if (pos < 1 || pos > count) {
        cerr << "Некорректная позиция! (1.." << count << ")\n";
        fin.close();
        return;
    }
    ofstream fout("temp.dat", ios::binary);
    if (!fout) { cerr << "Ошибка создания временного файла!\n"; fin.close(); return; }
    Stadium s, new1, new2;
    for (int i = 1; i <= pos; ++i) {
        fin.read((char*)&s, sizeof(Stadium));
        fout.write((char*)&s, sizeof(Stadium));
    }
    cout << "Первый новый стадион:\n";
    cout << "Название: "; clearInput(); cin.getline(new1.name, 50);
    cout << "Адрес: "; cin.getline(new1.address, 100);
    cout << "Вместимость: "; cin >> new1.capacity; clearInput();
    cout << "Виды спорта: "; cin.getline(new1.sports, 100);
    fout.write((char*)&new1, sizeof(Stadium));
    cout << "Второй новый стадион:\n";
    cout << "Название: "; cin.getline(new2.name, 50);
    cout << "Адрес: "; cin.getline(new2.address, 100);
    cout << "Вместимость: "; cin >> new2.capacity; clearInput();
    cout << "Виды спорта: "; cin.getline(new2.sports, 100);
    fout.write((char*)&new2, sizeof(Stadium));
    while (fin.read((char*)&s, sizeof(Stadium))) {
        fout.write((char*)&s, sizeof(Stadium));
    }
    fin.close();
    fout.close();
    remove(filename);
    rename("temp.dat", filename);
    cout << "Два элемента добавлены.\n";
}

int main() {
    system("chcp 1251");
    system("cls");
    setlocale(LC_ALL, "RU");
    const char* file = "stadium.dat";
    cout << "=== СОЗДАНИЕ ===\n";
    createFile(file);
    printFile(file);
    cout << "\n=== УДАЛЕНИЕ ===\n";
    char name[50];
    cout << "Название для удаления: ";
    cin.getline(name, 50);
    deleteByName(file, name);
    printFile(file);
    cout << "\n=== ДОБАВЛЕНИЕ ===\n";
    int pos;
    cout << "Номер позиции (после которой добавить): ";
    cin >> pos;
    insertAfter(file, pos);
    printFile(file);

    return 0;
}