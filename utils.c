#include "hasse.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

cell *create_cell(int arrival_vertex, float probability) {
    cell *new_cell = (cell *)malloc(sizeof(cell));
    if (new_cell == NULL) {
        perror("Failed to allocate memory for cell");
        exit(EXIT_FAILURE);
    }
    new_cell->arrival_vertex = arrival_vertex;
    new_cell->probability = probability;
    new_cell->next = NULL;
    return new_cell;
}

list *create_empty_list() {
    list *new_list = (list *)malloc(sizeof(list));
    if (new_list == NULL) {
        perror("Failed to allocate memory for list");
        exit(EXIT_FAILURE);
    }
    new_list->head = NULL;
    return new_list;
}

void add_cell_to_list(list *l, int arrival_vertex, float probability) {
    cell *new_cell = create_cell(arrival_vertex, probability);
    new_cell->next = l->head;
    l->head = new_cell;
}

void display_list(list *l) {
    cell *current = l->head;
    while (current != NULL) {
        printf("-> (%d, %.2f) ", current->arrival_vertex, current->probability);
        current = current->next;
    }
    printf("-> NULL\n");
}

adjacency_list *create_empty_adjacency_list(int nb_vertices) {
    adjacency_list *adj_list = (adjacency_list *)malloc(sizeof(adjacency_list));
    if (adj_list == NULL) {
        perror("Failed to allocate memory for adjacency list");
        exit(EXIT_FAILURE);
    }
    adj_list->nb_vertices = nb_vertices;
    adj_list->lists = (list *)malloc(nb_vertices * sizeof(list));
    if (adj_list->lists == NULL) {
        perror("Failed to allocate memory for lists in adjacency list");
        free(adj_list);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < nb_vertices; i++) {
        adj_list->lists[i].head = NULL; 
    }
    return adj_list;
}

void display_adjacency_list(adjacency_list *adj_list) {
    printf("Adjacency List:\n");
    for (int i = 0; i < adj_list->nb_vertices; i++) {
        printf("List for vertex %d: ", i + 1);
        display_list(&adj_list->lists[i]);
    }
}

char *getId(int num) {
    char *id = (char *)malloc(sizeof(char) * 3);
    if (id == NULL) {
        perror("Failed to allocate memory for ID");
        exit(EXIT_FAILURE);
    }

    if (num <= 26) {
        id[0] = 'A' + (num - 1);
        id[1] = '\0';
    } else {
        id[0] = 'A' + ((num - 1) / 26) - 1;
        id[1] = 'A' + ((num - 1) % 26);
        id[2] = '\0';
    }
    return id;
}
