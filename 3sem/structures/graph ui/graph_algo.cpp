#include "graph_algo.h"
#include "disjoint_set_union.h"
#include <limits>
#include <algorithm>

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
