#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include "rick_graph.h"
#include "rick_sten_graph.h"
#include <unordered_set>

using std::vector, std:: queue;

class RickGraphAdapter : public IGraph
{
public:
    RickGraphAdapter(IGraph* g)
        : g{g}
    {}
    long count ()
    {
        return g->count();
    }

    void getAdjacent (vector<long> & a, long v)
    {
        std::unordered_set<long> vert;
        vector<long> a0;
        g->getAdjacent(a0, v);
        for (auto u : a0)
            vert.insert(u);
        for (auto u : vert)
            a.push_back(u);
    }

    void getWeight (vector<long> & a, long v)
    {
        vector<long> weight;
        g->getWeight(weight, v);
        vector<long> a0;
        g->getAdjacent(a0, v);
        vector<long> a1;
        this->getAdjacent(a1, v);
        a.resize(a1.size());
        for (int i = 0; i < a1.size(); ++i)
        {
            for (int j = 0; j < a0.size(); ++j)
                if (a1[i] == a0[j])
                    a[i] += weight[j];
        }
    }

private:
    IGraph* g;
};

int main() {

    long a, b, M, x, y;
    std:: cin >> a >> b >> M >> x >> y;

//    long st0, st1, tax;
//    std:: cin >> st0 >> st1 >> tax;

    RickGraph gr(M, a, b);

    RickGraphAdapter graph(&gr);

    std:: cout << EdmondsKarp(&graph, x, y);

//    RickStenGraph graph(&gr, st0, st1, tax);

//    vector<long> way;

//    dijkstra(&graph, x, y, way);

//    vector<std:: pair<long, long>> mst;

//    Kruskal(&gr, mst);

//    std:: cout << " ------------ " << std:: endl;

//    for (auto [v, u] : mst)
//        std:: cout << v << " " << u << std:: endl;

//    std:: cout << " ------------ " << std:: endl;

//    std:: cout << KruskalW(&gr) << std:: endl;

    return 0;
}

/*
int main()
{
    int nv, ne, s, t;
    std:: cin >> nv >> ne >> s >> t;

    ListGraph g(nv);

    for (int i = 0; i < ne; ++i)
    {
        int v, u, c0;
        std:: cin >> v >> u >> c0;
        g.addEdge(v, u, c0);
    }

    std:: cout << EdmondsKarp(&g, s, t);
}*/

//class List_Graph : public IGraph
//{
//public:
//    List_Graph(const vector<vector<long>> & g,const vector<vector<long>> & w) : g{g}, w{w} {}
//    virtual long count()
//    {
//        return g.size();
//    }
//    virtual void getAdjacent(vector<long> & a,long v)
//    {
//      a = g[v];
//    }
//    virtual void getWeight(vector<long> & a,long v)
//    {
//        a = w[v];
//    }
//private:
//    const vector<vector<long>> & g;
//    const vector<vector<long>> & w;
//};

//int main()
//{
//    long nv, ne;
//    std:: cin >> nv >> ne;
//    vector<vector<long>> g(nv);
//    vector<vector<long>> wt(nv);

//    for (int i = 0; i < ne; ++i) {

//        long v, u, w;
//        std:: cin >> v >> u >> w;
//        g[v].push_back(u);
////        g[u].push_back(v);
//        wt[v].push_back(w);
////        wt[u].push_back(w);
//    }

//    List_Graph graph(g, wt);

//    std:: cout << KruskalW(&graph) << std:: endl;

//    return 0;
//}

