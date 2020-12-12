#include "rick_sten_graph.h"

RickStenGraph::RickStenGraph (IGraph* g, long st0, long st1, long tax) : tax{tax},
    g{g}, is_sten_universe(g->count()), military_base(g->count())
{
    vector<long> way;
    dijkstra(g, st0, st1, way);

    for (long i = 0; i < way.size(); ++i)
    {
        is_sten_universe[way[i]] = true;
    }

    for (long u : way)
        if (u % 2 == 0)
            military_base[u] = true;
}

long RickStenGraph::count()
{
    return g->count();
}

void RickStenGraph::getAdjacent(vector<long> & a, long v)
{
    vector<long> a0;
    g->getAdjacent(a0, v);
    for (long i = 0; i < a0.size(); ++i)
        if (!military_base[a0[i]])
            a.push_back(a0[i]);
}
void RickStenGraph::getWeight(vector<long> & a, long v)
{
    vector<long> a0;
    getAdjacent(a0, v);
    g->getWeight(a, v);
    for(long i = 0; i < a.size(); ++i)
        if(is_sten_universe[a0[i]])
            a[i] = tax;
}
