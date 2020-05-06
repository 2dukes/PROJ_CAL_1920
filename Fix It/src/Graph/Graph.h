/*
* Graph.h
*/

#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <new>
using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;


/*
 * ================================================================================================
 * Class Vertex
 * ================================================================================================
 */

template <class T>
class Vertex {
    T info;                     // Content
    vector<Edge<T> *> outgoing; // Outgoing Edges
    vector<Edge<T> *> incoming; // Incoming

    bool visited;               // for path finding
    Edge<T> *path;              // for path finding
    int queueIndex = 0; 		// required by MutablePriorityQueue


    Edge<T> * addEdge(Vertex<T> *dest, double c, double f);
    bool removeEdgeTo(Vertex<T> *d);
public:
    Vertex(T in);
    T getInfo() const;
    vector<Edge<T> *> getOutgoingEdges() const;
    vector<Edge<T> *> getIncomingEdges() const;
    friend class Graph<T>;
    friend class MutablePriorityQueue<Vertex<T>>;
};


template <class T>
Vertex<T>::Vertex(T in): info(in) {}

template <class T>
T Vertex<T>::getInfo() const {
    return this->info;
}

template<class T>
vector<Edge<T> *> Vertex<T>::getOutgoingEdges() const {
    return outgoing;
}

template<class T>
vector<Edge<T> *> Vertex<T>::getIncomingEdges() const {
    return incoming;
}

template <class T>
Edge<T> *Vertex<T>::addEdge(Vertex<T> *dest, double c, double f) {
    Edge<T> * e = new Edge<T>(this, dest, c, f); // IT'S THE SAME EDGE FOR BOTH VERTICES. DOESN'T SWITCH DIRECTION!
    this->outgoing.push_back(e);
    dest->incoming.push_back(e);
    return e;
}

template <class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
    typename vector<Edge<T>>::iterator iTr;
    for(iTr = outgoing.begin(); iTr != outgoing.end(); iTr++)
    {
        if(iTr->dest->info == d->info) {
            outgoing.erase(iTr);
            return true;
        }
    }
    return false;
}

/* ================================================================================================
 * Class Edge
 * ================================================================================================
 */

template <class T>
class Edge {
    Vertex<T> * orig;      // origin vertex
    Vertex<T> * dest;      // destination vertex
    double weight;         // edge weight
public:
    Edge(Vertex<T> *o, Vertex<T> *d, double w);
    Vertex<T>* getOrig();
    Vertex<T>* getDest();
    friend class Graph<T>;
    friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *o, Vertex<T> *d, double w): orig(o), dest(d), weight(w) {}

template <class T>
Vertex<T>* Edge<T>::getOrig() {
    return orig;
}

template <class T>
Vertex<T>* Edge<T>::getDest() {
    return dest;
}

/* ================================================================================================
 * Class Graph
 * ================================================================================================
 */

template <class T>
class Graph {
    vector<Vertex<T> *> vertexSet;    // vertex set
//    void dfsVisit(Vertex<T> *v,  vector<T> & res) const;
    Vertex<T> *findVertex(const T &in) const;
public:
    int getNumVertex() const;
    bool addVertex(const T &in);
    bool removeVertex(const T &in);
    bool addEdge(const T &sourc, const T &dest, double w);
    bool removeEdge(const T &sourc, const T &dest);
//    vector<T> dfs() const;
//    vector<T> bfs(const T &source) const;
};

template <class T>
int Graph<T>::getNumVertex() const {
    return vertexSet.size();
}

template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
    for (auto v : vertexSet)
        if (v->info == in)
            return v;
    return NULL;
}

template <class T>
bool Graph<T>::addVertex(const T &in) {
    if(findVertex(in) != NULL) // Vertex already exists
        return false;
    else {
        Vertex<T>* newVertex = new Vertex<T>(in);
        vertexSet.push_back(newVertex);
        return true;
    }
}

template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
    Vertex<T>* vSource = findVertex(sourc);
    Vertex<T>* vDest = findVertex(dest);
    if(vSource == NULL || vDest == NULL) // Vertexs don't exist
        return false;

    vSource->addEdge(vDest, w);
    return true;
}

template <class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
    Vertex<T>* vSource = findVertex(sourc);
    Vertex<T>* vDest = findVertex(dest);
    if(vSource == NULL || vDest == NULL)
        return false;

    return vSource->removeEdgeTo(vDest);
}

template <class T>
bool Graph<T>::removeVertex(const T &in) {
    Vertex<T>* toRemove = findVertex(in);
    if(toRemove == NULL) // No vertex to remove
        return false;

    typename vector<Edge<T>>::iterator iTr1;
    for(iTr1 = toRemove->adj.begin(); iTr1 != toRemove->adj.end(); iTr1++)
        iTr1 = --toRemove->adj.erase(iTr1);

    typename vector<Vertex<T> *>::iterator iTr2;
    for(iTr2 = vertexSet.begin(); iTr2 != vertexSet.end(); iTr2++) {
        (*iTr2)->removeEdgeTo(toRemove);
        if((*iTr2)->info == toRemove->info)
            iTr2 = --vertexSet.erase(iTr2);
    }
    return true;
}

#endif /* GRAPH_H_ */