#include <stdio.h>
#include <stdlib.h>

typedef struct elevador {
	int corredor;
	int andar;
} elevador;

int get_number(char *string)
{
    int num = 0;

    while (1)
    {
        char input[100];
        printf("%s", string);
        scanf(" %[^\n]s", input);

        int erro = 0, i = 0;

        while (input[i] != '\0')
        {
            if (input[i] == '0' ||
                input[i] == '1' ||
                input[i] == '2' ||
                input[i] == '3' ||
                input[i] == '4' ||
                input[i] == '5' ||
                input[i] == '6' ||
                input[i] == '7' ||
                input[i] == '8' ||
                input[i] == '9')
            {
                num = (num * 10) + ((int)input[i]) % 48;
                i += 1;
            }
            else
            {
                erro = 1;
                break;
            }
        }

        if (erro)
        {
            printf("\n----- ERRO -----\n");
            printf("Entrada invalida, digite apenas números\n\n");
        }
        else
        {
            break;
        }
    }

    return num;
}

void elevador_mais_prox(int posicao[3][300], int andar_esperado, int corredor_esperado, int posicao_elevador[][2])
{
    int array[15] = 0;
}

int main()
{
    int posicao[300][3] = {0};
    elevador elevadores[15];
    
    elevadores[0]->corredor = 0;
    elevadores[0]->andar = 0;
    elevadores[1]->corredor = 0;
    elevadores[1]->andar = 10;
	
	for (int i = 0; i < 300; i++)
		for (int j = 0; j < 3; j++)
			posicao[i][j] = 0;
		
	for (int i = 0; i < 15; i++)
		posicao[elevadores[i]->andar][elevadores[i]->corredor] = 1;
	
			

    while (1)
    {
        int qtd = get_number("Informe a quantidade de passageiros: ");
        int init;

        while (1)
        {
            init = get_number("Qual andar vocês estão: ");

            if (init <= 0 || init >= 301)
            {
                printf("\n---- ERRO ----\n");
                printf("Andar informado não existe, intervalo de 1 até 300\n\n");
            }
            else
            {
                init -= 1;
                break;
            }
        }

        while (qtd != 0)
        {

            int corredor;

            while (1)
            {
                corredor = get_number("Informe o numero do corredor: ");
                
                if (init <= 0 || init >= 4)
                {
                    printf("\n---- ERRO ----\n");
                    printf("Os corredores tem apenas esses valores: 1, 2 ou 3\n\n");
                }
                else
                {
                    corredor -= 1;
                    break;
                }
            }

            int qtd_elevador = 0;
            while (1)
            {
                qtd_elevador = get_number("Informe a quantidade de passageiros que vai entrar no elevador: ");
                
                if (qtd_elevador <= 0 || qtd_elevador > qtd)
                {
                    printf("\n---- ERRO ----\n");
                    printf("Os corredores tem apenas esses valores: 1, 2 ou 3\n\n");
                }
                else
                {
                    break;
                }
            }
            
            int end;
            while (qtd_elevador != 0)
            {
                end = get_number("Qual andar vocês desejam ir: ");
                
                if (end <= 0 || end >= 301)
                {
                    printf("\n---- ERRO ----\n");
                    printf("Andar informado não existe, intervalo de 1 até 300\n\n");
                }
                else
                {
                    end -= 1;
                    break;
                }

                int saiu_do_elevador;
                while (1)
                {
                    saiu_do_elevador = get_number("Quantos sairam do elevador: ");

                    if (saiu_do_elevador < 0 || saiu_do_elevador > qtd_elevador)
                    {
                        printf("\n---- ERRO ----\n");
                        printf("Quantidade de passageiros invalido, intervalo de 0 até %d\n\n", qtd_elevador);
                    }
                    else
                    {
                        break;
                    }
                }

                qtd_elevador -= saiu_do_elevador;
            }
            
        }
    }

    return 0;
}
