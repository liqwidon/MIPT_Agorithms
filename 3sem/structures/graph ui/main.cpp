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

    long st0, st1, tax;
    std:: cin >> st0 >> st1 >> tax;

    RickGraph gr(M, a, b);

    RickStenGraph graph(&gr, st0, st1, tax);

    vector<long> way;

    dijkstra(&graph, x, y, way);

    return 0;
}
