#ifndef ROOM_H
#define ROOM_H

typedef struct room room;

list *add_vertex(int x, int y, list *head);
void print_lines_vertices(list *head, int op);
list *search_of_area_size(int matrix[][2], int sum_matrix[][2], int size, int area);

#endif