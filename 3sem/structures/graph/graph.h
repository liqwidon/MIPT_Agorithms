#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>

///It's a wrapper to our graph classes
class IGraph {
public:

    virtual ~IGraph()
    {}

    virtual void add_edge(int v, int u) = 0;

    /// get all the adjacent to 'v' vertexes
    virtual void get_adj(int v, std:: vector<int>& a) const = 0;

    virtual int  count() const = 0;

    virtual void output() = 0;

    virtual bool has_edge(int v, int u) const = 0;
};

/// Graph is stored in the matrix
class MatrixGraph : public IGraph {
public:

    MatrixGraph(int n);


    void add_edge(int v, int u);

    void get_adj(int v, std:: vector<int>& adges) const;

    void output();

    bool has_edge(int v, int u) const { return matr[v][u]; }

    int count() const { return size; }

private:
    int size;
    bool** matr;
};

/// Graph is stored in the list
class ListGraph : public IGraph {
public:

    ListGraph(int n) { lst.resize(n); }

    void add_edge(int v, int u);

    void get_adj(int v, std:: vector<int>& edges) const { edges = lst[v]; }

    void output();

    bool has_edge(int v, int u) const;

    int count() const { return lst.size(); }

private:
    std:: vector<std:: vector<int> > lst;
};

enum color {
    WHITE = 0, GRAY, BLACK
};

///depth search recursion
void dfsSearch(IGraph& gr, std:: vector<color>& colors, int v);

///depth search
void dfs(IGraph& gr);

///depth search with parents recursion
void dfsSearchPrevious(IGraph& gr, std:: vector<color>& colors, std:: vector<int>& parents, int v);

///depth search with parents
void dfsParent(IGraph& gr);

///finding the path to the top rec
bool dfsSearchFirstWayRec(IGraph& gr, std:: vector<color>& colors, std:: vector<int>& parents, int v, int v1);

///finding the path to the vertex
void dfsSearchFirstWay(IGraph& gr, int v0, int v1);

///class for finding the first path
class DfsSearchFirstWay {
public:
    DfsSearchFirstWay(IGraph& graph, int v0, int v1);

private:
    bool rec(int v);

    IGraph& gr;
    std:: vector<int> parents;
    std:: vector<bool> visited;
    int v1;
};

///breadth-first search
void bfs(IGraph& gr, int v0);

///finding the distance to all vertexes
void bfsLength(IGraph& gr, int v0);

///minimum distance to the selected vertex
void minWay(IGraph& gr, int v0, int v1);


#endif // GRAPH_H
