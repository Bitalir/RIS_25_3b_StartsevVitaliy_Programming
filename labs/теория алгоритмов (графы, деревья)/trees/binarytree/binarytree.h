#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <QString>
#include <QVector>

// Узел дерева: хранит символ и указатели на левого/правого потомка
struct Node {
    char key;
    Node* left;
    Node* right;
    Node(char k) : key(k), left(nullptr), right(nullptr) {}
};

class BinaryTree
{
private:
    Node* root;                     // корень дерева

    // Вспомогательные рекурсивные методы
    Node* insertRec(Node* node, char key);
    Node* deleteRec(Node* node, char key);
    Node* findMin(Node* node);
    bool searchRec(Node* node, char key);
    int countKeyRec(Node* node, char key);
    void preorderRec(Node* node, QString &result);
    void inorderRec(Node* node, QString &result);
    void postorderRec(Node* node, QString &result);
    void storeInorder(Node* node, QVector<char> &nodes);
    Node* buildBalanced(QVector<char> &nodes, int start, int end);
    void clearTree(Node* node);
    void verticalPrintRec(Node* node, int level, QVector<QString> &lines, QVector<int> &positions);
    void horizontalPrintRec(Node* node, int level, QVector<QString> &lines);
    int getHeight(Node* node);

public:
    BinaryTree();
    ~BinaryTree();

    // Основные операции
    void insert(char key);
    void remove(char key);
    bool search(char key);
    int countKey(char key);

    // Обходы
    QString preorder();
    QString inorder();
    QString postorder();

    // Балансировка
    void balance();

    // Печать
    QString verticalPrint();
    QString horizontalPrint();

    // Доступ к корню (для отрисовки)
    Node* getRoot() { return root; }
};

#endif // BINARYTREE_H
