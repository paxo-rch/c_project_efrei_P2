#include "tarjan.h"

t_tarjan_vertex** convert_tarjan(adjacency_list* list)
{
    t_tarjan_vertex** vertices = malloc(sizeof(t_tarjan_vertex*) * list->nb_vertices);

    for (int i = 0; i < list->nb_vertices; i++)
    {
        t_tarjan_vertex* vertex = malloc(sizeof(t_tarjan_vertex));
        vertex->id = i;
        vertex->number = -1;
        vertex->accessible_number = -1;
        
        vertices[i] = vertex;
    }
    return vertices;
}

void push(stack* s, t_tarjan_vertex* e){ s->stack[s->len++] = e; }
t_tarjan_vertex* pop(stack* s) { return s->stack[--s->len]; }


void parse(t_tarjan_vertex* v, graph_v* g, graph_c* graph, int* num, stack* p, adjacency_list* adj_list)
{
    v->number = *num;
    v->accessible_number = *num;
    
    (*num)++;
    push(p, v);
    v->is_in_stack = true;

    struct cell* cur = adj_list->lists[v->id].head;
    while (cur != NULL)
    {
        // Adjust 1-based index from adjacency list to 0-based index for array access
        int neighbor_idx = cur->arrival_vertex - 1;
        
        if (neighbor_idx < 0 || neighbor_idx >= adj_list->nb_vertices) {
            cur = cur->next;
            continue;
        }

        if ((*g)[neighbor_idx]->number == -1)
        {
            parse((*g)[neighbor_idx], g, graph, num, p, adj_list);
            v->accessible_number = 
                (v->accessible_number < (*g)[neighbor_idx]->accessible_number) ? 
                v->accessible_number : (*g)[neighbor_idx]->accessible_number;
        } else
        {
            if ((*g)[neighbor_idx]->is_in_stack)
            {
                v->accessible_number = 
                    (v->accessible_number < (*g)[neighbor_idx]->number) ? 
                    v->accessible_number : (*g)[neighbor_idx]->number;
            }
        }
        cur = cur->next;
    }

    if (v->number == v->accessible_number)
    {
        t_class class;
        class.nb_vertices = 0;
        class.list = malloc(sizeof(t_tarjan_vertex*) * adj_list->nb_vertices);
        class.name = NULL;
        
        t_tarjan_vertex* w = NULL;
        do 
        {
            if (p->len <= 0) {
                break;
            }
            w = pop(p);
            w->is_in_stack = false;
            class.list[class.nb_vertices++] = w;
        } while (w != v);
        

        graph->list[graph->nb_vertices++] = class;
    }
}

graph_c tarjan(graph_v g, adjacency_list* adj_list)
{
    int n = 0;
    stack p = {0};
    graph_c partition;
    partition.nb_vertices = 0;
    partition.list = malloc(sizeof(t_class) * adj_list->nb_vertices);

    for (int i = 0; i < adj_list->nb_vertices; i++)
    {
        if (g[i]->number == -1)
        {
            parse(g[i], &g, &partition, &n, &p, adj_list);
        }
    }
    return partition;
}