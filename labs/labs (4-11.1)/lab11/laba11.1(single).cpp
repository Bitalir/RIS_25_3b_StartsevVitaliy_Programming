#include <iostream>
#include <string>
#include <clocale>
using namespace std;

struct Node {
    string data;
    Node* next = nullptr;
};

struct List {
    Node* head = nullptr;
};

void InsertItem(List& list, const string& data, int index = 0) {
    Node* newNode = new Node;
    newNode->data = data;

    if (list.head == nullptr) {
        list.head = newNode;
        return;
    }

    if (index <= 0) {                     
        newNode->next = list.head;
        list.head = newNode;
        return;
    }

    int counter = 0;
    Node* cur = list.head;
    while (cur->next != nullptr && counter < index - 1) {
        cur = cur->next;
        ++counter;
    }
    newNode->next = cur->next;
    cur->next = newNode;
}
void DeleteByIndex(List& list, int index) {
    if (list.head == nullptr || index < 0) return;

    if (index == 0) {
        Node* toDel = list.head;
        list.head = list.head->next;
        delete toDel;
        return;
    }

    Node* cur = list.head;
    int counter = 0;
    while (cur->next != nullptr && counter < index - 1) {
        cur = cur->next;
        ++counter;
    }

    if (cur->next == nullptr) return;

    Node* toDel = cur->next;
    cur->next = cur->next->next;
    delete toDel;
}
int listSize(const List& list) {
    int size = 0;
    Node* cur = list.head;
    while (cur) {
        ++size;
        cur = cur->next;
    }
    return size;
}
void printList(const List& list) {
    Node* cur = list.head;
    while (cur) {
        cout << cur->data << " ";
        cur = cur->next;
    }
    cout << endl;
}
void FillList(List& list, int n) {
    string temp;
    cout << "Введите " << n << " элементов:\n";
    for (int i = 0; i < n; ++i) {
        cout << i + 1 << "-й: ";
        cin >> temp;
        InsertItem(list, temp, i); 
    }
}

int main() {
    setlocale(LC_ALL, "RU");
    system("chcp 1251");
    system("cls");
    int n;
    cout << "Введите количество элементов: ";
    cin >> n;
    List list;
    FillList(list, n);
    printList(list);
    string str;
    cout << "Введите элемент для добавления в конец: ";
    cin >> str;
    InsertItem(list, str, listSize(list));
    printList(list);
    cout << "Введите элемент для добавления в начало: ";
    cin >> str;
    InsertItem(list, str);
    printList(list);
    int pos;
    cout << "Введите номер, после которого вставить: ";
    cin >> pos;
    cout << "Введите элемент: ";
    cin >> str;
    InsertItem(list, str, pos);
    printList(list);
    int K;
    cout << "Сколько элементов удалить? ";
    cin >> K;
    int* indices = new int[K];
    cout << "Введите номера удаляемых элементов (от 1 до " << listSize(list) << "):\n";
    for (int i = 0; i < K; ++i) {
        cin >> indices[i];
        indices[i]--; 
    }
    for (int i = 0; i < K - 1; ++i)
        for (int j = 0; j < K - i - 1; ++j)
            if (indices[j] < indices[j + 1])
                swap(indices[j], indices[j + 1]);
    for (int i = 0; i < K; ++i)
        DeleteByIndex(list, indices[i]);
    cout << "Список после удаления:\n";
    printList(list);
    cout << "Добавим " << K << " новых элементов на места удалённых.\n";
    int* newPositions = new int[K];
    string* newData = new string[K];
    for (int i = 0; i < K; ++i) {
        cout << "Введите позицию для вставки: ";
        cin >> newPositions[i];
        cout << "Введите строку: ";
        cin >> newData[i];
    }
    for (int i = 0; i < K; ++i)
        InsertItem(list, newData[i], newPositions[i]);
    cout << "Список после добавления:\n";
    printList(list);
    delete[] indices;
    delete[] newPositions;
    delete[] newData;
    return 0;
}