#ifndef TREEWIDGET_H
#define TREEWIDGET_H

#include <QWidget>
#include "binarytree.h"

class TreeWidget : public QWidget
{
    Q_OBJECT
private:
    BinaryTree* tree;
    void drawNode(QPainter& painter, Node* node, int x, int y, int xOffset, int level);
public:
    explicit TreeWidget(QWidget *parent = nullptr);
    void setTree(BinaryTree* newTree);
protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // TREEWIDGET_H
