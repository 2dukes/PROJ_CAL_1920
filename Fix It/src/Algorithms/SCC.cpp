
#include "SCC.h"

SCC::SCC(Graph<long> *graph) {
    this->graph = graph;
}

vector<vector<long>> SCC::calculateSCCs() {

    stack<Vertex<long>* > vPostOrdered; // Will have vertxes ordered according to Post-order.
    vector<long> dfsResult;
    dfsResult = dfsWithPostOrder(vPostOrdered);

    vector<vector<long>> SCCVector;
    SCCVector = reverseDFSVisit(vPostOrdered);

    return SCCVector;
}

vector<long> SCC::dfsWithPostOrder(stack<Vertex<long>* >  &vPostOrdered) const {
    vector<long> res;
    for(auto vertex: graph->getVertexSet())
        vertex->visited = false;
    for(auto vertex: graph->getVertexSet()) {
        if(!vertex->visited) // If not visited yet... Then visit.
            dfsWithPostOrderVisit(vertex, res, vPostOrdered);
    }
    return res;
}

void SCC::dfsWithPostOrderVisit(Vertex<long> *v, vector<long> & res, stack<Vertex<long>* >  &vPostOrdered) const {
    v->visited = true;
    res.push_back(v->info);
    for (auto edge: v->outgoing) {
        if(!edge->dest->visited)
            dfsWithPostOrderVisit(edge->dest, res, vPostOrdered);
    }
    vPostOrdered.push(v);
}

void SCC::ReversedfsWithPostOrderVisit(Vertex<long> *v, vector<long> & res) const {
    v->visited = true;
    res.push_back(v->info);
    for (auto edge: v->incoming) {
        if(!edge->orig->visited)
            ReversedfsWithPostOrderVisit(edge->orig, res);
    }
}

vector<vector<long>> SCC::reverseDFSVisit(stack<Vertex<long>* >  &vPostOrdered) const {
    vector<vector<long>> SCCVector;
    vector<long> res;
    for(auto vertex: graph->getVertexSet())
        vertex->visited = false;

    while(!vPostOrdered.empty()) {
        res.clear();

        Vertex<long>* auxVertex = vPostOrdered.top();
        vPostOrdered.pop();
        if(!auxVertex->visited) // If not visited yet... Then visit.
            ReversedfsWithPostOrderVisit(auxVertex, res); // res will hold the different trees!

        if(res.size() > 0) {
            SCCVector.push_back(res);
        }
    }

    return SCCVector;
}


