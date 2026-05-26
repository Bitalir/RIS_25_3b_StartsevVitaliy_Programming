#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QInputDialog>
#include <QGraphicsView>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    graph = new GraphModel();
    graph->setVerticesCount(6);
    // Рёбра по варианту (без 6→1)
    graph->addEdge(0,1,2);
    graph->addEdge(0,5,57);
    graph->addEdge(1,3,8);
    graph->addEdge(1,5,13);
    graph->addEdge(1,2,3);
    graph->addEdge(2,3,5);
    graph->addEdge(3,4,34);
    graph->addEdge(3,5,21);
    graph->addEdge(4,5,45);
    // Ребро 6→1 (18) удалено

    setupUI();
    updateGraphDisplay();
    updateMatrixTable();

    connect(scene, &GraphScene::vertexClicked, this, [this](int id) {
        outputText->append("Выбрана вершина " + QString::number(id+1));
    });
}

MainWindow::~MainWindow() { delete graph; }

void MainWindow::setupUI()
{
    QWidget* central = new QWidget;
    setCentralWidget(central);
    QHBoxLayout* mainLayout = new QHBoxLayout(central);

    scene = new GraphScene(this);
    scene->setGraph(graph);
    view = new QGraphicsView(scene);
    view->setRenderHint(QPainter::Antialiasing);
    view->setMinimumSize(600, 500);
    mainLayout->addWidget(view, 2);

    QWidget* rightPanel = new QWidget;
    QVBoxLayout* rightLayout = new QVBoxLayout(rightPanel);
    mainLayout->addWidget(rightPanel, 1);

    addVertexBtn = new QPushButton("Добавить вершину");
    removeVertexBtn = new QPushButton("Удалить вершину");
    addEdgeBtn = new QPushButton("Добавить ребро");
    removeEdgeBtn = new QPushButton("Удалить ребро");
    editEdgeWeightBtn = new QPushButton("Изменить вес ребра");
    rightLayout->addWidget(addVertexBtn);
    rightLayout->addWidget(removeVertexBtn);
    rightLayout->addWidget(addEdgeBtn);
    rightLayout->addWidget(removeEdgeBtn);
    rightLayout->addWidget(editEdgeWeightBtn);

    QHBoxLayout* fromLayout = new QHBoxLayout;
    fromLabel = new QLabel("От:");
    fromSpin = new QSpinBox;
    fromSpin->setMinimum(1);
    fromLayout->addWidget(fromLabel);
    fromLayout->addWidget(fromSpin);
    rightLayout->addLayout(fromLayout);

    QHBoxLayout* toLayout = new QHBoxLayout;
    toLabel = new QLabel("До:");
    toSpin = new QSpinBox;
    toSpin->setMinimum(1);
    toLayout->addWidget(toLabel);
    toLayout->addWidget(toSpin);
    rightLayout->addLayout(toLayout);

    QHBoxLayout* weightLayout = new QHBoxLayout;
    weightLabel = new QLabel("Вес:");
    weightSpin = new QSpinBox;
    weightSpin->setMinimum(1);
    weightSpin->setMaximum(999);
    weightLayout->addWidget(weightLabel);
    weightLayout->addWidget(weightSpin);
    rightLayout->addLayout(weightLayout);

    matrixTable = new QTableWidget;
    matrixTable->setMaximumHeight(250);
    rightLayout->addWidget(new QLabel("Матрица смежности:"));
    rightLayout->addWidget(matrixTable);
    updateMatrixBtn = new QPushButton("Обновить по матрице");
    rightLayout->addWidget(updateMatrixBtn);

    bfsBtn = new QPushButton("BFS (обход в ширину)");
    dfsBtn = new QPushButton("DFS (обход в глубину)");
    dijkstraBtn = new QPushButton("Дейкстра (с вершины 3)");
    floydBtn = new QPushButton("Флойд (все пары)");
    rightLayout->addWidget(bfsBtn);
    rightLayout->addWidget(dfsBtn);
    rightLayout->addWidget(dijkstraBtn);
    rightLayout->addWidget(floydBtn);

    outputText = new QTextEdit;
    outputText->setReadOnly(true);
    outputText->setMaximumHeight(150);
    rightLayout->addWidget(new QLabel("Результаты:"));
    rightLayout->addWidget(outputText);

    connect(addVertexBtn, &QPushButton::clicked, this, &MainWindow::onAddVertex);
    connect(removeVertexBtn, &QPushButton::clicked, this, &MainWindow::onRemoveVertex);
    connect(addEdgeBtn, &QPushButton::clicked, this, &MainWindow::onAddEdge);
    connect(removeEdgeBtn, &QPushButton::clicked, this, &MainWindow::onRemoveEdge);
    connect(editEdgeWeightBtn, &QPushButton::clicked, this, &MainWindow::onEditEdgeWeight);
    connect(updateMatrixBtn, &QPushButton::clicked, this, &MainWindow::onUpdateMatrix);
    connect(bfsBtn, &QPushButton::clicked, this, &MainWindow::onBFS);
    connect(dfsBtn, &QPushButton::clicked, this, &MainWindow::onDFS);
    connect(dijkstraBtn, &QPushButton::clicked, this, &MainWindow::onDijkstra);
    connect(floydBtn, &QPushButton::clicked, this, &MainWindow::onFloyd);
    connect(scene, &GraphScene::animationFinished, this, &MainWindow::onAnimationFinished);
}

void MainWindow::updateGraphDisplay()
{
    scene->setGraph(graph);
    int n = graph->verticesCount();
    fromSpin->setMaximum(n);
    toSpin->setMaximum(n);
    if (n > 0) { fromSpin->setValue(1); toSpin->setValue(1); }
}

void MainWindow::updateMatrixTable()
{
    int n = graph->verticesCount();
    matrixTable->clear();
    matrixTable->setRowCount(n);
    matrixTable->setColumnCount(n);
    for (int i = 0; i < n; ++i) {
        matrixTable->setVerticalHeaderItem(i, new QTableWidgetItem(QString::number(i+1)));
        matrixTable->setHorizontalHeaderItem(i, new QTableWidgetItem(QString::number(i+1)));
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int w = graph->getEdgeWeight(i, j);
            QTableWidgetItem* item = new QTableWidgetItem;
            item->setText(w == INF ? "-" : QString::number(w));
            matrixTable->setItem(i, j, item);
        }
    }
    matrixTable->resizeColumnsToContents();
}

void MainWindow::onAddVertex()
{
    graph->addVertex();
    updateGraphDisplay();
    updateMatrixTable();
    outputText->append("Добавлена новая вершина.");
}

void MainWindow::onRemoveVertex()
{
    int n = graph->verticesCount();
    if (n == 0) return;
    bool ok;
    int idx = QInputDialog::getInt(this, "Удалить вершину", "Номер (1.."+QString::number(n)+"):", 1, 1, n, 1, &ok);
    if (ok) {
        graph->removeVertex(idx-1);
        updateGraphDisplay();
        updateMatrixTable();
        outputText->append("Вершина " + QString::number(idx) + " удалена.");
    }
}

void MainWindow::onAddEdge()
{
    int from = fromSpin->value()-1, to = toSpin->value()-1, w = weightSpin->value();
    if (from<0 || from>=graph->verticesCount() || to<0 || to>=graph->verticesCount()) {
        QMessageBox::warning(this, "Ошибка", "Неверные номера вершин");
        return;
    }
    graph->addEdge(from, to, w);
    scene->addEdgeItem(from, to, w);
    updateMatrixTable();
    outputText->append(QString("Добавлено ребро %1→%2 вес %3").arg(from+1).arg(to+1).arg(w));
}

void MainWindow::onRemoveEdge()
{
    int from = fromSpin->value()-1, to = toSpin->value()-1;
    if (from<0 || from>=graph->verticesCount() || to<0 || to>=graph->verticesCount()) {
        QMessageBox::warning(this, "Ошибка", "Неверные номера вершин");
        return;
    }
    if (graph->getEdgeWeight(from, to) == INF) {
        QMessageBox::information(this, "Информация", "Ребра не существует");
        return;
    }
    graph->removeEdge(from, to);
    scene->removeEdgeItem(from, to);
    updateMatrixTable();
    outputText->append(QString("Удалено ребро %1→%2").arg(from+1).arg(to+1));
}

void MainWindow::onEditEdgeWeight()
{
    int from = fromSpin->value()-1, to = toSpin->value()-1, w = weightSpin->value();
    if (from<0 || from>=graph->verticesCount() || to<0 || to>=graph->verticesCount()) {
        QMessageBox::warning(this, "Ошибка", "Неверные номера вершин");
        return;
    }
    bool existed = (graph->getEdgeWeight(from, to) != INF);
    graph->setEdgeWeight(from, to, w);
    if (existed) {
        scene->updateEdgeWeight(from, to, w);
        outputText->append(QString("Вес ребра %1→%2 изменён на %3").arg(from+1).arg(to+1).arg(w));
    } else {
        scene->addEdgeItem(from, to, w);
        outputText->append(QString("Добавлено ребро %1→%2 весом %3").arg(from+1).arg(to+1).arg(w));
    }
    updateMatrixTable();
}

void MainWindow::onUpdateMatrix()
{
    int n = graph->verticesCount();
    for (int i=0; i<n; ++i) {
        for (int j=0; j<n; ++j) {
            QTableWidgetItem* item = matrixTable->item(i,j);
            if (item) {
                QString txt = item->text();
                if (txt=="-" || txt.isEmpty()) {
                    if (graph->getEdgeWeight(i,j) != INF) {
                        graph->removeEdge(i,j);
                        scene->removeEdgeItem(i,j);
                    }
                } else {
                    bool ok; int w = txt.toInt(&ok);
                    if (ok && w>0) {
                        graph->addEdge(i,j,w);
                        scene->updateEdgeWeight(i,j,w);
                    } else {
                        graph->removeEdge(i,j);
                        scene->removeEdgeItem(i,j);
                    }
                }
            }
        }
    }
    updateGraphDisplay();
    outputText->append("Матрица смежности обновлена.");
}

void MainWindow::onBFS()
{
    if (graph->verticesCount()==0) { outputText->append("Граф пуст"); return; }
    bool ok;
    int start = QInputDialog::getInt(this,"BFS","Начальная вершина (1.."+QString::number(graph->verticesCount())+"):",1,1,graph->verticesCount(),1,&ok);
    if (!ok) return;
    start--;
    QVector<int> order = graph->bfs(start);
    QString seq; for(int v:order) seq+=QString::number(v+1)+" ";
    outputText->append("BFS: "+seq);
    scene->animateBFS(order);
    bfsBtn->setEnabled(false); dfsBtn->setEnabled(false); dijkstraBtn->setEnabled(false);
}

void MainWindow::onDFS()
{
    if (graph->verticesCount()==0) { outputText->append("Граф пуст"); return; }
    bool ok;
    int start = QInputDialog::getInt(this,"DFS","Начальная вершина (1.."+QString::number(graph->verticesCount())+"):",1,1,graph->verticesCount(),1,&ok);
    if (!ok) return;
    start--;
    QVector<int> order = graph->dfs(start);
    QString seq; for(int v:order) seq+=QString::number(v+1)+" ";
    outputText->append("DFS: "+seq);
    scene->animateDFS(order);
    bfsBtn->setEnabled(false); dfsBtn->setEnabled(false); dijkstraBtn->setEnabled(false);
}

void MainWindow::onDijkstra()
{
    if (graph->verticesCount()==0) { outputText->append("Граф пуст"); return; }
    int start=2;
    if (start>=graph->verticesCount()) { outputText->append("Вершина 3 не существует"); return; }
    auto res = graph->dijkstra(start);
    QVector<int> dist = res.first, prev = res.second;
    QString txt = "Кратчайшие расстояния от вершины 3:\n";
    for (int i=0;i<dist.size();++i)
        txt += QString("  до %1: ").arg(i+1) + (dist[i]==INF ? "нет пути\n" : QString::number(dist[i])+"\n");
    outputText->append(txt);
    for (int i=0;i<dist.size();++i) scene->setVertexDistance(i, dist[i]);
    bool ok;
    int target = QInputDialog::getInt(this,"Дейкстра","Показать путь до вершины (1.."+QString::number(graph->verticesCount())+"):",3,1,graph->verticesCount(),1,&ok);
    if (ok && target-1!=start) {
        int v=target-1;
        if (dist[v]!=INF) {
            scene->resetColors();
            QVector<int> path;
            while (v!=-1) { path.prepend(v); v=prev[v]; }
            for (int i=0;i<path.size();++i) {
                scene->highlightVertex(path[i], Qt::green);
                if (i>0) scene->highlightEdge(path[i-1], path[i], Qt::red);
            }
        } else outputText->append("Путь до вершины "+QString::number(target)+" не существует.");
    }
}

void MainWindow::onFloyd()
{
    if (graph->verticesCount()==0) { outputText->append("Граф пуст"); return; }
    QVector<QVector<int>> d = graph->floyd();
    QString txt = "Матрица кратчайших расстояний (Флойд):\n";
    for (int i=0;i<d.size();++i) {
        for (int j=0;j<d[i].size();++j)
            txt += (d[i][j]==INF ? "INF\t" : QString::number(d[i][j])+"\t");
        txt += "\n";
    }
    outputText->append(txt);
}

void MainWindow::onAnimationFinished()
{
    bfsBtn->setEnabled(true);
    dfsBtn->setEnabled(true);
    dijkstraBtn->setEnabled(true);
    outputText->append("Анимация завершена.");
}
