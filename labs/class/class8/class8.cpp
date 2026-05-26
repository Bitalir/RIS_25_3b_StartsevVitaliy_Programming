#include <iostream>
#include <string>
using namespace std;

class Print {
protected:
    string title;
    string author;
public:
    Print() : title(""), author("") {}
    Print(const string& t, const string& a) : title(t), author(a) {}
    virtual ~Print() {}

    virtual void input() = 0;
    virtual void output() const = 0;

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    void setTitle(const string& t) { title = t; }
    void setAuthor(const string& a) { author = a; }

    Print& operator=(const Print& other) {
        if (this != &other) {
            title = other.title;
            author = other.author;
        }
        return *this;
    }
};

class Book : public Print {
private:
    int pages;
    string publisher;
public:
    Book() : Print(), pages(0), publisher("") {}
    Book(const string& t, const string& a, int p, const string& pub)
        : Print(t, a), pages(p), publisher(pub) {
    }
    ~Book() {}

    void input() override {
        cout << "Введите название книги: ";
        getline(cin, title);
        cout << "Введите автора: ";
        getline(cin, author);
        cout << "Введите количество страниц: ";
        cin >> pages;
        cin.ignore();
        cout << "Введите издательство: ";
        getline(cin, publisher);
    }

    void output() const override {
        cout << "Книга: " << title << ", автор: " << author
            << ", страниц: " << pages << ", издательство: " << publisher << endl;
    }

    int getPages() const { return pages; }
    string getPublisher() const { return publisher; }
    void setPages(int p) { pages = p; }
    void setPublisher(const string& p) { publisher = p; }
};

struct TreeNode {
    Print* data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(Print* obj) : data(obj), left(nullptr), right(nullptr) {}
};

class TreeGroup {
protected:
    TreeNode* root;
    int size;

    void addNode(TreeNode*& node, Print* obj) {
        if (node == nullptr) {
            node = new TreeNode(obj);
            ++size;
        }
        else {
            if (obj->getTitle() < node->data->getTitle())
                addNode(node->left, obj);
            else
                addNode(node->right, obj);
        }
    }

    TreeNode* findMin(TreeNode* node) const {
        while (node && node->left) node = node->left;
        return node;
    }

    TreeNode* removeNode(TreeNode* node, const string& title) {
        if (node == nullptr) return nullptr;
        if (title < node->data->getTitle())
            node->left = removeNode(node->left, title);
        else if (title > node->data->getTitle())
            node->right = removeNode(node->right, title);
        else {
            if (node->left == nullptr) {
                TreeNode* rightChild = node->right;
                delete node->data;
                delete node;
                --size;
                return rightChild;
            }
            else if (node->right == nullptr) {
                TreeNode* leftChild = node->left;
                delete node->data;
                delete node;
                --size;
                return leftChild;
            }
            else {
                TreeNode* minNode = findMin(node->right);
                Book* newData = new Book(*dynamic_cast<Book*>(minNode->data));
                delete node->data;
                node->data = newData;
                node->right = removeNode(node->right, minNode->data->getTitle());
            }
        }
        return node;
    }

    void deleteTree(TreeNode* node) {
        if (node) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node->data;
            delete node;
        }
    }

    void inorderDisplay(TreeNode* node, int& counter) const {
        if (node) {
            inorderDisplay(node->left, counter);
            cout << ++counter << ". ";
            node->data->output();
            inorderDisplay(node->right, counter);
        }
    }

    bool findTitleByIndex(TreeNode* node, int target, int& current, string& result) const {
        if (!node) return false;
        if (findTitleByIndex(node->left, target, current, result))
            return true;
        ++current;
        if (current == target) {
            result = node->data->getTitle();
            return true;
        }
        return findTitleByIndex(node->right, target, current, result);
    }

public:
    TreeGroup() : root(nullptr), size(0) {}
    ~TreeGroup() {
        deleteTree(root);
    }

    TreeGroup(const TreeGroup& other) : root(nullptr), size(0) {
        copyTree(root, other.root);
    }

    void copyTree(TreeNode*& dest, TreeNode* src) {
        if (src) {
            dest = new TreeNode(new Book(*dynamic_cast<Book*>(src->data)));
            copyTree(dest->left, src->left);
            copyTree(dest->right, src->right);
        }
    }

    TreeGroup& operator=(const TreeGroup& other) {
        if (this != &other) {
            deleteTree(root);
            root = nullptr;
            size = 0;
            copyTree(root, other.root);
        }
        return *this;
    }

    void add(Print* obj) {
        addNode(root, obj);
    }

    void remove(const string& title) {
        root = removeNode(root, title);
    }

    void display() const {
        if (!root) {
            cout << "Группа пуста." << endl;
            return;
        }
        int counter = 0;
        inorderDisplay(root, counter);
    }

    void printTitleByIndex(int k) const {
        if (k < 1 || k > size) {
            cout << "Неверный номер элемента." << endl;
            return;
        }
        string result;
        int current = 0;
        if (findTitleByIndex(root, k, current, result)) {
            cout << "Название элемента " << k << ": " << result << endl;
        }
    }

    int getSize() const { return size; }
    operator int() const { return size; }
};

class Dialog : public TreeGroup {
public:
    void run() {
        char command;
        cout << "========== Система управления группой (дерево) ==========" << endl;
        cout << "Команды:" << endl;
        cout << "  m <количество>  - создать группу из N элементов" << endl;
        cout << "  +               - добавить элемент" << endl;
        cout << "  -               - удалить элемент (по названию)" << endl;
        cout << "  s               - вывести информацию обо всех элементах" << endl;
        cout << "  z <k>           - вывести название элемента с номером k" << endl;
        cout << "  q               - выход" << endl;
        cout << "=========================================================" << endl;

        while (true) {
            cout << "\nВведите команду: ";
            cin >> command;
            cin.ignore();

            if (command == 'm') {
                int n;
                cin >> n;
                cin.ignore();
                deleteTree(root);
                root = nullptr;
                size = 0;

                for (int i = 0; i < n; ++i) {
                    cout << "\nВвод данных для элемента " << i + 1 << ":" << endl;
                    Book* book = new Book();
                    book->input();
                    add(book);
                }
                cout << "Создана группа из " << size << " элементов." << endl;
            }
            else if (command == '+') {
                cout << "Ввод данных новой книги:" << endl;
                Book* book = new Book();
                book->input();
                add(book);
                cout << "Элемент добавлен. Размер группы: " << getSize() << endl;
            }
            else if (command == '-') {
                if (getSize() == 0) {
                    cout << "Группа пуста, нечего удалять." << endl;
                    continue;
                }
                string title;
                cout << "Введите название книги для удаления: ";
                getline(cin, title);
                remove(title);
                cout << "После удаления размер группы: " << getSize() << endl;
            }
            else if (command == 's') {
                display();
            }
            else if (command == 'z') {
                int k;
                cin >> k;
                cin.ignore();
                printTitleByIndex(k);
            }
            else if (command == 'q') {
                cout << "Завершение работы." << endl;
                break;
            }
            else {
                cout << "Неизвестная команда. Попробуйте снова." << endl;
            }
        }
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    Dialog dlg;
    dlg.run();
    return 0;
}