#include "hasse.h"
#include "tarjan.h"
#include <stdio.h>

int main()
{
  const char *filename = "data/exemple_hasse1.txt";
  adjacency_list *graph = readGraph(filename);

  if (graph == NULL)
  {
    printf("error reading file\n");
    return 1;
  }

  printf("- Part 2: Tarjan Validation -\n\n");

  printf("Loaded graph:\n");
  display_adjacency_list(graph);

  t_tarjan_vertex **tarjan_graph = convert_tarjan(graph);
  graph_c partition = tarjan(tarjan_graph, graph);

  printf("\nTarjan's algorithm results:\n");
  printf("Found %d SCC(s):\n\n", partition.nb_vertices);

  for (int i = 0; i < partition.nb_vertices; i++)
  {
    printf("SCC %d: {", i + 1);
    for (int j = 0; j < partition.list[i].nb_vertices; j++)
    {
      printf("%d", partition.list[i].list[j]->id + 1);
      if (j < partition.list[i].nb_vertices - 1)
        printf(", ");
    }
    printf("}\n");
  }

  int nb_vertices = graph->nb_vertices;
  for (int i = 0; i < nb_vertices; i++)
  {
    cell *current = graph->lists[i].head;
    while (current != NULL)
    {
      cell *temp = current;
      current = current->next;
      free(temp);
    }
  }
  free(graph->lists);
  free(graph);

  for (int i = 0; i < partition.nb_vertices; i++)
  {
    free(partition.list[i].list);
  }
  free(partition.list);

  for (int i = 0; i < nb_vertices; i++)
  {
    free(tarjan_graph[i]);
  }
  free(tarjan_graph);

  return 0;
}
