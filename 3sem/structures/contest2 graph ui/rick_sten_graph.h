#ifndef RICK_STEN_GRAPH_H
#define RICK_STEN_GRAPH_H
#include "graph_algo.h"

class RickStenGraph : public IGraph
{
public:
    RickStenGraph (IGraph* g, long st0, long st1, long tax);

    long count();
    void getAdjacent(vector<long> & a, long v);
    void getWeight(vector<long> & a, long v);

private:
    long tax;
    IGraph * g;
    vector<bool> is_sten_universe;
    vector<bool> military_base;
};

#endif // RICK_STEN_GRAPH_H
