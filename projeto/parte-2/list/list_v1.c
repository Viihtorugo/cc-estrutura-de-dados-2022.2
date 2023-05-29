#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int get_number(char *string)
{
    int num = 0, neg = 0;

    while (1)
    {
        char input[100];
        printf("%s", string);
        scanf(" %[^\n]s", input);

        int erro = 0, i = 0;

        if (input[i] == '-')
        {
            neg = -1;
            i += 1;
        }

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

    if (neg == -1)
        num = num * neg;

    return num;
}

typedef struct elevador
{
    int corredor_atual;
    int andar_atual;
    int andar_dest;
    int ocupado;
    int passageiros;
    int subir;
} elevador;

void print_elevadores(elevador *elevadores)
{
    for (int i = 0; i < 15; i++)
    {
        if (i + 1 < 10)
        {
            if (elevadores[i].andar_atual < 10)
            {
                printf("Elevador 0%d: 00%d andar e %d corredor\n", i + 1, elevadores[i].andar_atual, elevadores[i].corredor_atual);
            }
            else if (elevadores[i].andar_atual < 100)
            {
                printf("Elevador 0%d: 0%d andar e %d corredor\n", i + 1, elevadores[i].andar_atual, elevadores[i].corredor_atual);
            }
            else
            {
                printf("Elevador 0%d: %d andar e %d corredor\n", i + 1, elevadores[i].andar_atual, elevadores[i].corredor_atual);
            }
        }
        else
        {
            if (elevadores[i].andar_atual < 10)
            {
                printf("Elevador %d: 00%d andar e %d corredor\n", i + 1, elevadores[i].andar_atual, elevadores[i].corredor_atual);
            }
            else if (elevadores[i].andar_atual < 100)
            {
                printf("Elevador %d: 0%d andar e %d corredor\n", i + 1, elevadores[i].andar_atual, elevadores[i].corredor_atual);
            }
            else
            {
                printf("Elevador %d: %d andar e %d corredor\n", i + 1, elevadores[i].andar_atual, elevadores[i].corredor_atual);
            }
        }
    }
}

void tratamento_colisao(int i, int k, elevador elevadores[])
{
    printf("\n---- TRATAMENTO DE COLISÃO ----\n\n");

    while (elevadores[i].andar_atual % 10 != 0)
    {
        int prox_andar;

        if (elevadores[i].subir)
        {
            prox_andar = elevadores[i].andar_atual + 1;
        }
        else
        {
            prox_andar = elevadores[i].andar_atual - 1;
        }

        printf("\n");
        print_elevadores(elevadores);
        printf("\n");

        elevadores[i].andar_atual = prox_andar;

        if (elevadores[i].ocupado == 0)
            elevadores[i].andar_dest = prox_andar;
    }

    printf("\n\n----- MODIFICANDO O CORREDOR! -----\n");
    
    int prox_corredor, atualizar_corretor;

    if (elevadores[i].corredor_atual == 3)
    {
        atualizar_corretor = elevadores[i].corredor_atual;
        elevadores[i].corredor_atual -= 1;
    }
    else
    {
        atualizar_corretor = elevadores[i].corredor_atual;
        elevadores[i].corredor_atual += 1;
    }


    printf("\n");
    print_elevadores(elevadores);
    printf("\n");

    printf("\n\n----- FIM DO TRATAMENTO DE COLISÃO -----\n");
}

int colisao(int index, elevador elevadores[])
{

    int count = 1;

    while (count <= 10)
    {
        for (int i = 0; i < 15; i++)
        {
            int aux;

            if (elevadores[index].subir)
            {
                aux = elevadores[index].andar_atual + count;
            }
            else
            {
                aux = elevadores[index].andar_atual - count;
            }

            if (aux == elevadores[i].andar_atual)
                if (elevadores[i].corredor_atual == elevadores[index].corredor_atual)
                    return i;
        }

        count += 1;
    }

    return -1;
}

int andar_elevador_dif_andar_dest(elevador elevadores[])
{
    for (int i = 0; i < 15; i++)
        if ((elevadores[i].andar_atual != elevadores[i].andar_dest) || elevadores[i].ocupado)
            return 1;

    return 0;
}

void iniciar_elevadores(elevador elevadores[])
{
    for (int i = 0; i < 15; i++)
    {
        if ((elevadores[i].andar_atual != elevadores[i].andar_dest) || elevadores[i].ocupado)
        {
            if (elevadores[i].andar_atual == elevadores[i].andar_dest && elevadores[i].passageiros == 0)
            {
                printf("\n---- ELEVADOR %d: ANDAR %d ----\n", i + 1, elevadores[i].andar_atual);
                int andar_dest;
                
                while (1)
                {
                    andar_dest = get_number("\nDigite o andar que deseja ir: ");

                    if (andar_dest > 300 || andar_dest < 1)
                    {
                        printf("\n---- ERRO ----\n");
                        printf("\n1 - O sistema não suporta números negativos!\n");
                        printf("2 - O sistema não suporta números acima de 300 ou abaixo 1, pois o intervalo dos andares é de 1 até 300!\n");
                    }
                    else
                    {
                        break;
                    }
                }

                elevadores[i].passageiros = 1;
                elevadores[i].andar_dest = andar_dest;

                if (elevadores[i].andar_atual > andar_dest)
                {
                    elevadores[i].subir = 0;
                }
                else
                {
                    elevadores[i].subir = 1;
                }
            }
            else if (elevadores[i].andar_atual == elevadores[i].andar_dest && elevadores[i].passageiros)
            {
                printf("\n----- ELEVADOR %d LIBERADO -----\n", i + 1);
                elevadores[i].passageiros = 0;
                elevadores[i].ocupado = 0;
            }
            else
            {
                if (elevadores[i].subir)
                {
                    elevadores[i].andar_atual += 1;
                }
                else
                {
                    elevadores[i].andar_atual -= 1;
                }

                int index_colisao = colisao(i, elevadores);

                if (index_colisao != -1)
                {
                    tratamento_colisao(i, index_colisao, elevadores);
                }
            }
        }
    }

    printf("\n ---- Movimentos ---- \n\n");
    print_elevadores(elevadores);
    printf("\n");
    
}

int elevador_mais_prox(int andar_dest, elevador elevadores[])
{
    int menor = 0;

    for (int i = 0; i < 15; i++)
    {
        if (elevadores[i].ocupado == 0)
        {
            int dist_i = elevadores[i].andar_atual - andar_dest;
            int dist_menor = elevadores[menor].andar_atual - andar_dest;

            if (dist_i < 0)
                dist_i *= (-1);

            if (dist_menor < 0)
                dist_menor *= (-1);

            if ((dist_i < dist_menor) || elevadores[menor].ocupado)
                menor = i;
        }
    }

    printf("\nElevador %d: %d andar e %d corredor\n\n", menor + 1, elevadores[menor].andar_atual, elevadores[menor].corredor_atual);
    return menor;
}

int andar_de_destino_ja_foi_alocado(int andar_dest, elevador elevadores[])
{

    for (int i = 0; i < 15; i++)
        if (elevadores[i].andar_dest == andar_dest && elevadores[i].ocupado)
            return i;

    return -1;
}

int main()
{
    srand(time(NULL));

    elevador *elevadores = (elevador *)malloc(15 * sizeof(elevador));

    if (elevadores == NULL)
    {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }

    for (int i = 0; i < 15; i++)
    {
        elevadores[i].andar_atual = 0;
        elevadores[i].corredor_atual = 0;
        elevadores[i].andar_dest = 0;
        elevadores[i].ocupado = 0;
        elevadores[i].passageiros = 0;
        elevadores[i].subir = 0;
    }

    int andar = 60;

    for (int i = 0; i < 15; i += 3)
    {
        elevadores[i].andar_atual = andar - 1;
        elevadores[i].andar_dest = andar - 1;
        elevadores[i].corredor_atual = 1;
        elevadores[i + 1].andar_atual = andar - 2;
        elevadores[i + 1].andar_dest = andar - 2;
        elevadores[i + 1].corredor_atual = 2;
        elevadores[i + 2].andar_atual = andar - 3;
        elevadores[i + 2].andar_dest = andar - 3;
        elevadores[i + 2].corredor_atual = 3;
        andar += 60;
    }

    printf("\n---- POSIÇÃO INCIAL DOS ELEVADORES ----\n\n");
    print_elevadores(elevadores);
    printf("\n---------------------------------------\n");

    while (1)
    {
        int andar = 0;

        while (1)
        {
            printf("Digite 0 caso não tenha requisição: ");
            andar = get_number("\nDigite o andar da requisição: ");

            if (andar > 300 || andar < 0)
            {
                printf("\n---- ERRO ----\n");
                printf("\n1 - O sistema não suporta números negativos!\n");
                printf("2 - O sistema não suporta números acima de 300, pois o intervalo dos andares é de 1 até 300!\n");
            }
            else
            {
                break;
            }
        }

        if (andar != 0)
        {
            int index = andar_de_destino_ja_foi_alocado(andar, elevadores);

            if (index == -1)
            {
                index = elevador_mais_prox(andar, elevadores);

                elevadores[index].andar_dest = andar;
                elevadores[index].ocupado = 1;
                elevadores[index].passageiros = 0;

                if (andar > elevadores[index].andar_atual)
                {
                    printf("---- Subir! --- \n");
                    elevadores[index].subir = 1;
                }
                else
                {
                    printf("---- Descer! --- \n");
                    elevadores[index].subir = 0;
                }
            }
            else
            {
                printf("\nO elevador %d está nesse andar ou passará está ocupado!\n", index + 1);

                elevadores[index].ocupado = 1;
                elevadores[index].passageiros = 0;
            }
        }

        iniciar_elevadores(elevadores);
    }

    printf("\n--------- FIM DO SISTEMA ---------\n");

    return 0;
}
