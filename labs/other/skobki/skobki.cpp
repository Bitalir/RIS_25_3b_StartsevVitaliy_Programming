#include <iostream>
#include <string>
#include <clocale>

using namespace std;

struct Node {
    char data;
    Node* next;

    Node(char value) {
        data = value;
        next = nullptr;
    }
};

class Stack {
private:
    Node* top;
    int size;

public:
    Stack() {
        top = nullptr;
        size = 0;
    }

    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    void push(char value) {
        Node* newNode = new Node(value);
        newNode->next = top;
        top = newNode;
        size++;
    }

    void pop() {
        if (isEmpty()) return;
        Node* temp = top;
        top = top->next;
        delete temp;
        size--;
    }

    char getTop() {
        if (isEmpty()) return '\0';
        return top->data;
    }

    bool isEmpty() {
        return top == nullptr;
    }

    int getSize() {
        return size;
    }
};

bool isOpeningBracket(char c) {
    return c == '(' || c == '[' || c == '{';
}

char getMatchingOpeningBracket(char closing) {
    switch (closing) {
    case ')': return '(';
    case ']': return '[';
    case '}': return '{';
    default: return '\0';
    }
}

bool checkBrackets(const string& str) {
    Stack stack;

    for (int i = 0; i < str.length(); i++) {
        char currentChar = str[i];

        if (currentChar == ' ') continue;

        if (isOpeningBracket(currentChar)) {
            stack.push(currentChar);
        }
        else if (currentChar == ')' || currentChar == ']' || currentChar == '}') {
            if (stack.isEmpty()) {
                return false;
            }

            if (stack.getTop() != getMatchingOpeningBracket(currentChar)) {
                return false;
            }

            stack.pop();
        }
        else {
            cout << "Ошибка: обнаружен недопустимый символ '" << currentChar << "'" << endl;
            return false;
        }
    }

    return stack.isEmpty();
}

int main() {
    setlocale(LC_ALL, "RU");
    string input;

    cout << "Введите последовательность скобок: ";
    getline(cin, input);

    if (checkBrackets(input)) {
        cout << "Скобки расставлены ВЕРНО!" << endl;
    }
    else {
        cout << "Скобки расставлены НЕВЕРНО!" << endl;
    }

    return 0;
}