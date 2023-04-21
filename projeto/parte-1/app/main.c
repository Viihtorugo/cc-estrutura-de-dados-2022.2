#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE_WINDOW 1000.0

void display()
{
}

int main(int argc, char **argv)
{
  double x, y;
  int pos;

  while (1)
  {
    printf("Informe a largura do terreno: ");
    scanf("%lf", &x);

    printf("Informe o comprimento do terreno: ");
    scanf("%lf", &y);

    if (x < 30 || y < 30)
    {
      if (x <= y)
      {
        if (x * x > 300)
          break;
      }
      else
      {
        if (y * y > 300)
          break;
      }

      printf("O terreno não consegue construir a casa planejada!\n");
    }
  }

  while (1)
  {
    printf("\nMenu:\n");
    printf("1 - Norte para cima;\n");
    printf("2 - Norte para direita;\n");
    printf("3 - Norte para baixo;\n");
    printf("4 - Norte para esquerda;\n");
    printf("Digite uma opcao para definir o norte: ");
    scanf("%d", &pos);

    if (pos >= 1 && pos <= 4)
      break;

    printf("Digite uma opcao valida!\n\n");
  }

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE);
  glutInitWindowSize(MAX_SIZE_WINDOW, MAX_SIZE_WINDOW);
  glutInitWindowPosition(100, 0);
  glutCreateWindow("Planta baixa de casa");
  gluOrtho2D(0.0, MAX_SIZE_WINDOW, 0.0, MAX_SIZE_WINDOW);

  display();

  glutMainLoop();

  return 0;
}