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

typedef t_tarjan_vertex** graph_v;
typedef t_class* graph_c;

void push(stack* s, t_tarjan_vertex* e){ s->stack[s->len++]; }
t_tarjan_vertex* pop(stack* s) { return s->stack[--s->len]; }

t_tarjan_vertex** convert_tarjan(adjacency_list* list);

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
            
            t_tarjan_vertex* w = NULL;
            do 
            {
                t_tarjan_vertex* w = pop(p);
                w->is_in_stack = false;
                class.list[class.nb_vertices++] = w;
            } while (w != v);
            

            graph->list = realloc(graph->list, sizeof(t_class) * (graph->nb_vertices + 1));
            graph->list[graph->nb_vertices++] = class.list;
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