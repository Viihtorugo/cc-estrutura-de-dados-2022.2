#include "utils.h"

void print_window(int x, int y)
{
  glBegin(GL_LINES);

  glVertex2i(x - 10, y - 10);
  glVertex2i(x + 10, y + 10);

  glVertex2i(x - 10, y + 10);
  glVertex2i(x + 10, y - 10);

  glEnd();
  glFlush();
}

// Modificar a função posteriormente
void print_door(int x, int y)
{
  glBegin(GL_LINE_STRIP);

  glVertex2i(x - 10, y - 10);
  glVertex2i(x + 10, y + 10);

  glEnd();
  glFlush();
}

void print_lines_vertices(list *head, int op)
{
  // cria a função de desenhar 
  glBegin(GL_LINE_STRIP);

  if (op == 1)
  {
	  // Altera a cor do desenho para vermelho
	  glColor3f(1.0f, 0.0f, 0.0f);
  }
  else if (op == 2)
  {
    // Altera a cor do desenho para verde
	  glColor3f(0.0f, 1.0f, 0.0f);
  }
  else if (op == 3)
  {
    // Altera a cor do desenho para azul
	  glColor3f(0.0f, 0.0f, 1.0f);
  }
  else
  {
    //Altera a cor do desenho para branco
    glColor3f (1.0, 1.0, 1.0);
  }

  while (head != NULL)
  {
    //imprime as linhas certas da cor escolhida
    glVertex2d(head->x, head->y);
    head = head->next;
  }

  //acabar 
  glEnd();
  // executar 
  glFlush();
}

int area_with_matrix(int **matrix, int size)
{
  int area = 0;

  for (int i = 0; i < size; i++)
  {
    if (i + 1 == size)
    {
      area += matrix[i][0] * matrix[0][1];
    }
    else
    {
      area += matrix[i][0] * matrix[i + 1][1];
    }
  }

  for (int i = 0; i < size; i++)
  {
    if (i + 1 == size)
    {
      area -= matrix[0][0] * matrix[i][1];
    }
    else
    {
      area -= matrix[i + 1][0] * matrix[i][1];
    }
  }

  if (area < 0)
    area *= (-1);

  area /= 2;

  return area;
}