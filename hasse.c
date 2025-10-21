#include <malloc.h>
#include "hasse.h"
#include <math.h> 
adjacency_list *readGraph(const char *filename) {
    FILE *file = fopen(filename, "rt");
    int nbvert, start, end;
    float proba;
    adjacency_list *adj_list = NULL;

    if (file == NULL) {
        perror("Could not open file for reading");
        exit(EXIT_FAILURE);
    }

    if (fscanf(file, "%d", &nbvert) != 1) {
        perror("Could not read number of vertices");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    adj_list = create_empty_adjacency_list(nbvert);

    while (fscanf(file, "%d %d %f", &start, &end, &proba) == 3) {
        if (start >= 1 && start <= nbvert) {
            add_cell_to_list(&adj_list->lists[start - 1], end, proba);
        } else {
            fprintf(stderr, "Invalid vertex number encountered: %d\n", start);
        }
    }

    fclose(file);
    return adj_list;
}

void is_markov_graph(adjacency_list *adj_list) {
    printf("\nChecking if the graph is a Markov graph:\n");
    int is_markov = 1;
    for (int i = 0; i < adj_list->nb_vertices; i++) {
        float sum_probabilities = 0.0;
        cell *current = adj_list->lists[i].head;
        while (current != NULL) {
            sum_probabilities += current->probability;
            current = current->next;
        }

        if (fabs(sum_probabilities - 1.0) > 0.01) {
            printf("The graph is not a Markov graph.\n");
            printf("The sum of the probabilities of vertex %d is %.2f\n", i + 1, sum_probabilities);
            is_markov = 0;
        }
    }

    if (is_markov) {
        printf("The graph is a Markov graph.\n");
    }
}

void generate_mermaid_file(adjacency_list *adj_list, const char *filename) {
    FILE *file = fopen(filename, "wt");
    if (file == NULL) {
        perror("Could not open file for writing Mermaid graph");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "---\n");
    fprintf(file, "config:\n");
    fprintf(file, " layout: elk\n");
    fprintf(file, " theme: neo\n");
    fprintf(file, " look: neo\n");
    fprintf(file, "---\n");
    fprintf(file, "flowchart LR\n");

    for (int i = 0; i < adj_list->nb_vertices; i++) {
        char *id = getId(i + 1);
        fprintf(file, "%s((%d))\n", id, i + 1);
        free(id); 
    }

    for (int i = 0; i < adj_list->nb_vertices; i++) {
        cell *current = adj_list->lists[i].head;
        char *from_id = getId(i + 1);
        while (current != NULL) {
            char *to_id = getId(current->arrival_vertex);
            fprintf(file, "%s -->|%.2f|%s\n", from_id, current->probability, to_id);
            free(to_id);
            current = current->next;
        }
        free(from_id); 
    }

    fclose(file);
    printf("Mermaid graph generated successfully to %s\n", filename);
}