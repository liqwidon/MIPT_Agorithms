#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include <vector>
using std:: vector;

class IGraph
{
public:
    virtual ~IGraph () {}

    virtual long count () = 0;

    virtual void getAdjacent (vector<long> & a, long v) = 0;

    virtual void getWeight (vector<long> & a, long v) = 0;

    virtual void addEdge (long v, long u, long w = 1);

    virtual void removeEdge (long v, long u);

    virtual IGraph* createEmpty (long nv);
};

bool bfsMinWay(IGraph* g, long v0, long v1, vector<long>& w);

bool dijkstra(IGraph* gr, long v0, long v1, vector<long>& way);

/// для неориентированного графа
/// \brief Prima
/// \param g - неориентированный граф
/// \param parents
///
void Prima(IGraph* g, std::vector<long>& parents);

long PrimW(IGraph* g);

void Kruskal(IGraph* g, vector<std:: pair<long, long>>& mst);

long KruskalW(IGraph* g);

long EdmondsKarp(IGraph* g, long s, long t);

#endif // DIJKSTRA_H
