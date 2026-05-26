#include "treewidget.h"
#include <QPainter>

TreeWidget::TreeWidget(QWidget *parent) : QWidget(parent), tree(nullptr) {}

void TreeWidget::setTree(BinaryTree* newTree) {
    tree = newTree;
    update();   // перерисовать
}

void TreeWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    if (tree == nullptr || tree->getRoot() == nullptr) {
        painter.drawText(rect(), Qt::AlignCenter, "Дерево пусто");
        return;
    }
    int width = this->width();
    int startX = width / 2;
    int startY = 50;
    int xOffset = width / 4;
    drawNode(painter, tree->getRoot(), startX, startY, xOffset, 0);
}

void TreeWidget::drawNode(QPainter& painter, Node* node, int x, int y, int xOffset, int level) {
    if (node == nullptr) return;
    // Рисуем кружок
    painter.setBrush(Qt::lightGray);
    painter.drawEllipse(x - 15, y - 15, 30, 30);
    painter.drawText(x - 7, y + 5, QString(node->key));
    // Линии к детям
    int childY = y + 60;
    int childXOffset = xOffset / 2;
    if (node->left != nullptr) {
        int leftX = x - xOffset;
        painter.drawLine(x, y + 15, leftX, childY - 15);
        drawNode(painter, node->left, leftX, childY, childXOffset, level + 1);
    }
    if (node->right != nullptr) {
        int rightX = x + xOffset;
        painter.drawLine(x, y + 15, rightX, childY - 15);
        drawNode(painter, node->right, rightX, childY, childXOffset, level + 1);
    }
}
