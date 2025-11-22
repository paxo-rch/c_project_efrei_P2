#include "utils.h"
#include "hasse.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

cell *create_cell(int arrival_vertex, float probability) {
/*
This function creates a new cell from an arrival vertex and probability.
*/
    cell *new_cell = (cell *)malloc(sizeof(cell));
    if (new_cell == NULL) {
        printf("memory error for cell");
        exit(1);
    }
    new_cell->arrival_vertex = arrival_vertex;
    new_cell->probability = probability;
    new_cell->next = NULL;
    return new_cell;
}

list *create_empty_list() {
    /*
    This function creates an empty list.
    */
    list *new_list = (list *)malloc(sizeof(list));
    if (new_list == NULL) {
        printf("memory error for list");
        exit(1);
    }
    new_list->head = NULL;
    return new_list;
}

void add_cell_to_list(list *l, int arrival_vertex, float probability) {
    /*
    This function adds a cell to a list.
    */
    cell *new_cell = create_cell(arrival_vertex, probability);
    new_cell->next = l->head;
    l->head = new_cell;
}

void display_list(list *l) {
    /*
    This function displays a list.
    */
    cell *current = l->head;
    while (current != NULL) {
        printf("-> (%d, %.2f) ", current->arrival_vertex, current->probability);
        current = current->next;
    }
    printf("-> NULL\n");
}

adjacency_list *create_empty_adjacency_list(int nb_vertices) {
    /*
    This function creates an empty adjacency list with a given number of vertices.
    */
    adjacency_list *adj_list = (adjacency_list *)malloc(sizeof(adjacency_list));
    if (adj_list == NULL) {
        printf("memory error for adjacency list");
        exit(1);
    }
    adj_list->nb_vertices = nb_vertices;
    adj_list->lists = (list *)malloc(nb_vertices * sizeof(list));
    if (adj_list->lists == NULL) {
        printf("memory error adjacency list");
        free(adj_list);
        exit(1);
    }
    for (int i = 0; i < nb_vertices; i++) {
        adj_list->lists[i].head = NULL; 
    }
    return adj_list;
}

void display_adjacency_list(adjacency_list *adj_list) {
    /*
    This function displays the adjacency list.
    */
    printf("Adjacency List:\n");
    for (int i = 0; i < adj_list->nb_vertices; i++) {
        printf("list of vertex %d: ", i + 1);
        display_list(&adj_list->lists[i]);
    }
}

char *getID(int i)
{
    // translate from 1,2,3, .. ,500+ to A,B,C,..,Z,AA,AB,...
    static char buffer[10];
    char temp[10];
    int index = 0;

    i--; // Adjust to 0-based index
    while (i >= 0)
    {
        temp[index++] = 'A' + (i % 26);
        i = (i / 26) - 1;
    }

    // Reverse the string to get the correct order
    for (int j = 0; j < index; j++)
    {
        buffer[j] = temp[index - j - 1];
    }
    buffer[index] = '\0';

    return buffer;
}
