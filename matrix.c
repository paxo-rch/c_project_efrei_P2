#include "matrix.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

t_matrix newMatrixFromAdj(
    adjacency_list *adj_list) { // create a matrix from an adjacent list
  t_matrix m;
  m.sx = adj_list->nb_vertices;
  m.sy = adj_list->nb_vertices;
  m.data = (float **)malloc(m.sx * sizeof(float *));

  for (int i = 0; i < m.sx; i++) {
    m.data[i] = (float *)calloc(
        m.sy, sizeof(float)); // it easier to initialize the matrix with 0
  }

  for (int i = 0; i < adj_list->nb_vertices; i++) {
    cell *current = adj_list->lists[i].head;

    while (current != NULL) {
      int j = current->arrival_vertex - 1; // We use 0 based indexes, so -1
      if (j >= 0 && j < m.sy) {
        m.data[i][j] = current->probability;
      }
      current = current->next;
    }
  }

  return m;
}

t_matrix
createEmptyMatrix(int n) // create an empty n x n matrix filled with zeros
{
  t_matrix m;
  m.sx = n;
  m.sy = n;
  m.data = (float **)malloc(n * sizeof(float *));

  for (int i = 0; i < n; i++) {
    m.data[i] = (float *)calloc(n, sizeof(float));
  }

  return m;
}

void copyMatrix(t_matrix from, t_matrix to) // Copy matrix from to to
{
  for (int i = 0; i < from.sx; i++) {
    for (int j = 0; j < from.sy; j++) {
      to.data[i][j] = from.data[i][j];
    }
  }
}

void multiplyMatrices(t_matrix a, t_matrix b,
                      t_matrix out) // Multiply two matrices: result = a * b
{
  // First set to 0 because it is a sum
  for (int i = 0; i < out.sx; i++) {
    for (int j = 0; j < out.sy; j++) {
      out.data[i][j] = 0;
    }
  }

  // main calculations
  for (int i = 0; i < a.sx; i++) {
    for (int j = 0; j < b.sy; j++) {
      for (int k = 0; k < a.sy; k++) {
        out.data[i][j] += a.data[i][k] * b.data[k][j];
      }
    }
  }
}

float matrixDifference(t_matrix a, t_matrix b) // abs(a - b)
{
  float diff = 0;
  for (int i = 0; i < a.sx; i++) {
    for (int j = 0; j < a.sy; j++) {
      diff += fabs(a.data[i][j] - b.data[i][j]);
    }
  }
  return diff;
}

void displayMatrix(t_matrix m) // display the matrix
{
  printf("Matrix %dx%d:\n", m.sx, m.sy);
  for (int i = 0; i < m.sx; i++) {
    for (int j = 0; j < m.sy; j++) {
      printf("%.4f ", m.data[i][j]);
    }
    printf("\n");
  }
}

void freeMatrix(t_matrix *m) // Free matrix
{
  for (int i = 0; i < m->sx; i++) {
    free(m->data[i]);
  }
  free(m->data);
  m->data = NULL;
  m->sx = 0;
  m->sy = 0;
}

t_matrix subMatrix(t_matrix matrix, graph_c partition,
                   int compo_index) // extract submatrix for a specific SCC
{
  t_class *component = &partition.list[compo_index];
  int size = component->nb_vertices;

  t_matrix sub;
  sub.sx = size;
  sub.sy = size;
  sub.data = (float **)malloc(size * sizeof(float *));

  for (int i = 0; i < size; i++) {
    sub.data[i] = (float *)calloc(size, sizeof(float));
  }

  // copy the data
  for (int i = 0; i < size; i++) {
    int row_idx = component->list[i]->id;
    for (int j = 0; j < size; j++) {
      int col_idx = component->list[j]->id;
      sub.data[i][j] = matrix.data[row_idx][col_idx];
    }
  }

  return sub;
}

int gcd(int *vals, int nbvals) // GCD function for periodicity calculation
{
  if (nbvals == 0)
    return 0;
  int result = vals[0];
  for (int i = 1; i < nbvals; i++) {
    int a = result;
    int b = vals[i];
    while (b != 0) {
      int temp = b;
      b = a % b;
      a = temp;
    }
    result = a;
  }
  return result;
}

int getPeriod(t_matrix sub_matrix) // Calculate period of a class
{
  int n = sub_matrix.sx;
  int *periods = (int *)malloc(n * sizeof(int));
  int period_count = 0;
  int cpt = 1;
  t_matrix power_matrix = createEmptyMatrix(n);
  t_matrix result_matrix = createEmptyMatrix(n);
  copyMatrix(sub_matrix, power_matrix);

  for (cpt = 1; cpt <= n; cpt++) {
    int diag_nonzero = 0;
    for (int i = 0; i < n; i++) {
      if (power_matrix.data[i][i] > 0) {
        diag_nonzero = 1;
      }
    }
    if (diag_nonzero) {
      periods[period_count] = cpt;
      period_count++;
    }
    multiplyMatrices(power_matrix, sub_matrix, result_matrix);
    copyMatrix(result_matrix, power_matrix);
  }

  int period = gcd(periods, period_count);

  free(periods);
  freeMatrix(&power_matrix);
  freeMatrix(&result_matrix);

  return period;
}
