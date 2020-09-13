#include "graph.h"

//for MatrixGraph
MatrixGraph:: MatrixGraph(int n) {
    this-> size = n;
    matr = new bool* [n];
    for (int i = 0; i < n; ++i)
        matr[i] = new bool[n] ();
}

void MatrixGraph:: add_edge(int v, int u) {
    matr[v][u] = true;
    matr[u][v] = true;
}

void MatrixGraph:: get_adj(int v, std:: vector<int>& adges) const {
    for (int i = 0; i < size; ++i)
        if(matr[v][i])
            adges.push_back(i);
}

void MatrixGraph:: output() {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j)
            std:: cout << matr[i][j] << " ";
        std:: cout << '\n';
    }
    std:: cout << '\n';
}


//for ListGraph
void ListGraph:: add_edge(int v, int u) {
    if ((u != v) && (std:: find (lst[u].begin(), lst[u].end(), v) == lst[u].end())) {
        lst[v].push_back(u);
        lst[u].push_back(v);
    }
}

void ListGraph:: output() {
    for (int i = 0; i < lst.size(); ++i) {
        for (int j = 0; j < lst[i].size(); ++j)
            std:: cout << lst[i][j] << " ";
        std:: cout << '\n';
    }
    std:: cout << '\n';
}

bool ListGraph:: has_edge(int v, int u) const {
    return std:: find (lst[v].begin(), lst[v].end(), u) != lst[v].end();
}
//


void dfsSearch(IGraph& gr, std:: vector<color>& colors, int v) {
    colors[v] = GRAY;
    std:: vector<int> a;
    gr.get_adj(v, a);
    std:: cout << v << " ";
    for (int i = 0; i < a.size(); ++i)
        if (colors[a[i]] == WHITE)
            dfsSearch(gr, colors, a[i]);

    colors[v] = BLACK;
}

void dfs(IGraph& gr) {
    std:: vector<color> colors(gr.count());
    for (int v = 0; v < gr.count(); ++v)
        if (colors[v] == WHITE)
            dfsSearch(gr, colors, v);
}

void dfsSearchPrevious(IGraph& gr, std:: vector<color>& colors, std:: vector<int>& parents, int v) {
    colors[v] = GRAY;
    std:: vector<int> a;
    gr.get_adj(v, a);
    //    std:: cout << v << " ";
    for (int i = 0; i < a.size(); ++i)
        if (colors[a[i]] == WHITE) {
            parents[a[i]] = v;
            dfsSearchPrevious(gr, colors, parents, a[i]);
        }
    colors[v] = BLACK;
}

void dfsParent(IGraph& gr) {
    std:: vector<color> colors(gr.count());
    std:: vector<int> parents(gr.count());
    std:: fill(parents.begin(), parents.end(), -1);
    for (int v = 0; v < gr.count(); ++v)
        if (colors[v] == WHITE)
            dfsSearchPrevious(gr, colors, parents, v);
    std:: cout << '\n';
    for (int v = 0; v < gr.count(); ++v)
        std:: cout << parents[v] << ' ';
    std:: cout << '\n';
    for (int v = 0; v < gr.count(); ++v)
        std:: cout << colors[v] << ' ';
}

bool dfsSearchFirstWayRec(IGraph& gr, std:: vector<color>& colors, std:: vector<int>& parents, int v, int v1) {
    colors[v] = GRAY;
    std:: vector<int> a;
    gr.get_adj(v, a);
    for (int u : a) {
        if (colors[u] == WHITE) {
            parents[u] = v;
            if (u == v1)
                return true;
            if (dfsSearchFirstWayRec(gr, colors, parents, u, v1))
                return true;
        }
    }
    colors[v] = BLACK;
    return false;
}

void dfsSearchFirstWay(IGraph& gr, int v0, int v1) {
    std:: vector<int> parents(gr.count());
    std:: vector<color> colors(gr.count());
    std:: fill(parents.begin(), parents.end(), -1);
    if (dfsSearchFirstWayRec(gr, colors, parents, v0, v1)) {
        std:: vector<int> path;
        int v = v1;
        path.push_back(v1);
        while (v != v0) {
            path.push_back(parents[v]);
            v = parents[v];
        }
        std:: reverse(path.begin(), path.end());
        for (int u : path)
            std:: cout << u << " ";
    }
    else
        std:: cout << "No path";
}


DfsSearchFirstWay:: DfsSearchFirstWay(IGraph& graph, int v0, int v1)
    : gr(graph), parents(graph.count()), visited(graph.count()), v1(v1)
{
    std:: fill(parents.begin(), parents.end(), -1);
    if (rec(v0)) {
        std:: vector<int> path;
        int v = v1;
        path.push_back(v1);
        while (v != v0) {
            path.push_back(parents[v]);
            v = parents[v];
        }
        std:: reverse(path.begin(), path.end());
        for (int u : path)
            std:: cout << u << " ";
    }
    else
        std:: cout << "No path";
}

bool DfsSearchFirstWay:: rec(int v) {
    visited[v] = true;
    std:: vector<int> a;
    gr.get_adj(v, a);
    for (int u : a) {
        if (!visited[u]) {
            parents[u] = v;
            if (u == v1)
                return true;
            if (rec(u))
                return true;
        }
    }
    return false;
}


//можно использовать для поиска пути
void bfs(IGraph& gr, int v0) {
    std:: vector<int> parents (gr.count(), -1);
    std:: vector<color> colors(gr.count());
    std:: queue<int> q;
    q.push(v0);
    colors[v0] = GRAY;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        colors[v] = BLACK;
        std:: vector<int> a;
        gr.get_adj(v, a);
        for (int u : a)
            if (colors[u] == WHITE) {
                parents[u] = v;
                q.push(u);
                colors[u] = GRAY;
            }
    }
    for (int u : parents)
        std:: cout << u << " ";
}

void bfsLength(IGraph& gr, int v0) {
    std:: vector<int> d(gr.count(), -1);
    std:: vector<bool> visited(gr.count());

    std:: queue<int> q;
    q.push(v0);
    visited[v0] = true;
    d[v0] = 0;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        visited[v] = true;
        std:: vector<int> a;
        gr.get_adj(v, a);
        for (int u : a)
            if (visited[u] == false) {
                q.push(u);
                visited[u] = true;
                d[u] = d[v] + 1;
            }
    }
    for (int u : d)
        std:: cout << u << " ";
}

void minWay(IGraph& gr, int v0, int v1) {
    std:: vector<int> d(gr.count(), -1);
    std:: vector<int> p (gr.count(), -1);

    std:: queue<int> q;
    q.push(v0);
    d[v0] = 0;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        std:: vector<int> a;
        gr.get_adj(v, a);
        for (int u : a)
            if (d[u] == -1) {
                q.push(u);
                p[u] = v;
                d[u] = d[v] + 1;
                if (u == v1) {
                    std:: vector<int> w;
                    int v = v1;
                    w.push_back(v1);
                    while (v != v0) {
                        w.push_back(p[v]);
                        v = p[v];
                    }
                    std:: reverse(w.begin(), w.end());
                    for (int u : w)
                        std:: cout << u << " ";
                    std:: cout << '\n';
                    std:: cout << d[u];
                    return;
                }
            }
    }
    std:: cout << "No way";
}

