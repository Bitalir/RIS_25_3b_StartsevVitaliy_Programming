#ifndef GRAPHMODEL_H
#define GRAPHMODEL_H

#include <QVector>
#include <QQueue>
#include <QStack>
#include <QPair>

const int INF = 1e9;

class GraphModel
{
public:
    GraphModel();
    void setVerticesCount(int n);
    int verticesCount() const { return vertexCount; }
    void addVertex();
    void removeVertex(int index);
    void addEdge(int from, int to, int weight);
    void removeEdge(int from, int to);
    void setEdgeWeight(int from, int to, int weight);
    int getEdgeWeight(int from, int to) const;
    QVector<QVector<int>> getAdjacencyMatrix() const;
    void setAdjacencyMatrix(const QVector<QVector<int>>& matrix);

    QVector<int> bfs(int start);
    QVector<int> dfs(int start);
    QPair<QVector<int>, QVector<int>> dijkstra(int start);
    QVector<QVector<int>> floyd();

private:
    int vertexCount;
    QVector<QVector<int>> adjMatrix;
};

#endif // GRAPHMODEL_H
