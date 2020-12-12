#include "graph_algo.h"
#include "disjoint_set_union.h"
#include <limits>
#include <algorithm>
#include <queue>

void IGraph::addEdge (long v, long u, long w)
{}

IGraph* IGraph::createEmpty (long nv)
{
    return new ListGraph(nv);
}

void IGraph::removeEdge (long v, long u)
{}

long ListGraph::count()
{
    return g.size();
}
void ListGraph::getAdjacent(vector<long> & a,long v)
{
  a = g[v];
}
void ListGraph::getWeight(vector<long> & a,long v)
{
    a = w[v];
}
void ListGraph::addEdge(long v, long u, long w)
{
    g[v].push_back(u);
    this->w[v].push_back(w);
}
void ListGraph::removeEdge(long v, long u)
{
    long iu = find(g[v].begin(), g[v].end(), u) - g[v].begin();
    if (iu < g[v].size())
    {
        g[v].erase(iu + g[v].begin());
        w[v].erase(iu + w[v].begin());
    }
}

class PriorityQueue
{
public:
    PriorityQueue(const std:: vector<long> &d)
        : iv(d.size()), pv(d.size()), d{d}
    {
        for (long i = 0; i < d.size(); ++i)
        {
            iv[i] = i;
            pv[i] = i;
        }
    }

    bool empty() const { return iv.empty(); }

    long decreaseKey(long v) { sift_up(pv[v]); }

    long pop()
    {
        long v = iv.front();
        swap_id(0, iv.size() - 1);
        iv.pop_back();
        sift_down(0);
        return v;
    }

private:
    void sift_up(long i)
    {
        while(i > 0)
        {
            long p = (i - 1) / 2;
            if(d[iv[i]] > d[iv[p]])
                return;
            swap_id(i, p);
            i = p;
        }
    }

    void sift_down(long i)
    {
        long l = 2 * i + 1;
        long r = l + 1;
        long mn = i;
        if(r < iv.size() && d[iv[r]] < d[iv[mn]])
            mn = r;
        if(l < iv.size() && d[iv[l]] < d[iv[mn]])
            mn = l;
        if(mn != i)
        {
            swap_id(i, mn);
            sift_down(mn);
        }
    }

    void swap_id(long i, long j)
    {
        std:: swap(pv[iv[i]], pv[iv[j]]);
        std:: swap(iv[i], iv[j]);
    }

    std:: vector<long> iv;
    std:: vector<long> pv;
    const std:: vector<long> &d;
};



void wayFromP(const vector<long>& p, vector<long>& w, long v1)
{
    long v = v1;
    while (v != -1)
    {
        w.push_back(v);
        v = p[v];
    }
    std:: reverse(w.begin(), w.end());
}

bool bfsMinWay(IGraph* g, long v0, long v1, vector<long>& w)
{
    w.clear();
    vector<bool> visited(g->count());
    vector<long> p(g->count(), -1);

    std:: queue<long> q;
    q.push(v0);
    visited[v0] = true;
    while (!q.empty())
    {
        long v = q.front();
        q.pop();
        vector<long> adj;
        g->getAdjacent(adj, v);
        for (long u : adj)
        {
            if (!visited[u])
            {
                q.push(u);
                p[u] = v;
                visited[u] = true;
                if (u == v1)
                {
                    wayFromP(p, w, v1);
                    return true;
                }
            }
        }
    }
    return false;
}

bool dijkstra(IGraph* gr, long v0, long v1, vector<long>& way) {

    vector<long> d(gr->count(), std:: numeric_limits<long>:: max() / 2);
    vector<long> parents(gr->count(), -1);

    PriorityQueue q(d);

    d[v0] = 0;
    q.decreaseKey(v0);

    while (!q.empty()) {

        long v = q.pop();

        if (d[v] == std:: numeric_limits<long>:: max())
            return false;

        if (v == v1) {
            way.push_back(v1);
            while (v != v0) {
                way.push_back(parents[v]);
                v = parents[v];
            }
            std:: reverse(way.begin(), way.end());
            return true;
        }

        vector<long> adj;
        vector<long> weight;
        gr->getAdjacent(adj, v);
        gr->getWeight(weight, v);

        for(long i = 0; i < adj.size(); ++i)
        {
            if (d[v] + weight[i] < d[adj[i]])
            {
                d[adj[i]] = d[v] + weight[i];
                parents[adj[i]] = v;
                q.decreaseKey(adj[i]);
            }
        }
    }
    return false;
}
///

void Prima(IGraph* g, std::vector<long>& parents)
{
    parents.resize(g->count());
    std::fill(parents.begin(), parents.end(), -1);
    std::vector<long>  d(g->count(), std::numeric_limits<long>::max());
    std::vector<bool> usage(g->count());
    PriorityQueue q(d);

    d[0] = 0;
    q.decreaseKey(0);

    while (!q.empty()) {

        long v = q.pop();
        usage[v] = true;

        vector<long> adj;
        vector<long> weight;
        g->getAdjacent(adj, v);
        g->getWeight(weight, v);

        for(long i = 0; i < adj.size(); ++i)
        {
            if (!usage[adj[i]] && weight[i] < d[adj[i]])
            {
                d[adj[i]] = weight[i];
                parents[adj[i]] = v;
                q.decreaseKey(adj[i]);
            }
        }
    }
}

long PrimW(IGraph* g)
{
    std::vector <long> parents;
    Prima(g, parents);
    long W = 0;

    for (long v = 1; v < parents.size(); v++)
    {
        long pv = parents[v];
        vector<long> adj;
        vector<long> weight;
        g->getAdjacent(adj, v);
        g->getWeight(weight, v);

        W += weight[std::find(adj.begin(), adj.end(), pv) - adj.begin()];
    }
    return W;
}


void Kruskal(IGraph *g, vector<std::pair<long, long> > &mst)
{
    struct E
    {
        long u;
        long v;
        long w;
    };

    vector<E> edges;
    for (long v = 0; v < g->count(); ++v)
    {
        vector<long> adj;
        vector<long> weight;
        g->getAdjacent(adj, v);
        g->getWeight(weight, v);
        for (int i = 0; i < adj.size(); ++i)
            edges.push_back({v, adj[i], weight[i]});
    }

    std::sort(edges.begin(), edges.end(), [](E u, E v)
    {
        return u.w < v.w;
    });

    disjoint_set_union d(g->count());
    for(auto [u, v, w] : edges)
    {
        if(d.find_set(u) != d.find_set(v))
        {
            mst.push_back({u, v});
            d.union_sets(u, v);
        }
    }
}

long KruskalW(IGraph *g)
{
    long W = 0;
    vector<std:: pair<long, long>> mst;
    Kruskal(g, mst);
    for(auto [v, u] : mst)
    {
        vector<long> adj;
        vector<long> weight;
        g->getAdjacent(adj, v);
        g->getWeight(weight, v);
        W += weight[std::find(adj.begin(), adj.end(), u) - adj.begin()];
    }

    return W;
}

/*
//static bool bfsMinWay(const vector<vector<long>>& gf, const vector<vector<long>>& cf, long v0, long v1, vector<long>& w)
//{
//    w.clear();
//    vector<bool> visited(gf.size());
//    vector<long> p(gf.size(), -1);

//    std:: queue<long> q;
//    q.push(v0);
//    visited[v0] = true;
//    while (!q.empty())
//    {
//        long v = q.front();
//        q.pop();

//        for (long iu = 0; iu < gf[v].size(); ++iu)
//        {
//            long u = gf[v][iu];

//            if (!visited[u] && cf[v][iu] != 0)
//            {
//                q.push(u);
//                p[u] = v;
//                visited[u] = true;
//                if (u == v1)
//                {
//                    wayFromP(p, w, v1);
//                    return true;
//                }
//            }
//        }
//    }
//    return false;
//}

//static long minWayC(const vector<vector<long>>& gf, const vector<vector<long>>& cf, const vector<long>& way)
//{
//    long minc = LONG_MAX;
//    for (long i = 1; i < way.size(); ++i)
//    {
//        long v = way[i - 1];
//        long u = way[i];
//        long iu = find(gf[v].begin(), gf[v].end(), u) - gf[v].begin();
//        if (cf[v][iu] < minc)
//            minc = cf[v][iu];
//    }
//    return minc;
//}

//long EdmondsKarp(IGraph* g, long s, long t)
//{
//    long maxf = 0;
//    vector<long> way;
//    vector< vector<long> >  gf (g->count());
//    vector< vector<long> >  cf (g->count());

//    for (long v = 0; v < g->count(); ++v)
//    {
//        vector<long> adj;
//        vector<long> weight;
//        g->getAdjacent(adj, v);
//        g->getWeight(weight, v);
//        for (long iu = 0; iu < adj.size(); ++iu)
//        {
//            long u = adj[iu];
//            long w = weight[iu];
//            cf[v].push_back(w);
//            cf[u].push_back(0);
//            gf[v].push_back(u);
//            gf[u].push_back(v);
//        }
//    }

//    while (bfsMinWay(gf, cf, s, t, way))
//    {
//        long cfw = minWayC(gf, cf, way);
//        maxf += cfw;
//        for (long i = 1; i < way.size(); ++i)
//        {
//            long v = way[i - 1];
//            long u = way[i];
//            long iv = find(gf[u].begin(), gf[u].end(), v) - gf[u].begin();
//            long iu = find(gf[v].begin(), gf[v].end(), u) - gf[v].begin();
//            cf[v][iu] -= cfw;
//            cf[u][iv] += cfw;
//        }
//    }
//    return maxf;
//}
*/

static long minWayC(IGraph* g, const vector<long>& way)
{
    long minc = LONG_MAX;
    for (long i = 1; i < way.size(); ++i)
    {
        long v = way[i - 1];
        long u = way[i];

        vector<long> adj;
        vector<long> weight;
        g->getAdjacent(adj, v);
        g->getWeight(weight, v);

        long iu = find(adj.begin(), adj.end(), u) - adj.begin();
        if (weight[iu] < minc)
            minc = weight[iu];
    }
    return minc;
}

long EdmondsKarp(IGraph* g, long s, long t)
{
    long maxf = 0;
    vector<long> way;

    IGraph* gf = g->createEmpty(g->count());
    if (gf == nullptr)
        return 0;

    for (long v = 0; v < g->count(); ++v)
    {
        vector<long> adj;
        vector<long> weight;
        g->getAdjacent(adj, v);
        g->getWeight(weight, v);
        for (long iu = 0; iu < adj.size(); ++iu)
        {
            long u = adj[iu];
            long w = weight[iu];
            gf->addEdge(v, u, w);
        }
    }

    while (bfsMinWay(gf, s, t, way))
    {
        long cfw = minWayC(gf, way);
        maxf += cfw;
        for (long i = 1; i < way.size(); ++i)
        {
            long v = way[i - 1];
            long u = way[i];
            long wv = cfw;
            long wu = -cfw;

            vector<long> adjv, adju;
            vector<long> weightv, weightu;
            gf->getAdjacent(adjv, v);
            gf->getAdjacent(adju, u);
            gf->getWeight(weightv, v);
            gf->getWeight(weightu, u);

            long iv = find(adju.begin(), adju.end(), v) - adju.begin();
            if (iv < adju.size())
            {
                wv += weightu[iv];
                gf->removeEdge(u, v);
            }
            wu += weightv[find(adjv.begin(), adjv.end(), u) - adjv.begin()];
            gf->removeEdge(v, u);

            if (wu != 0)
                gf->addEdge(v, u, wu);
            if (wv != 0)
                gf->addEdge(u, v, wv);
        }
    }
    delete gf;
    return maxf;
}


