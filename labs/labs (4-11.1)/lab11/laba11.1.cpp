#include <iostream>
#include <clocale>
using namespace std;

struct Node {
    string data;
    Node* pointer_to_next_node = nullptr;
    Node* pointer_to_prev_node = nullptr;
};

struct List {
    Node* head_node = nullptr;
    Node* tail_node = nullptr;
};

void InsertItem(List& list, const string& data, int index = 0) {
    Node* new_node = new Node;
    new_node->data = data;

    if (list.head_node == nullptr) {
        list.head_node = new_node;
        list.tail_node = new_node;
        return;
    }

    if (index <= 0) { 
        new_node->pointer_to_next_node = list.head_node;
        list.head_node->pointer_to_prev_node = new_node;
        list.head_node = new_node;
        return;
    }

    int counter = 0;
    Node* current_node = list.head_node;
    while (current_node != nullptr && counter < index - 1) {
        current_node = current_node->pointer_to_next_node;
        ++counter;
    }

    if (current_node == nullptr) { 
        new_node->pointer_to_prev_node = list.tail_node;
        list.tail_node->pointer_to_next_node = new_node;
        list.tail_node = new_node;
        return;
    }

    new_node->pointer_to_prev_node = current_node;
    new_node->pointer_to_next_node = current_node->pointer_to_next_node;

    if (current_node->pointer_to_next_node != nullptr) {
        current_node->pointer_to_next_node->pointer_to_prev_node = new_node;
    }
    else {
        list.tail_node = new_node;
    }
    current_node->pointer_to_next_node = new_node;
}

void FillList(List& list, int size) {
    string temp;
    cout << "Введите элементы: " << endl;
    for (int i = 0; i < size; i++) {
        cout << i + 1 << "-й элемент: ";
        cin >> temp;
        InsertItem(list, temp, i);
    }
}

void printList(const List& list) {
    Node* cur = list.head_node;
    while (cur != nullptr) {
        cout << cur->data << " ";
        cur = cur->pointer_to_next_node;
    }
    cout << endl;
}

void DeleteElByIndex(List& l, int index) {
    if (l.head_node == nullptr || index < 0) return;

    Node* cur = l.head_node;
    int currentIndex = 0;
    while (cur != nullptr && currentIndex < index) {
        cur = cur->pointer_to_next_node;
        currentIndex++;
    }

    if (cur == nullptr) return; 

    Node* toDelete = cur;

    if (toDelete == l.head_node) {
        l.head_node = toDelete->pointer_to_next_node;
        if (l.head_node != nullptr) {
            l.head_node->pointer_to_prev_node = nullptr;
        }
        else {
            l.tail_node = nullptr; 
        }
    }
    else if (toDelete == l.tail_node) {
        l.tail_node = toDelete->pointer_to_prev_node;
        l.tail_node->pointer_to_next_node = nullptr;
    }
    else {
        toDelete->pointer_to_prev_node->pointer_to_next_node = toDelete->pointer_to_next_node;
        toDelete->pointer_to_next_node->pointer_to_prev_node = toDelete->pointer_to_prev_node;
    }

    delete toDelete;
}

int listSize(const List& list) {
    int size = 0;
    Node* cur = list.head_node;
    while (cur != nullptr) {
        size++;
        cur = cur->pointer_to_next_node;
    }
    return size;
}

int main() {
    setlocale(LC_ALL, "RU");
    system("chcp 1251");
    system("cls");

    string str;
    int n, k, K, del;

    cout << "Введите кол-во элементов: ";
    cin >> n;
    List list;
    FillList(list, n);
    printList(list);

    cout << "Введите элемент, который хотите добавить в конец: ";
    cin >> str;
    InsertItem(list, str, n);

    cout << "Введите элемент, который хотите добавить в начало: ";
    cin >> str;
    InsertItem(list, str);

    cout << "Введите номер эл-та, после которого нужно вставить элемент: ";
    cin >> k;
    cout << "Введите элемент, который хотите добавить: ";
    cin >> str;
    InsertItem(list, str, k);
    printList(list);

    cout << "Введите кол-во элементов, которые нужно удалить: ";
    cin >> K;
    int* itemNumbers = new int[K];
    cout << "Введите номера удаляемых элементов (от 1 до " << listSize(list) << "):" << endl;
    for (int i = 0; i < K; i++) {
        cin >> itemNumbers[i];
        itemNumbers[i]--; 
    }
    for (int i = 0; i < K - 1; i++) {
        for (int j = 0; j < K - i - 1; j++) {
            if (itemNumbers[j] < itemNumbers[j + 1]) {
                swap(itemNumbers[j], itemNumbers[j + 1]);
            }
        }
    }

    for (int i = 0; i < K; i++) {
        DeleteElByIndex(list, itemNumbers[i]);
    }
    printList(list);
    cout << "Теперь добавим " << K << " новых элементов на места удалённых." << endl;

    int* insertPositions = new int[K];
    string* newElements = new string[K];

    for (int i = 0; i < K; i++) {
        cout << "Введите позицию для вставки " << (i + 1) << "-го нового элемента: ";
        cin >> insertPositions[i];

        cout << "Введите строку для " << (i + 1) << "-го нового элемента: ";
        cin >> newElements[i];
    }
    for (int i = 0; i < K; i++) {
        InsertItem(list, newElements[i], insertPositions[i]);
    }
    cout << "Список после добавления новых элементов:" << endl;
    printList(list);
    delete[] itemNumbers;
    delete[] insertPositions;
    delete[] newElements;

    return 0;
}
