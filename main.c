#include "hasse.h"
#include "matrix.h"
#include "tarjan.h"
#include <stdio.h>

int main() {
  const char *filename = "data/exemple_hasse1.txt";
  adjacency_list *graph = readGraph(filename);

  if (graph == NULL) {
    printf("error reading file\n");
    return 1;
  }

  printf("=== Part 2: Tarjan Algorithm ===\n");
  printf("Original graph:\n");
  display_adjacency_list(graph);

  // Run Tarjan algorithm to find SCCs
  t_tarjan_vertex **tarjan_graph = convert_tarjan(graph);
  graph_c partition = tarjan(tarjan_graph, graph);

  printf("\nFound %d strongly connected components:\n", partition.nb_vertices);
  for (int i = 0; i < partition.nb_vertices; i++) {
    printf("SCC %d: {", i + 1);
    for (int j = 0; j < partition.list[i].nb_vertices; j++) {
      printf("%d", partition.list[i].list[j]->id + 1);
      if (j < partition.list[i].nb_vertices - 1)
        printf(", ");
    }
    printf("}\n");
  }

  printf("\n=== Part 3: Matrix Operations ===\n");

  // Step 1: Create matrix from adjacency list
  t_matrix M = newMatrixFromAdj(graph);
  printf("\nTransition Matrix M:\n");
  displayMatrix(M);

  // Calculate M^3
  printf("\nCalculating M^3...\n");
  t_matrix M_power = createEmptyMatrix(M.sx);
  t_matrix M_temp = createEmptyMatrix(M.sx);
  copyMatrix(M, M_power);

  for (int i = 1; i < 3; i++) {
    multiplyMatrices(M_power, M, M_temp);
    copyMatrix(M_temp, M_power);
  }
  printf("M^3:\n");
  displayMatrix(M_power);

  // Calculate M^7
  printf("\nCalculating M^7...\n");
  copyMatrix(M, M_power);
  for (int i = 1; i < 7; i++) {
    multiplyMatrices(M_power, M, M_temp);
    copyMatrix(M_temp, M_power);
  }
  printf("M^7:\n");
  displayMatrix(M_power);

  // Find convergence
  printf("\nFinding stationary distribution (epsilon < 0.01)...\n");
  t_matrix M_n = createEmptyMatrix(M.sx);
  t_matrix M_n_plus_1 = createEmptyMatrix(M.sx);
  copyMatrix(M, M_n);

  int n = 1;
  float diff;
  do {
    multiplyMatrices(M_n, M, M_n_plus_1);
    diff = matrixDifference(M_n, M_n_plus_1);
    copyMatrix(M_n_plus_1, M_n);
    n++;
  } while (diff >= 0.01 && n < 1000);

  printf("Converged at M^%d (difference: %.6f)\n", n, diff);
  displayMatrix(M_n);

  // Step 2: Calculate stationary distribution for each SCC
  printf("\n=== Step 2: Stationary Distributions per SCC ===\n");
  for (int i = 0; i < partition.nb_vertices; i++) {
    if (partition.list[i].nb_vertices > 1 ||
        M.data[partition.list[i].list[0]->id][partition.list[i].list[0]->id] >
            0) {
      printf("\nSCC %d: {", i + 1);
      for (int j = 0; j < partition.list[i].nb_vertices; j++) {
        printf("%d", partition.list[i].list[j]->id + 1);
        if (j < partition.list[i].nb_vertices - 1)
          printf(", ");
      }
      printf("}\n");

      t_matrix sub = subMatrix(M, partition, i);
      printf("Submatrix for SCC %d:\n", i + 1);
      displayMatrix(sub);

      // Calculate period
      int period = getPeriod(sub);
      printf("Period: %d\n", period);

      // Calculate stationary distribution
      if (period == 1) {
        t_matrix sub_n = createEmptyMatrix(sub.sx);
        t_matrix sub_n_plus_1 = createEmptyMatrix(sub.sx);
        copyMatrix(sub, sub_n);

        int steps = 1;
        float sub_diff;
        do {
          multiplyMatrices(sub_n, sub, sub_n_plus_1);
          sub_diff = matrixDifference(sub_n, sub_n_plus_1);
          copyMatrix(sub_n_plus_1, sub_n);
          steps++;
        } while (sub_diff >= 0.001 && steps < 1000);

        printf("Stationary distribution (converged at step %d):\n", steps);
        displayMatrix(sub_n);

        freeMatrix(&sub_n);
        freeMatrix(&sub_n_plus_1);
      } else {
        printf("Periodic class - no unique stationary distribution\n");
      }

      freeMatrix(&sub);
    }
  }

  // Free memory
  int nb_vertices = graph->nb_vertices;

  for (int i = 0; i < nb_vertices; i++) {
    cell *current = graph->lists[i].head;
    while (current != NULL) {
      cell *temp = current;
      current = current->next;
      free(temp);
    }
  }
  free(graph->lists);
  free(graph);

  for (int i = 0; i < partition.nb_vertices; i++) {
    free(partition.list[i].list);
  }
  free(partition.list);

  for (int i = 0; i < nb_vertices; i++) {
    free(tarjan_graph[i]);
  }
  free(tarjan_graph);

  freeMatrix(&M);
  freeMatrix(&M_power);
  freeMatrix(&M_temp);
  freeMatrix(&M_n);
  freeMatrix(&M_n_plus_1);

  return 0;
}