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

adjacency_list* convert_hasse(graph_v g, int nb_vertices, adjacency_list* adj_list) {
    adjacency_list* new_adj_list = create_empty_adjacency_list(nb_vertices);

    for (int i = 0; i < nb_vertices; i++) {
        struct cell* cur = adj_list->lists[g[i]->id].head;
        while (cur != NULL) {
            add_cell_to_list(&new_adj_list->lists[i], g[cur->arrival_vertex]->id, cur->probability);
            cur = cur->next;
        }
    }

    return new_adj_list;
}

void push(stack* s, t_tarjan_vertex* e){ s->stack[s->len++]; }
t_tarjan_vertex* pop(stack* s) { return s->stack[--s->len]; }


void parse(t_tarjan_vertex* v, graph_v* g, graph_c graph, int num, stack* p, adjacency_list* adj_list)
{
    v->number = num;
    v->accessible_number = num;
    
    num++;
    push(p, v);
    v->is_in_stack = true;

    struct cell* cur = adj_list->lists[v->id].head;
    for (int i = 0; cur->next != NULL; i++)
    {
        if ((*g)[cur->arrival_vertex]->number == -1)
        {
            parse((*g)[cur->arrival_vertex],g,graph, num, p, adj_list);
            v->accessible_number = 
                (v->accessible_number < (*g)[cur->arrival_vertex]->accessible_number) ? 
                v->accessible_number : (*g)[cur->arrival_vertex]->accessible_number;
        } else
        {
            if ((*g)[cur->arrival_vertex]->is_in_stack)
            {
                v->accessible_number = 
                    (v->accessible_number < (*g)[cur->arrival_vertex]->number) ? 
                    v->accessible_number : (*g)[cur->arrival_vertex]->number;
            }
        }

        if (v->number == v->accessible_number)
        {
            t_class class;
            class.nb_vertices = 0;
            class.list = malloc(sizeof(t_tarjan_vertex*) * adj_list->nb_vertices);
            class.name = NULL;
            
            /*t_tarjan_vertex* w = NULL;              // Probably segfault here
            do 
            {
                t_tarjan_vertex* w = pop(p);
                w->is_in_stack = false;
                class.list[class.nb_vertices++] = w;
            } while (w != v);
            

            graph.list[graph.nb_vertices++] = class;*/
        }
    }
}

graph_c tarjan(graph_v g, adjacency_list* adj_list)
{
    int n = 0;
    stack p = {0};
    graph_c partition;

    for (int i = 0; i < adj_list->nb_vertices; i++)
    {
        if (g[i]->number == -1)
        {
            parse(g[i], &g, partition, n, &p, adj_list);
        }
    }
}