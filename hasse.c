#include <malloc.h>
#include "hasse.h"
#include <math.h> 
adjacency_list *readGraph(const char *filename) {
    FILE *file = fopen(filename, "rt");
    int nbvert, start, end;
    float proba;
    adjacency_list *adj_list = NULL;

    if (file == NULL) {
        printf("could not open file");
        exit(1);
    }

    if (fscanf(file, "%d", &nbvert) != 1) {
        printf("error reading vertices");
        fclose(file);
        exit(1);
    }

    adj_list = create_empty_adjacency_list(nbvert);

    while (fscanf(file, "%d %d %f", &start, &end, &proba) == 3) {
        if (start >= 1 && start <= nbvert) {
            add_cell_to_list(&adj_list->lists[start - 1], end, proba);
        } else {
            fprintf(stderr, "invalid vertex number: %d\n", start);
        }
    }

    fclose(file);
    return adj_list;
}

void is_markov_graph(adjacency_list *adj_list) {
    int is_markov = 1;
    for (int i = 0; i < adj_list->nb_vertices; i++) {
        float sum = 0.0;
        cell *current = adj_list->lists[i].head;
        while (current != NULL) {
            sum += current->probability;
            current = current->next;
        }

        if (fabs(sum - 1.0) > 0.01) {
            printf("not a markov graph\n");
            is_markov = 0;
        }
    }

    if (is_markov) {
        printf("markov graph\n");
    }
}

void generate_mermaid_file(adjacency_list *adj_list, const char *filename) {
    FILE *file = fopen(filename, "wt");
    if (file == NULL) {
        printf("could not create mermaid file\n");
        exit(1);
    }

    fprintf(file, "---\n");
    fprintf(file, "config:\n");
    fprintf(file, " layout: elk\n");
    fprintf(file, " theme: neo\n");
    fprintf(file, " look: neo\n");
    fprintf(file, "---\n");
    fprintf(file, "flowchart LR\n");
    printf("DEBUG: 1\n");

    for (int i = 0; i < adj_list->nb_vertices; i++) {
        char *id = getID(i + 1);
        fprintf(file, "%s((%d))\n", id, i + 1);
    }


    for (int i = 0; i < adj_list->nb_vertices; i++) {
        cell *current = adj_list->lists[i].head;
        char *from_id = getID(i + 1);
        while (current != NULL) {
            char *to_id = getID(current->arrival_vertex);
            fprintf(file, "%s -->|%.2f|%s\n", from_id, current->probability, to_id);
            current = current->next;
        }
    }
    printf("DEBUG: 2\n");

    fclose(file);
    printf("mermaid file generated");
}