#include <stdio.h>
#include "hasse.h"
#include "tarjan.h"

int main() {
    const char *filename = "data/exemple_hasse1.txt";
    adjacency_list *graph = readGraph(filename);

    if (graph == NULL) {
        printf("error reading file\n");
        return 1;
    }
    t_tarjan_vertex** tarjan_graph = convert_tarjan(graph);
    graph_c out_tarjan = tarjan(tarjan_graph, graph);
    adjacency_list* converted_graph = convert_hasse(&out_tarjan, graph);

    display_adjacency_list(converted_graph);

    is_markov_graph(converted_graph);

    generate_mermaid_file(converted_graph, "mermaid_graph.mmd");

    for (int i = 0; i < converted_graph->nb_vertices; i++) {  // Free the whole graph
        cell *current = converted_graph->lists[i].head;
        while (current != NULL) {
            cell *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(converted_graph->lists);
    free(converted_graph);

    return 0;
}