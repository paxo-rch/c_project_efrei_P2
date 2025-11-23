#ifndef __HASSE_H__
#define __HASSE_H__

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

typedef struct adjacency_list
{
    int nb_vertices;
    list *lists;
} adjacency_list;

adjacency_list *create_empty_adjacency_list(int nb_vertices);
void display_adjacency_list(adjacency_list *adj_list);
adjacency_list *readGraph(const char *filename);
void is_markov_graph(adjacency_list *adj_list);
void generate_mermaid_file(adjacency_list *adj_list, const char *filename);

#endif
