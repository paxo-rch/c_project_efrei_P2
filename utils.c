#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

static char *getID(int i)
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
cell create_cell(int arrival_vertex, float probability)
{
    cell new_cell;
    new_cell.arrival_vertex = arrival_vertex;
    new_cell.probability = probability;
    new_cell.next_edge = NULL;
    return new_cell;
}
plist create_list()
{
    plist new_list;
    new_list.head = NULL;
    return new_list;
}
void append_to_list(plist* list, cell new_cell)
{
    cell* new_node = (cell*)malloc(sizeof(cell));
    if (!new_node)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    *new_node = new_cell;
    new_node->next_edge = NULL;

    if (list->head == NULL)
    {
        list->head = new_node;
    }
    else
    {
        cell* current = list->head;
        while (current->next_edge != NULL)
        {
            current = current->next_edge;
        }
        current->next_edge = new_node;
    }
}
void display_list(plist* list)
{
    cell* current = list->head;
    while (current != NULL)
    {
        printf("-> (%s, %.2f) ", getID(current->arrival_vertex), current->probability);
        current = current->next_edge;
    }
    printf("\n");
}
void display_adjacency_list(adjacency_list* adj_list)
{
    for (int i = 0; i < adj_list->size; i++)
    {
        printf("%s: ", getID(i + 1));
        cell* current = adj_list->edges[i];
        while (current != NULL)
        {
            printf("-> (%s, %.2f) ", getID(current->arrival_vertex), current->probability);
            current = current->next_edge;
        }
        printf("\n");
    }
}

adjacency_list create_adjacency_list(int size)
{
    adjacency_list new_adj_list;
    new_adj_list.size = size;
    for (int i = 0; i < size; i++)
    {
        new_adj_list.edges[i] = create_list();
    }
    return new_adj_list;
}