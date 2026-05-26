#include <iostream>
#include <string>
#include <clocale>
using namespace std;

struct Node {
    string data;
    Node* next = nullptr;
};

struct Stack {
    Node* top = nullptr;
};

void Push(Stack& s, const string& val) {
    Node* newNode = new Node;
    newNode->data = val;
    newNode->next = s.top;
    s.top = newNode;
}

string Pop(Stack& s) {
    if (!s.top) return "";
    Node* toDel = s.top;
    string val = toDel->data;
    s.top = s.top->next;
    delete toDel;
    return val;
}

int size(const Stack& s) {
    int cnt = 0;
    Node* cur = s.top;
    while (cur) { ++cnt; cur = cur->next; }
    return cnt;
}

void printStack(const Stack& s) {
    Node* cur = s.top;
    while (cur) {
        cout << cur->data << " ";
        cur = cur->next;
    }
    cout << endl;
}

void FillStack(Stack& s, int n) {
    string tmp;
    cout << "Введите " << n << " элементов (последний будет на вершине):\n";
    for (int i = 0; i < n; ++i) {
        cout << i + 1 << "-й: ";
        cin >> tmp;
        Push(s, tmp);
    }
}

int main() {
    setlocale(LC_ALL, "RU");
    system("chcp 1251 > nul");
    system("cls");
    int n;
    cout << "Введите количество элементов: ";
    cin >> n;
    Stack s;
    FillStack(s, n);
    printStack(s);
    string str;
    cout << "Введите элемент для добавления на вершину (начало): ";
    cin >> str;
    Push(s, str);
    printStack(s);
    cout << "Удаление элемента с вершины:\n";
    if (s.top) cout << "Удалён: " << Pop(s) << endl;
    printStack(s);

    return 0;
}