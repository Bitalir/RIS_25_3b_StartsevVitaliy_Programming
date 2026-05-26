#include <iostream>
#include <clocale>
#include <string>

using namespace std;

struct Node {
    Node* prev = nullptr;
    Node* next = nullptr;
    int data;
};

class BaseError {
public:
    virtual void what() const = 0;
    virtual ~BaseError() {}
};

class IndexError : public BaseError {
protected:
    string msg;
public:
    IndexError(const string& s = "Index error") : msg(s) {}
    void what() const override { cout << msg << endl; }
};

class NegativeIndexError : public IndexError {
public:
    NegativeIndexError() : IndexError("Ошибка! Индекс отрицательный") {}
};

class OutOfRangeError : public IndexError {
public:
    OutOfRangeError() : IndexError("Ошибка! Индекс больше или равен размеру списка") {}
};

class SizeError : public BaseError {
protected:
    string msg;
public:
    SizeError(const string& s = "Size error") : msg(s) {}
    void what() const override { cout << msg << endl; }
};

class MaxSizeError : public SizeError {
public:
    MaxSizeError() : SizeError("Ошибка! Превышен максимальный размер списка (30)") {}
};

class EmptyListError : public SizeError {
public:
    EmptyListError() : SizeError("Ошибка! Попытка удаления из пустого списка") {}
};

class ShiftLeftError : public IndexError {
public:
    ShiftLeftError() : IndexError("Ошибка! Неверный номер элемента при переходе влево (должен быть от 1 до размера)") {}
};

class List {
private:
    int size;
    Node* head = nullptr;
    Node* tail = nullptr;
    static const int MAX_SIZE = 30;

public:
    List() : size(0), head(nullptr), tail(nullptr) {}
    List(int s, int k = 0);
    List(const List& a);
    ~List();
    int front();
    int back();
    void pushback(int data);
    void pushfront(int data);
    void popback();
    void popfront();
    bool empty();
    List& operator=(const List& a);
    int& operator[](int index);
    int operator()();
    List operator*(const int& n);
    int& operator-(int n);          

    friend ostream& operator<<(ostream& out, const List& a);
    friend istream& operator>>(istream& in, List& a);
};

List::List(int s, int k) {
    if (s > MAX_SIZE) throw MaxSizeError();
    if (s < 0) throw SizeError("Отрицательный размер списка");

    size = s;
    Node* node = new Node;
    node->data = k;
    head = node;
    tail = node;
    for (int i = 0; i < size - 1; ++i) {
        Node* node = new Node;
        node->data = k + 2 + i;
        tail->next = node;
        node->prev = tail;
        tail = node;
    }
    tail->next = nullptr;
}

List::List(const List& a) : size(0), head(nullptr), tail(nullptr) {
    Node* node = a.head;
    while (node != nullptr) {
        pushback(node->data);
        node = node->next;
    }
}

List::~List() {
    Node* currentNode = head;
    while (currentNode != nullptr) {
        head = currentNode->next;
        delete currentNode;
        currentNode = head;
    }
}

void List::pushback(int data) {
    if (size >= MAX_SIZE) throw MaxSizeError();

    Node* newNode = new Node;
    newNode->data = data;
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
        ++size;
    }
    else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
        ++size;
    }
}

void List::pushfront(int data) {
    if (size >= MAX_SIZE) throw MaxSizeError();

    Node* newNode = new Node;
    newNode->data = data;
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
        ++size;
    }
    else {
        head->prev = newNode;
        newNode->next = head;
        head = newNode;
        ++size;
    }
}

int List::front() {
    if (!head) throw EmptyListError();  
    return head->data;
}

int List::back() {
    if (!tail) throw EmptyListError();   
    return tail->data;
}

void List::popback() {
    if (head == nullptr) throw EmptyListError();   
    if (head == tail) {
        delete head;
        head = tail = nullptr;
        --size;
        return;
    }
    Node* currentNode = tail;
    tail = currentNode->prev;
    delete currentNode;
    tail->next = nullptr;
    --size;
}

void List::popfront() {
    if (head == nullptr) throw EmptyListError(); 
    if (head == tail) {
        delete head;
        head = tail = nullptr;
        --size;
        return;
    }
    Node* currnetNode = head;
    head = currnetNode->next;
    delete currnetNode;
    head->prev = nullptr;
    --size;
}

bool List::empty() {
    return size == 0;
}

int List::operator()() {  
    return size;
}

List& List::operator=(const List& a) {
    cout << "Оператор присваивания" << endl;
    if (this == &a) {
        return *this;
    }
    Node* node = head;
    while (node != nullptr) {
        head = node->next;
        delete node;
        node = head;
    }
    head = tail = nullptr;
    size = 0;
    Node* currentNode = a.head;
    while (currentNode != nullptr) {
        pushback(currentNode->data);
        currentNode = currentNode->next;
    }
    return *this;
}

int& List::operator[](int index) {
    if (index < 0) throw NegativeIndexError();        
    if (index >= size) throw OutOfRangeError();       
    Node* current = head;
    for (int i = 0; i != index; ++i) {
        current = current->next;
    }
    return current->data;
}

List List::operator*(const int& n) {
    List temp(size);
    for (int i = 0; i < size; ++i) {
        temp[i] = (*this)[i] * n;
    }
    return temp;
}

int& List::operator-(int n) {
    if (n < 1 || n > size) throw ShiftLeftError();
    return (*this)[size - n]; 
}

ostream& operator<<(ostream& out, const List& a) {
    out << endl << "---Вывод элементов списка---" << endl;
    Node* current = a.head;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    out << endl << "---Вывод элементов списка завершён---" << endl;
    return out;
}

istream& operator>>(istream& in, List& a) { 
    cout << endl << "---Ввод элементов списка---" << endl;
    Node* current = a.head;
    while (current != nullptr) {
        in >> current->data;
        current = current->next;
    }
    cout << endl << "---Ввод элементов списка завершён---" << endl;
    return in;
}

int main() {
    setlocale(LC_ALL, "Rus");

    try {
        List a(5);
        cout << a;
        cout << "Первый элемент: " << a.front() << " / Последний элемент: " << a.back() << endl;

        for (int i = 0; i < a(); ++i)
            a[i] = i * i - 24 + i;
        cout << a;

        List b = a * 3;
        cout << "Список b = a * 3:" << b;

        cout << "Элемент с номером 1 слева (последний): " << (b - 1) << endl;
        cout << "Элемент с номером 2 слева (предпоследний): " << (b - 2) << endl;

        cout << "\nПроверка исключения operator[]:" << endl;
        cout << a[100] << endl;
    }
    catch (const NegativeIndexError& e) {
        cout << "Исключение: "; e.what();
    }
    catch (const OutOfRangeError& e) {
        cout << "Исключение: "; e.what();
    }
    catch (const MaxSizeError& e) {
        cout << "Исключение: "; e.what();
    }
    catch (const EmptyListError& e) {
        cout << "Исключение: "; e.what();
    }
    catch (const ShiftLeftError& e) {
        cout << "Исключение: "; e.what();
    }
    catch (const BaseError& e) {
        cout << "Общее исключение: "; e.what();
    }

    try {
        List emptyList;
        cout << "\nПопытка удалить из пустого списка:" << endl;
        emptyList.popfront();
    }
    catch (const EmptyListError& e) {
        cout << "Исключение: "; e.what();
    }
    try {
        cout << "\nПопытка создать список из 35 элементов:" << endl;
        List tooBig(35);
    }
    catch (const MaxSizeError& e) {
        cout << "Исключение: "; e.what();
    }

    try {
        List c(3);
        c[0] = 10; c[1] = 20; c[2] = 30;
        cout << "\nСписок c: " << c;
        cout << "Попытка перехода к элементу -5: ";
        cout << (c - 5) << endl;
    }
    catch (const ShiftLeftError& e) {
        cout << "Исключение: "; e.what();
    }

    return 0;
}
