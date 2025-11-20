#ifndef TARJAN_H
#define TARJAN_H

#include "hasse.h"
#include "utils.h"
#include <stdbool.h>

#define MAX_STACK 100

typedef struct t_tarjan_vertex
{
    int id;     // id of the node
    int number;
    int accessible_number;
    int is_in_stack;

} t_tarjan_vertex;



typedef struct t_class
{
    char* name;
    int nb_vertices;
    t_tarjan_vertex** list;
} t_class;

typedef struct stack
{
    int len;
    t_tarjan_vertex* stack[MAX_STACK];
} stack;

typedef struct partition
{
    int nb_vertices;
    t_class* list;
} partition;

typedef t_tarjan_vertex** graph_v;
typedef partition graph_c;

void push(stack* s, t_tarjan_vertex* e);
t_tarjan_vertex* pop(stack* s);

t_tarjan_vertex** convert_tarjan(adjacency_list* list);

void parse(t_tarjan_vertex* v, graph_v* g, graph_c* graph, int* num, stack* p, adjacency_list* adj_list);
graph_c tarjan(graph_v g, adjacency_list* adj_list);

#endif