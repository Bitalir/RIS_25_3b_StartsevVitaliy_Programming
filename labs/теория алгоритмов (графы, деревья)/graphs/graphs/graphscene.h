#ifndef GRAPHSCENE_H
#define GRAPHSCENE_H

#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsTextItem>
#include <QPen>
#include <QBrush>
#include <QTimerEvent>
#include "graphmodel.h"

class VertexItem : public QGraphicsEllipseItem
{
public:
    VertexItem(int id, qreal x, qreal y, qreal radius = 40);
    int getId() const { return id; }
    void setDistanceText(int dist);
    void setColor(const QColor& color);
    void setDefaultColor();

protected:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

private:
    int id;
    qreal radius;
    int distance;
};

class EdgeItem : public QGraphicsLineItem
{
public:
    EdgeItem(int from, int to, int weight, QPointF fromPos, QPointF toPos);
    void setColor(const QColor& color);
    void setDefaultColor();
    void updatePosition(QPointF fromPos, QPointF toPos);
    int getFrom() const { return from; }
    int getTo() const { return to; }
    QGraphicsTextItem* weightText;

private:
    int from, to;
    void drawArrow(QPointF from, QPointF to);
};

class GraphScene : public QGraphicsScene
{
    Q_OBJECT
public:
    GraphScene(QObject* parent = nullptr);
    void setGraph(GraphModel* graph);
    void updateLayout();
    void clearItems();
    void highlightVertex(int id, const QColor& color);
    void resetVertexColors();
    void highlightEdge(int from, int to, const QColor& color);
    void resetEdgeColors();
    void setVertexDistance(int id, int dist);
    void animateBFS(const QVector<int>& order);
    void animateDFS(const QVector<int>& order);
    void startDijkstraAnimation(int start);
    void resetColors();

    // Добавленные методы для динамического обновления рёбер
    EdgeItem* getEdge(int from, int to) const;
    void addEdgeItem(int from, int to, int weight);
    void removeEdgeItem(int from, int to);
    void updateEdgeWeight(int from, int to, int newWeight);

signals:
    void vertexClicked(int id);
    void animationFinished();

private:
    void doDijkstraStep();
    void timerEvent(QTimerEvent* event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

    GraphModel* graph;
    QVector<VertexItem*> vertices;
    QVector<QVector<EdgeItem*>> edges;
    qreal radius;
    int animationTimerId;
    int animationStep;
    QVector<int> animationOrder;

    QVector<int> dijkstraDist;
    QVector<int> dijkstraPrev;
    QVector<bool> dijkstraVisited;
    int dijkstraStart;
    int dijkstraCurrent;
};

#endif // GRAPHSCENE_H
