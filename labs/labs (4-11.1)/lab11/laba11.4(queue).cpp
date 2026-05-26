#include <iostream>
#include <string>
#include <clocale>
using namespace std;

struct Node {
    string data;
    Node* next = nullptr;
};

struct Queue {
    Node* front = nullptr;
    Node* rear = nullptr;
};

void Enqueue(Queue& q, const string& val) {
    Node* newNode = new Node;
    newNode->data = val;
    if (!q.rear) {
        q.front = q.rear = newNode;
        return;
    }
    q.rear->next = newNode;
    q.rear = newNode;
}

string Dequeue(Queue& q) {
    if (!q.front) return "";
    Node* toDel = q.front;
    string val = toDel->data;
    q.front = q.front->next;
    if (!q.front) q.rear = nullptr;
    delete toDel;
    return val;
}

int size(const Queue& q) {
    int cnt = 0;
    Node* cur = q.front;
    while (cur) { ++cnt; cur = cur->next; }
    return cnt;
}

void printQueue(const Queue& q) {
    Node* cur = q.front;
    while (cur) {
        cout << cur->data << " ";
        cur = cur->next;
    }
    cout << endl;
}

void FillQueue(Queue& q, int n) {
    string tmp;
    cout << "Введите " << n << " элементов:\n";
    for (int i = 0; i < n; ++i) {
        cout << i + 1 << "-й: ";
        cin >> tmp;
        Enqueue(q, tmp);
    }
}

int main() {
    setlocale(LC_ALL, "RU");
    system("chcp 1251 > nul");
    system("cls");
    int n;
    cout << "Введите количество элементов: ";
    cin >> n;
    Queue q;
    FillQueue(q, n);
    printQueue(q);
    string str;
    cout << "Введите элемент для добавления в конец: ";
    cin >> str;
    Enqueue(q, str);
    printQueue(q);
    cout << "Удаление элемента из начала:\n";
    if (q.front) cout << "Удалён: " << Dequeue(q) << endl;
    printQueue(q);

    return 0;
}