#ifndef RICK_GRAPH_H
#define RICK_GRAPH_H
#include "graph_algo.h"

class RickGraph : public IGraph
{
public:
    RickGraph(long n, long b0, long b1)
        : n{n}, b0{b0}, b1{b1}
    {}
    long count();
    void getAdjacent(vector<long> & a, long v);
    void getWeight(vector<long> & a, long v);
private:
    long n;
    long b0, b1;
};

#endif // RICK_GRAPH_H
