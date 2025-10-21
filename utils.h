#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>

typedef struct cell {
    int arrival_vertex;
    float probability;
    struct cell* next;
} cell;

typedef struct list {
    struct cell* head;
} list;

cell *create_cell(int arrival_vertex, float probability);
list *create_empty_list();
void add_cell_to_list(list *l, int arrival_vertex, float probability);
void display_list(list *l);
char *getId(int num);

#endif
