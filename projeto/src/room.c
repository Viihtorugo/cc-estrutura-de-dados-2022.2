#include "room.h"

typedef struct room
{
  int **vertices;
  int size;
  window *w;
  door *d;
  struct room *next;
} room;

room *add_room(int x, int y, room *r)
{
  list *new_vertex = (list *)malloc(sizeof(list));

  if (new_vertex == NULL)
  {
    printf("Falta de memória no dispositivo\n");
    exit(1);
  }

  new_vertex->x = x;
  new_vertex->y = y;
  new_vertex->next = NULL;

  if (head == NULL)
  {
    return new_vertex;
  }
  else
  {
    list *aux = head;

    while (aux->next != NULL)
      aux = aux->next;

    aux->next = new_vertex;

    return head;
  }
}



list *search_of_area_size(int matrix[][2], int sum_matrix[][2], int size, int area)
{

  int area_cal = area_with_matrix(matrix, size);

  while (area_cal < area)
  {
    for (int i = 0; i < size; i++)
    {
      matrix[i][0] += sum_matrix[i][0];
      matrix[i][1] += sum_matrix[i][1];
    }

    int aux = area_with_matrix(matrix, size);

    if (aux > area)
      break;

    area_cal = aux;
  }

  list *l = (list *) malloc(sizeof(list));

  if (l == NULL)
  {
    printf("Falta de memoria no dispositivo\n");
    exit(1);
  }

  l = NULL;

  for (int i = 0; i < size; i++)
  {
    l = add_vertex(matrix[i][0], matrix[i][1], l);

    if (i + 1 == size)
      l = add_vertex(matrix[0][0], matrix[0][1], l);
  }

  return l;
}