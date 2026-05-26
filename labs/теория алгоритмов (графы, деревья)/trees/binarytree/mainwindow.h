#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "binarytree.h"
#include "treewidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_insertButton_clicked();
    void on_deleteButton_clicked();
    void on_findButton_clicked();
    void on_countButton_clicked();
    void on_traverseButton_clicked();
    void on_balanceButton_clicked();
    void on_verticalPrintButton_clicked();
    void on_horizontalPrintButton_clicked();

private:
    Ui::MainWindow *ui;
    BinaryTree tree;
    void updateTreeDisplay();
};

#endif // MAINWINDOW_H
