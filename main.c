#include <stdio.h>
#include "hasse.h"

int main() {
    printf("Hello, Markov Graph Project!\n");

    const char *filename = "data/exemple1.txt";
    adjacency_list *graph = readGraph(filename);

    if (graph == NULL) {
        fprintf(stderr, "Failed to read graph from %s\n", filename);
        return EXIT_FAILURE;
    }

    display_adjacency_list(graph);

    is_markov_graph(graph);

    generate_mermaid_file(graph, "mermaid_graph.mmd");

    for (int i = 0; i < graph->nb_vertices; i++) {
        cell *current = graph->lists[i].head;
        while (current != NULL) {
            cell *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(graph->lists);
    free(graph);

    return 0;
}