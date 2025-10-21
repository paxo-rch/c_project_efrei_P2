#ifndef UTILS_H
#define UTILS_H

typedef struct cell {
    int arrival_vertex;
    float probability;
    struct cell* next_edge;
} cell;

typedef struct list {
    struct cell* head;
} plist;

typedef struct adjacency_list {
    struct cell* edges[100];
    int size;
} adjacency_list;
#endif
