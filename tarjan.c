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