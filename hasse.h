#ifndef __HASSE_H__
#define __HASSE_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct cell {
    int arrival_vertex;
    float probability;
    struct cell *next;
} cell;

typedef struct list {
    cell *head;
} list;

typedef struct adjacency_list {
    int nb_vertices;
    list *lists;
} adjacency_list;

cell *create_cell(int arrival_vertex, float probability);
list *create_empty_list();
void add_cell_to_list(list *l, int arrival_vertex, float probability);
void display_list(list *l);
adjacency_list *create_empty_adjacency_list(int nb_vertices);
void display_adjacency_list(adjacency_list *adj_list);
adjacency_list *readGraph(const char *filename);
void is_markov_graph(adjacency_list *adj_list);
char *getId(int num);
void generate_mermaid_file(adjacency_list *adj_list, const char *filename);

#endif