#ifndef FIX_IT_DFS_H
#define FIX_IT_DFS_H

#include "../Graph/Graph.h"

template <class T>
class SearchAlgorithm {
protected:
    Graph<T>* graph;

public:
    SearchAlgorithm(const Graph<T>* graph);
    vector<T> dfs() const;
    vector<T> bfs(const T &source) const;
    void dfsVisit(Vertex<T> *v, vector<T> &res) const;
    friend class Graph<T>;
};

template<class T>
SearchAlgorithm<T>::SearchAlgorithm(const Graph<T> *graph) {
    this->graph = graph;
}

template <class T>
vector<T> SearchAlgorithm<T>::dfs() const {
    vector<T> res;
    for(auto vertex: graph->vertexSet)
        vertex->visited = false;
    for(auto vertex: graph->vertexSet) {
        if(!vertex->visited) // If not visited yet... Then visit.
            dfsVisit(vertex, res);
    }
    return res;
}

template <class T>
void SearchAlgorithm<T>::dfsVisit(Vertex<T> *v, vector<T> & res) const {
    v->visited = true;
    res.push_back(v->info);
    for (auto edge: v->adj) {
        if(!edge.dest->visited)
            dfsVisit(edge.dest, res);
    }
}

template <class T>
vector<T> SearchAlgorithm<T>::bfs(const T & source) const {
    vector<T> res;
    for(auto vertex: graph->vertexSet)
        vertex->visited = false;

    queue<Vertex<T> *> vertexQueue;
    Vertex<T>* root = graph->findVertex(source);
    root->visited = true;
    vertexQueue.push(root);

    while(!vertexQueue.empty()) {
        Vertex<T>* vertex = vertexQueue.front();
        res.push_back(vertex->info);

        for(auto edge: vertex->adj) {
            if(!edge.dest->visited) {
                vertexQueue.push(edge.dest);
                edge.dest->visited = true;
            }
        }

        vertexQueue.pop();
    }

    return res;
}

#endif //FIX_IT_DFS_H
