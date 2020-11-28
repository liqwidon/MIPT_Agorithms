#ifndef DISJOINT_SET_UNION_H
#define DISJOINT_SET_UNION_H
#include <vector>

class disjoint_set_union
{
public:
    disjoint_set_union(long vertex_num)
        : parent(vertex_num)
    {
        for(long i = 0; i < vertex_num; ++i)
            parent[i] = i;
    }

    void union_sets(long u, long v)
    {
        u = find_set(u);
        v = find_set(v);
        if(u != v)
            parent[v] = u;
    }

    long find_set(long u)
    {
        if(u == parent[u])
            return u;
        return find_set(parent[u]);
    }

private:
    std:: vector<long> parent;

};

#endif // DISJOINT_SET_UNION_H
