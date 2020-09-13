#include "graph.h"

///пример функции инициализации графа через обертку IGraph
void initGraph(IGraph& gr) {
    gr.add_edge(0, 0);
    gr.add_edge(0, 1);
    gr.add_edge(0, 3);
    gr.add_edge(1, 2);
    gr.add_edge(1, 3);
    gr.output();
}

int main() {
    ListGraph gr(10);
    gr.add_edge(0, 1);
    gr.add_edge(0, 2);
    gr.add_edge(1, 3);
    gr.add_edge(1, 4);
    gr.add_edge(3, 4);
    gr.add_edge(4, 2);
    gr.add_edge(2, 5);
    gr.add_edge(2, 6);
    gr.add_edge(7, 8);
    gr.add_edge(7, 9);
    gr.add_edge(9, 8);
    gr.add_edge(6, 7);
    gr.add_edge(0 ,9);

//    DfsSearchFirstWay(gr, 1 , 5);

    minWay(gr, 3, 9);

    return 0;
}
