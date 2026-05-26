#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QLabel>
#include "graphmodel.h"
#include "graphscene.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void onAddVertex();
    void onRemoveVertex();
    void onAddEdge();
    void onRemoveEdge();
    void onEditEdgeWeight();
    void onUpdateMatrix();
    void onBFS();
    void onDFS();
    void onDijkstra();
    void onFloyd();
    void onAnimationFinished();

private:
    void setupUI();
    void updateGraphDisplay();
    void updateMatrixTable();

    GraphModel* graph;
    GraphScene* scene;
    QGraphicsView* view;
    QTableWidget* matrixTable;
    QTextEdit* outputText;
    QPushButton* addVertexBtn, *removeVertexBtn, *addEdgeBtn, *removeEdgeBtn, *editEdgeWeightBtn;
    QPushButton* updateMatrixBtn, *bfsBtn, *dfsBtn, *dijkstraBtn, *floydBtn;
    QSpinBox *fromSpin, *toSpin, *weightSpin;
    QLabel *fromLabel, *toLabel, *weightLabel;
};

#endif // MAINWINDOW_H
