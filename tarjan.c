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