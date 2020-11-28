#include "graph_algo.h"
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
