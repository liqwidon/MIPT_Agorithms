#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include "rick_graph.h"
#include "rick_sten_graph.h"

using std::vector, std:: queue;

int main() {

    long a, b, M, x, y;
    std:: cin >> a >> b >> M >> x >> y;

//    long st0, st1, tax;
//    std:: cin >> st0 >> st1 >> tax;

    RickGraph gr(M, a, b);

//    RickStenGraph graph(&gr, st0, st1, tax);

    vector<long> way;

//    dijkstra(&graph, x, y, way);

    vector<std:: pair<long, long>> mst;

    Kruskal(&gr, mst);

    std:: cout << " ------------ " << std:: endl;

    for (auto [v, u] : mst)
        std:: cout << v << " " << u << std:: endl;

    std:: cout << " ------------ " << std:: endl;

    std:: cout << KruskalW(&gr) << std:: endl;

    return 0;
}

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

