#ifndef MATRIX_H
#define MATRIX_H

#include "hasse.h"
#include "tarjan.h"

typedef struct t_matrix {
  int sx;
  int sy;
  float **data;
} t_matrix;

t_matrix newMatrixFromAdj(adjacency_list *adj_list);
t_matrix createEmptyMatrix(int n);
void copyMatrix(t_matrix from, t_matrix to);
void multiplyMatrices(t_matrix a, t_matrix b, t_matrix result);
float matrixDifference(t_matrix a, t_matrix b);
void displayMatrix(t_matrix m);
void freeMatrix(t_matrix *m);

t_matrix subMatrix(t_matrix matrix, graph_c partition, int compo_index);

int gcd(int *vals, int nbvals);
int getPeriod(t_matrix sub_matrix);

#endif
