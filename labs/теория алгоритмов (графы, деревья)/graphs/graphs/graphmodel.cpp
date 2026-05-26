#include "graphmodel.h"

GraphModel::GraphModel() : vertexCount(0) {}

void GraphModel::setVerticesCount(int n)
{
    vertexCount = n;
    adjMatrix.resize(vertexCount);
    for (int i = 0; i < vertexCount; ++i) {
        adjMatrix[i].resize(vertexCount);
        for (int j = 0; j < vertexCount; ++j) {
            adjMatrix[i][j] = (i == j) ? 0 : INF;
        }
    }
}

void GraphModel::addVertex()
{
    int newCount = vertexCount + 1;
    adjMatrix.resize(newCount);
    for (int i = 0; i < newCount; ++i) {
        adjMatrix[i].resize(newCount);
        if (i < vertexCount) {
            adjMatrix[i][newCount-1] = INF;
        }
        adjMatrix[newCount-1][i] = INF;
    }
    adjMatrix[newCount-1][newCount-1] = 0;
    vertexCount = newCount;
}

void GraphModel::removeVertex(int index)
{
    if (index < 0 || index >= vertexCount) return;
    QVector<QVector<int>> newMatrix(vertexCount-1, QVector<int>(vertexCount-1, INF));
    int newRow = 0;
    for (int i = 0; i < vertexCount; ++i) {
        if (i == index) continue;
        int newCol = 0;
        for (int j = 0; j < vertexCount; ++j) {
            if (j == index) continue;
            newMatrix[newRow][newCol] = adjMatrix[i][j];
            ++newCol;
        }
        ++newRow;
    }
    adjMatrix = newMatrix;
    vertexCount--;
    for (int i = 0; i < vertexCount; ++i) adjMatrix[i][i] = 0;
}

void GraphModel::addEdge(int from, int to, int weight)
{
    if (from < 0 || from >= vertexCount || to < 0 || to >= vertexCount) return;
    adjMatrix[from][to] = weight;
}

void GraphModel::removeEdge(int from, int to)
{
    if (from < 0 || from >= vertexCount || to < 0 || to >= vertexCount) return;
    adjMatrix[from][to] = INF;
}

void GraphModel::setEdgeWeight(int from, int to, int weight)
{
    addEdge(from, to, weight);
}

int GraphModel::getEdgeWeight(int from, int to) const
{
    if (from < 0 || from >= vertexCount || to < 0 || to >= vertexCount) return INF;
    return adjMatrix[from][to];
}

QVector<QVector<int>> GraphModel::getAdjacencyMatrix() const
{
    return adjMatrix;
}

void GraphModel::setAdjacencyMatrix(const QVector<QVector<int>>& matrix)
{
    adjMatrix = matrix;
    vertexCount = adjMatrix.size();
    for (int i = 0; i < vertexCount; ++i) {
        adjMatrix[i][i] = 0;
    }
}

QVector<int> GraphModel::bfs(int start)
{
    QVector<int> order;
    QVector<bool> visited(vertexCount, false);
    QQueue<int> q;
    visited[start] = true;
    q.enqueue(start);
    while (!q.isEmpty()) {
        int v = q.dequeue();
        order.append(v);
        for (int to = 0; to < vertexCount; ++to) {
            if (adjMatrix[v][to] != INF && !visited[to]) {
                visited[to] = true;
                q.enqueue(to);
            }
        }
    }
    return order;
}

QVector<int> GraphModel::dfs(int start)
{
    QVector<int> order;
    QVector<bool> visited(vertexCount, false);
    QStack<int> stack;
    stack.push(start);
    while (!stack.isEmpty()) {
        int v = stack.pop();
        if (!visited[v]) {
            visited[v] = true;
            order.append(v);
            for (int to = vertexCount-1; to >= 0; --to) {
                if (adjMatrix[v][to] != INF && !visited[to]) {
                    stack.push(to);
                }
            }
        }
    }
    return order;
}

QPair<QVector<int>, QVector<int>> GraphModel::dijkstra(int start)
{
    QVector<int> dist(vertexCount, INF);
    QVector<int> prev(vertexCount, -1);
    QVector<bool> visited(vertexCount, false);
    dist[start] = 0;
    for (int i = 0; i < vertexCount; ++i) {
        int u = -1;
        for (int j = 0; j < vertexCount; ++j) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }
        if (u == -1 || dist[u] == INF) break;
        visited[u] = true;
        for (int v = 0; v < vertexCount; ++v) {
            if (adjMatrix[u][v] != INF) {
                int newDist = dist[u] + adjMatrix[u][v];
                if (newDist < dist[v]) {
                    dist[v] = newDist;
                    prev[v] = u;
                }
            }
        }
    }
    return qMakePair(dist, prev);
}

QVector<QVector<int>> GraphModel::floyd()
{
    QVector<QVector<int>> d = adjMatrix;
    for (int k = 0; k < vertexCount; ++k) {
        for (int i = 0; i < vertexCount; ++i) {
            for (int j = 0; j < vertexCount; ++j) {
                if (d[i][k] != INF && d[k][j] != INF && d[i][k] + d[k][j] < d[i][j]) {
                    d[i][j] = d[i][k] + d[k][j];
                }
            }
        }
    }
    return d;
}
