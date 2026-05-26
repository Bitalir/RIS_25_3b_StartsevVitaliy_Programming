#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->treeWidget->setTree(&tree);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateTreeDisplay() {
    ui->treeWidget->update();   // перерисовка дерева
}

void MainWindow::on_insertButton_clicked() {
    QString text = ui->keyLineEdit->text();
    if (text.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите символ");
        return;
    }
    char key = text.at(0).toLatin1();
    tree.insert(key);
    updateTreeDisplay();
    ui->keyLineEdit->clear();
}

void MainWindow::on_deleteButton_clicked() {
    QString text = ui->keyLineEdit->text();
    if (text.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите символ");
        return;
    }
    char key = text.at(0).toLatin1();
    tree.remove(key);
    updateTreeDisplay();
    ui->keyLineEdit->clear();
}

void MainWindow::on_findButton_clicked() {
    QString text = ui->keyLineEdit->text();
    if (text.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите символ");
        return;
    }
    char key = text.at(0).toLatin1();
    bool found = tree.search(key);
    if (found) {
        QMessageBox::information(this, "Результат", "Элемент найден");
    } else {
        QMessageBox::information(this, "Результат", "Элемент не найден");
    }
}

void MainWindow::on_countButton_clicked() {
    QString text = ui->keyLineEdit->text();
    if (text.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите символ");
        return;
    }
    char key = text.at(0).toLatin1();
    int count = tree.countKey(key);
    QMessageBox::information(this, "Результат", QString("Количество элементов с ключом '%1': %2").arg(key).arg(count));
}

void MainWindow::on_traverseButton_clicked() {
    int index = ui->traverseComboBox->currentIndex();
    QString result;
    if (index == 0) {
        result = tree.preorder();
    } else if (index == 1) {
        result = tree.inorder();
    } else {
        result = tree.postorder();
    }
    ui->textEdit->setPlainText(result);
}

void MainWindow::on_balanceButton_clicked() {
    tree.balance();
    updateTreeDisplay();
    QMessageBox::information(this, "Балансировка", "Дерево сбалансировано");
}

void MainWindow::on_verticalPrintButton_clicked() {
    QString result = tree.verticalPrint();
    ui->textEdit->setPlainText(result);
}

void MainWindow::on_horizontalPrintButton_clicked() {
    QString result = tree.horizontalPrint();
    ui->textEdit->setPlainText(result);
}
