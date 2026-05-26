#include <iostream>
#include <clocale>
using namespace std;

struct Node {
	Node* prev = nullptr;
	Node* next = nullptr;
	int data;
};

class Iterator {
	friend class List;
public:
	Iterator() {
		elem = nullptr;
	}
	Iterator(const Iterator& it) {
		elem = it.elem;
	}
	Iterator& operator=(const Iterator& a) {
		elem = a.elem;
		return *this;
	}
	bool operator==(const Iterator& it) {
		return elem == it.elem;
	}
	bool operator!=(const Iterator& it) {
		return elem != it.elem;
	}
	Iterator& operator++() {
		elem = elem->next;
		return *this;
	}
	Iterator& operator--() {
		elem = elem->prev;
		return *this;
	}
	Iterator& operator+(const int& a) {
		for (int i = 0; i < a; ++i) {
			elem = elem->next;
		}
		return *this;
	}
	Iterator& operator-(const int& a) {
		for (int i = 0; i < a; ++i) {
			elem = elem->prev;
		}
		return *this;
	}
	int& operator*()const {
		return (elem->data);
	}
private:
	Node* elem;
};

class List {
private:
	int size;
	Node* head = nullptr;
	Node* tail = nullptr;
	Iterator beg;
	Iterator end;
public:
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
	int& operator()();
	List operator*(const int& n);
	friend ostream& operator<<(ostream& out, const List& a);
	friend istream& operator>>(istream& in, const List& a);
	Iterator first() {
		return beg;
	}
	Iterator last() {
		return end;
	}
};

List::List(int s, int k) {
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
	beg.elem = head;
	end.elem = tail->next;
}

List::List(const List& a) {
	Node* node = a.head;
	while (node != nullptr) {
		pushback(node->data);
		node = node->next;
	}
	beg = a.beg;
	end = a.end;
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
	Node* newNode = new Node;
	newNode->data = data;
	if (head == nullptr) {
		head = newNode;
		tail = newNode;
		++size;
		end.elem = tail->next;
	}
	else {
		tail->next = newNode;
		newNode->prev = tail;
		tail = newNode;
		++size;
		end.elem = tail->next;
	}
}

void List::pushfront(int data) {
	Node* newNode = new Node;
	newNode->data = data;
	if (head == nullptr) {
		head = newNode;
		tail = newNode;
		++size;
		beg.elem = head;
	}
	else {
		head->prev = newNode;
		newNode->next = head;
		head = newNode;
		++size;
		beg.elem = head;
	}
}

int List::front() {
	return head->data;
}

int List::back() {
	return tail->data;
}

void List::popback() {
	if (head != nullptr) {
		Node* currentNode = tail;
		tail = currentNode->prev;
		delete currentNode;
		tail->next = nullptr;
		--size;
		end.elem = tail->next;
	}
}

void List::popfront() {
	if (head != nullptr) {
		Node* currnetNode = head;
		head = currnetNode->next;
		delete currnetNode;
		head->prev = nullptr;
		--size;
		beg.elem = head;
	}
}

bool List::empty() {
	return size == 0;
}

int& List::operator()() {
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
		--size;
	}
	Node* currentNode = a.head;
	while (currentNode != nullptr) {
		pushback(currentNode->data);
		currentNode = currentNode->next;
	}
	beg = a.beg;
	end = a.end;
	return *this;
}

int& List::operator[](int index) {
	if (index < size and index >= 0) {
		Node* current = head;
		for (int i = 0; i != index; ++i) {
			current = current->next;
		}
		return current->data;
	}
	else {
		if (index >= size) {
			cout << "Ошибка! Индекс больше или равен размеру списка" << endl;
			exit(0);
		}
		else {
			cout << "Ошибка! Иднекс отрицательный" << endl;
			exit(0);
		}
	}
}

List List::operator*(const int& n) {
	List temp(size);
	for (int i = 0; i < size; ++i) {
		temp[i] = (*this)[i] * n;
	}
	return temp;
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

istream& operator>>(istream& in, const List& a) {
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
	List a(10);
	cout << endl << a << endl;
	cout << "Первый элемент списка a : " << *(a.first()) << " / Последний элемент списка a : " << a.back() << endl;
	for (int i = 0; i < a(); ++i) {
		a[i] = i * i - 24 + i;
	}
	cout << endl << a << endl;
	cout << "Первый элемент списка a : " << *(a.first()) << " / Последний элемент списка a : " << a.back() << endl;
	List b(a);
	cout << endl << b << endl;
	cout << "Первый элемент списка b : " << *(b.first()) << " / Последний элемент списка b : " << b.back() << endl;
	b.pushback(34), b.popfront();
	cout << endl << b << endl;
	cout << "Первый элемент списка b : " << *(b.first()) << " / Последний элемент списка b : " << b.back() << endl;
	List c(6);
	cin >> c;
	cout << endl << c << endl;
	int x;
	cout << "Введите число, на которое нужно умножить все эл-ты списка: ";
	cin >> x;
	List d = c * x;
	cout << d << endl;
	cout << "Первый элемент списка d : " << *(d.first()) << " / Последний элемент списка d : " << d.back() << endl;
	cout << "Вывод списка с с помощью итераторов: ";
	cout << endl;
	Iterator it = d.first();
	cout << "Первый элемент списка d: " << *it << endl;
	++it;
	cout << "Второй элемент списка d: " << *it << endl;
	it = it + 4;
	cout << "Шестой элемент списка d: " << *it << endl;
	it = it - 2;
	cout << "Четвёртый элемент списка d: " << *it << endl;
	for (Iterator iter = b.first(); iter != b.last(); ++iter) {
		cout << *iter << ' ';
	}
	return 0;
}