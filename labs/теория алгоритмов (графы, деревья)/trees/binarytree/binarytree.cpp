#include "binarytree.h"
#include <QQueue>

BinaryTree::BinaryTree() : root(nullptr) {}

BinaryTree::~BinaryTree() {
    clearTree(root);
}

void BinaryTree::clearTree(Node* node) {
    if (node != nullptr) {
        clearTree(node->left);
        clearTree(node->right);
        delete node;
    }
}

Node* BinaryTree::insertRec(Node* node, char key) {
    if (node == nullptr) {
        return new Node(key);
    }
    if (key < node->key) {
        node->left = insertRec(node->left, key);
    } else {
        // Дубликаты идут в правое поддерево
        node->right = insertRec(node->right, key);
    }
    return node;
}

void BinaryTree::insert(char key) {
    root = insertRec(root, key);
}

Node* BinaryTree::findMin(Node* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

Node* BinaryTree::deleteRec(Node* node, char key) {
    if (node == nullptr) {
        return nullptr;
    }
    if (key < node->key) {
        node->left = deleteRec(node->left, key);
    } else if (key > node->key) {
        node->right = deleteRec(node->right, key);
    } else {
        // Узел найден
        if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            return temp;
        }
        // Два потомка – ищем минимальный в правом поддереве
        Node* temp = findMin(node->right);
        node->key = temp->key;
        node->right = deleteRec(node->right, temp->key);
    }
    return node;
}

void BinaryTree::remove(char key) {
    root = deleteRec(root, key);
}

bool BinaryTree::searchRec(Node* node, char key) {
    if (node == nullptr) {
        return false;
    }
    if (key == node->key) {
        return true;
    } else if (key < node->key) {
        return searchRec(node->left, key);
    } else {
        return searchRec(node->right, key);
    }
}

bool BinaryTree::search(char key) {
    return searchRec(root, key);
}

int BinaryTree::countKeyRec(Node* node, char key) {
    if (node == nullptr) {
        return 0;
    }
    int count = 0;
    if (node->key == key) {
        count = 1;
    }
    return count + countKeyRec(node->left, key) + countKeyRec(node->right, key);
}

int BinaryTree::countKey(char key) {
    return countKeyRec(root, key);
}

void BinaryTree::preorderRec(Node* node, QString &result) {
    if (node != nullptr) {
        result += node->key;
        result += " ";
        preorderRec(node->left, result);
        preorderRec(node->right, result);
    }
}

QString BinaryTree::preorder() {
    QString result;
    preorderRec(root, result);
    return result.trimmed();
}

void BinaryTree::inorderRec(Node* node, QString &result) {
    if (node != nullptr) {
        inorderRec(node->left, result);
        result += node->key;
        result += " ";
        inorderRec(node->right, result);
    }
}

QString BinaryTree::inorder() {
    QString result;
    inorderRec(root, result);
    return result.trimmed();
}

void BinaryTree::postorderRec(Node* node, QString &result) {
    if (node != nullptr) {
        postorderRec(node->left, result);
        postorderRec(node->right, result);
        result += node->key;
        result += " ";
    }
}

QString BinaryTree::postorder() {
    QString result;
    postorderRec(root, result);
    return result.trimmed();
}

void BinaryTree::storeInorder(Node* node, QVector<char> &nodes) {
    if (node != nullptr) {
        storeInorder(node->left, nodes);
        nodes.push_back(node->key);
        storeInorder(node->right, nodes);
    }
}

Node* BinaryTree::buildBalanced(QVector<char> &nodes, int start, int end) {
    if (start > end) {
        return nullptr;
    }
    int mid = (start + end) / 2;
    Node* node = new Node(nodes[mid]);
    node->left = buildBalanced(nodes, start, mid - 1);
    node->right = buildBalanced(nodes, mid + 1, end);
    return node;
}

void BinaryTree::balance() {
    QVector<char> nodes;
    storeInorder(root, nodes);
    clearTree(root);
    root = buildBalanced(nodes, 0, nodes.size() - 1);
}

int BinaryTree::getHeight(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    int leftH = getHeight(node->left);
    int rightH = getHeight(node->right);
    if (leftH > rightH) {
        return leftH + 1;
    } else {
        return rightH + 1;
    }
}

// Вертикальная печать (по уровням)
QString BinaryTree::verticalPrint() {
    if (root == nullptr) {
        return "Дерево пусто";
    }
    int h = getHeight(root);
    QVector<QVector<char>> levels(h);
    struct QueueItem {
        Node* node;
        int level;
    };
    QQueue<QueueItem> queue;
    if (root != nullptr) {
        queue.enqueue({root, 0});
    }
    while (!queue.isEmpty()) {
        QueueItem item = queue.dequeue();
        levels[item.level].append(item.node->key);
        if (item.node->left != nullptr) {
            queue.enqueue({item.node->left, item.level + 1});
        }
        if (item.node->right != nullptr) {
            queue.enqueue({item.node->right, item.level + 1});
        }
    }
    QString result;
    for (int i = 0; i < levels.size(); ++i) {
        result += "Уровень " + QString::number(i) + ": ";
        for (int j = 0; j < levels[i].size(); ++j) {
            result += levels[i][j];
            result += " ";
        }
        result += "\n";
    }
    return result;
}

// Горизонтальная печать (повёрнутое дерево, корень справа)
void BinaryTree::horizontalPrintRec(Node* node, int level, QVector<QString> &lines) {
    if (node == nullptr) return;
    horizontalPrintRec(node->right, level + 1, lines);
    QString line;
    for (int i = 0; i < level; ++i) {
        line += "    ";
    }
    line += node->key;
    lines.append(line);
    horizontalPrintRec(node->left, level + 1, lines);
}

QString BinaryTree::horizontalPrint() {
    if (root == nullptr) {
        return "Дерево пусто";
    }
    QVector<QString> lines;
    horizontalPrintRec(root, 0, lines);
    QString result;
    for (int i = 0; i < lines.size(); ++i) {
        result += lines[i] + "\n";
    }
    return result;
}
