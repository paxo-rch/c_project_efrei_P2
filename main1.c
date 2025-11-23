#include "hasse.h"
#include <stdio.h>

int main()
{
  const char *filename = "data/exemple1.txt";
  adjacency_list *graph = readGraph(filename);

  if (graph == NULL)
  {
    printf("error reading file\n");
    return 1;
  }

  printf("- Part 1: Validations -\n\n");

  printf("Step 1: Graph loaded from %s\n", filename);
  display_adjacency_list(graph);

  printf("\nStep 2: Markov graph validation\n");
  is_markov_graph(graph);

  printf("\nStep 3: Mermaid file generation\n");
  generate_mermaid_file(graph, "mermaid_graph.mmd");

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

  return 0;
}
