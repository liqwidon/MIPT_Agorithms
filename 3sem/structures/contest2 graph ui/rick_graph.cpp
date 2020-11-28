#include "rick_graph.h"

long RickGraph::count()
{
    return n;
}
void RickGraph::getAdjacent(vector<long> & a, long v)
{
    a.push_back((v + 1) % n);
    long vl = v;
    a.push_back((vl * vl + 1)% n);
}
void RickGraph::getWeight(vector<long> & a, long v)
{
    a.push_back(b0);
    a.push_back(b1);
}
