#include "graphscene.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QTimer>
#include <cmath>

static const qreal PI = 3.14159265358979323846;

// ---------- VertexItem ----------
VertexItem::VertexItem(int id, qreal x, qreal y, qreal radius)
    : QGraphicsEllipseItem(x - radius, y - radius, 2*radius, 2*radius)
    , id(id), radius(radius), distance(-1)
{
    setPen(QPen(Qt::black, 2));
    setBrush(QBrush(Qt::white));
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemSendsGeometryChanges);
}

void VertexItem::setDistanceText(int dist)
{
    distance = dist;
    update();
}

void VertexItem::setColor(const QColor& color)
{
    setBrush(QBrush(color));
}

void VertexItem::setDefaultColor()
{
    setBrush(QBrush(Qt::white));
}

void VertexItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    QGraphicsEllipseItem::paint(painter, option, widget);
    painter->save();
    painter->setPen(Qt::black);
    QFont font("Arial", 12, QFont::Bold);
    painter->setFont(font);
    QRectF rect = boundingRect();
    QString numberStr = QString::number(id + 1);
    painter->drawText(rect, Qt::AlignCenter, numberStr);
    if (distance >= 0 && distance < INF/2) {
        painter->setPen(Qt::darkGreen);
        QFont distFont("Arial", 10);
        painter->setFont(distFont);
        QString distStr = QString::number(distance);
        QRectF distRect = rect;
        distRect.setTop(rect.center().y());
        painter->drawText(distRect, Qt::AlignCenter, distStr);
    }
    painter->restore();
}

void VertexItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsEllipseItem::mousePressEvent(event);
}

// ---------- EdgeItem ----------
EdgeItem::EdgeItem(int from, int to, int weight, QPointF fromPos, QPointF toPos)
    : QGraphicsLineItem(), from(from), to(to)
{
    setPen(QPen(Qt::black, 2));
    weightText = new QGraphicsTextItem(QString::number(weight), this);
    weightText->setDefaultTextColor(Qt::darkBlue);
    weightText->setFont(QFont("Arial", 10));
    updatePosition(fromPos, toPos);
}

void EdgeItem::setColor(const QColor& color)
{
    setPen(QPen(color, 3));
}

void EdgeItem::setDefaultColor()
{
    setPen(QPen(Qt::black, 2));
}

void EdgeItem::updatePosition(QPointF fromPos, QPointF toPos)
{
    QLineF line(fromPos, toPos);
    qreal len = line.length();
    qreal r = 40;
    if (len < 0.1) return;
    QPointF newFrom = fromPos + (toPos - fromPos) * (r / len);
    QPointF newTo = toPos - (toPos - fromPos) * (r / len);
    setLine(QLineF(newFrom, newTo));
    drawArrow(newFrom, newTo);
    QPointF mid = (newFrom + newTo) / 2;
    weightText->setPos(mid);
}

void EdgeItem::drawArrow(QPointF from, QPointF to)
{
    QLineF line(from, to);
    qreal angle = std::acos(line.dx() / line.length());
    if (line.dy() >= 0) angle = 2*PI - angle;
    QPointF arrowP1 = to + QPointF(std::sin(angle - PI/3)*10, std::cos(angle - PI/3)*10);
    QPointF arrowP2 = to + QPointF(std::sin(angle - PI + PI/3)*10, std::cos(angle - PI + PI/3)*10);
    QPolygonF arrowHead;
    arrowHead << to << arrowP1 << arrowP2;
    QList<QGraphicsItem*> children = childItems();
    for (int i = 0; i < children.size(); ++i) {
        if (children[i] != weightText) delete children[i];
    }
    QGraphicsPolygonItem* arrow = new QGraphicsPolygonItem(arrowHead, this);
    arrow->setBrush(Qt::black);
    arrow->setPen(Qt::NoPen);
}

// ---------- GraphScene ----------
GraphScene::GraphScene(QObject* parent) : QGraphicsScene(parent), graph(nullptr), radius(40), animationTimerId(0) {}

void GraphScene::setGraph(GraphModel* graph)
{
    this->graph = graph;
    updateLayout();
}

void GraphScene::updateLayout()
{
    clearItems();
    if (!graph || graph->verticesCount() == 0) return;
    int n = graph->verticesCount();
    vertices.clear();
    edges.clear();
    edges.resize(n);
    for (int i = 0; i < n; ++i) {
        edges[i].resize(n);
        for (int j = 0; j < n; ++j) edges[i][j] = nullptr;
    }
    qreal centerX = 400, centerY = 300, rad = 200;
    QVector<QPointF> positions(n);
    for (int i = 0; i < n; ++i) {
        qreal angle = 2 * PI * i / n - PI/2;
        qreal x = centerX + rad * std::cos(angle);
        qreal y = centerY + rad * std::sin(angle);
        positions[i] = QPointF(x, y);
        VertexItem* v = new VertexItem(i, x, y, radius);
        addItem(v);
        vertices.append(v);
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int w = graph->getEdgeWeight(i, j);
            if (w != INF && i != j) {
                EdgeItem* edge = new EdgeItem(i, j, w, positions[i], positions[j]);
                addItem(edge);
                edges[i][j] = edge;
            }
        }
    }
    update();
}

void GraphScene::clearItems()
{
    for (auto v : vertices) delete v;
    vertices.clear();
    for (auto row : edges) {
        for (auto e : row) delete e;
    }
    edges.clear();
    QGraphicsScene::clear();
}

void GraphScene::highlightVertex(int id, const QColor& color)
{
    if (id >= 0 && id < vertices.size()) vertices[id]->setColor(color);
}

void GraphScene::resetVertexColors()
{
    for (auto v : vertices) v->setDefaultColor();
}

void GraphScene::highlightEdge(int from, int to, const QColor& color)
{
    if (from < edges.size() && to < edges[from].size() && edges[from][to])
        edges[from][to]->setColor(color);
}

void GraphScene::resetEdgeColors()
{
    for (int i = 0; i < edges.size(); ++i)
        for (int j = 0; j < edges[i].size(); ++j)
            if (edges[i][j]) edges[i][j]->setDefaultColor();
}

void GraphScene::setVertexDistance(int id, int dist)
{
    if (id >= 0 && id < vertices.size()) vertices[id]->setDistanceText(dist);
}

void GraphScene::animateBFS(const QVector<int>& order)
{
    if (animationTimerId) killTimer(animationTimerId);
    resetColors();
    animationOrder = order;
    animationStep = 0;
    animationTimerId = startTimer(500);
}

void GraphScene::animateDFS(const QVector<int>& order) { animateBFS(order); }

void GraphScene::startDijkstraAnimation(int start)
{
    if (!graph) return;
    int n = graph->verticesCount();
    dijkstraDist.fill(INF, n);
    dijkstraPrev.fill(-1, n);
    dijkstraVisited.fill(false, n);
    dijkstraDist[start] = 0;
    dijkstraStart = start;
    if (animationTimerId) killTimer(animationTimerId);
    resetColors();
    for (int i = 0; i < n; ++i)
        setVertexDistance(i, dijkstraDist[i] == INF ? -1 : dijkstraDist[i]);
    highlightVertex(start, Qt::yellow);
    animationTimerId = startTimer(800);
}

void GraphScene::doDijkstraStep()
{
    int n = dijkstraDist.size();
    int u = -1;
    for (int i = 0; i < n; ++i) {
        if (!dijkstraVisited[i] && (u == -1 || dijkstraDist[i] < dijkstraDist[u]))
            u = i;
    }
    if (u == -1 || dijkstraDist[u] == INF) {
        killTimer(animationTimerId);
        animationTimerId = 0;
        emit animationFinished();
        return;
    }
    dijkstraVisited[u] = true;
    highlightVertex(u, Qt::red);
    for (int v = 0; v < n; ++v) {
        int w = graph->getEdgeWeight(u, v);
        if (w != INF && dijkstraDist[u] + w < dijkstraDist[v]) {
            dijkstraDist[v] = dijkstraDist[u] + w;
            dijkstraPrev[v] = u;
            setVertexDistance(v, dijkstraDist[v]);
            highlightEdge(u, v, Qt::green);
        }
    }
    QTimer::singleShot(300, this, [this, u]() {
        if (u < vertices.size()) vertices[u]->setDefaultColor();
    });
}

void GraphScene::timerEvent(QTimerEvent* event)
{
    if (event->timerId() != animationTimerId) return;
    if (!animationOrder.isEmpty()) {
        if (animationStep < animationOrder.size()) {
            highlightVertex(animationOrder[animationStep], Qt::green);
            animationStep++;
        } else {
            killTimer(animationTimerId);
            animationTimerId = 0;
            emit animationFinished();
        }
    } else {
        doDijkstraStep();
    }
}

void GraphScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsItem* item = itemAt(event->scenePos(), QTransform());
    VertexItem* vitem = dynamic_cast<VertexItem*>(item);
    if (vitem) emit vertexClicked(vitem->getId());
    QGraphicsScene::mousePressEvent(event);
}

void GraphScene::resetColors()
{
    resetVertexColors();
    resetEdgeColors();
}

// ----- Динамическое обновление рёбер -----
EdgeItem* GraphScene::getEdge(int from, int to) const
{
    if (from >= 0 && from < edges.size() && to >= 0 && to < edges[from].size())
        return edges[from][to];
    return nullptr;
}

void GraphScene::addEdgeItem(int from, int to, int weight)
{
    if (!graph || from >= vertices.size() || to >= vertices.size()) return;
    QPointF fromPos = vertices[from]->pos();
    QPointF toPos = vertices[to]->pos();
    EdgeItem* edge = new EdgeItem(from, to, weight, fromPos, toPos);
    addItem(edge);
    edges[from][to] = edge;
}

void GraphScene::removeEdgeItem(int from, int to)
{
    EdgeItem* edge = getEdge(from, to);
    if (edge) {
        delete edge;
        edges[from][to] = nullptr;
    }
}

void GraphScene::updateEdgeWeight(int from, int to, int newWeight)
{
    EdgeItem* edge = getEdge(from, to);
    if (edge) {
        edge->weightText->setPlainText(QString::number(newWeight));
    } else {
        addEdgeItem(from, to, newWeight);
    }
}
