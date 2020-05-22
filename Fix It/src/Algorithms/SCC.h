#ifndef FIX_IT_SCC_H
#define FIX_IT_SCC_H

#include "../Graph/Graph.h"
#include <stack>

class SCC {
    Graph<long>* graph;
public:
    SCC(Graph<long>* graph);
    vector<long> dfsWithPostOrder(stack<Vertex<long>* >  &vPostOrdered) const;
    void dfsWithPostOrderVisit(Vertex<long> *v, vector<long> & res, stack<Vertex<long>* > &vPostOrdered) const;
    vector<vector<long>> calculateSCCs();

    vector<vector<long>> reverseDFSVisit(stack<Vertex<long>* >  &vPostOrdered) const;
    void ReversedfsWithPostOrderVisit(Vertex<long> *v, vector<long> & res) const;
};



#endif //FIX_IT_SCC_H
