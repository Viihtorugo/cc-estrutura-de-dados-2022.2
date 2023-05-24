#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct stack
{
    int elem;
    struct stack *next;
} stack;

int is_empty(stack *top)
{
    return (int)(top == NULL);
}

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
                num = (num * 10) + ((int) input[i]) % 48;
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
            printf("Entrada invalida, digite apenas números positivos ou zero\n\n");
        }
        else
        {
            break;
        }
    }

    return num;
}

stack *push(stack *top, int elem)
{
    stack *new_top = (stack *)malloc(sizeof(stack));

    if (is_empty(new_top))
    {
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }

    new_top->elem = elem;
    new_top->next = top;

    return new_top;
}

int pop(stack **top)
{
    if (is_empty(*top))
    {
        printf("Erro: a pilha esta vazia!\n");
        exit(1);
    }

    stack *aux = *top;
    int r = aux->elem;

    *top = (*top)->next;
    aux->next = NULL;

    free(aux);

    return r;
}

int count_stack(stack *top)
{
    stack *aux = top;
    int count = 0;

    while (aux != NULL)
    {
        aux = aux->next;
        count += 1;
    }

    return count;
}

stack *shuffle(stack *top, int size)
{
    stack *new_top = NULL;

    while (top != NULL)
    {
        int r = random() % size;
        stack *aux = NULL;

        while (top != NULL && r + 1 != 0)
        {
            aux = push(aux, pop(&top));
            r -= 1;
        }

        new_top = push(new_top, pop(&aux));

        while (aux != NULL)
            top = push(top, pop(&aux));

        size -= 1;
    }

    return new_top;
}

void print_cartas(stack *topo)
{
    stack *aux = topo;

    while (aux != NULL)
    {
        printf("%d ", aux->elem);
        aux = aux->next;
    }

    printf("\n");
}

int main()
{
    srand(time(NULL));

    int n = 0;

    while (1)
    {
        n = get_number("Digite a quantidade de cartas: ");

        if (n <= 0 || n > 53)
        {
            printf("\n----- Erro ---- \nUm baralho possui no máximo 52 cartas e o minimo é 1 carta!\n\n");
        }
        else
        {
            break;
        }
    }

    printf("\nOs baralhos tem %d carta(s)!\n", n);
    int cartas[n], num[13] = {0}, i = 0, elem;

    while (i < n)
    {
        printf("%d carta -> ", i + 1);
        elem = get_number("Digite o valor da carta: ");

        if ((elem >= 1 && elem <= 13) && num[elem - 1] != 4)
        {
            cartas[i] = elem;
            num[elem - 1] += 1;
            i += 1;
        }
        else
        {
            printf("\nPossíveis erros:\n");
            printf("1 - O valor das cartas de um baralho está no intervalo de 1 a 13!\n");
            printf("2 - Um baralho só pode ter 4 cartas com a mesma valor!\n\n");
            
            for (int j = 0; j < 13; j++)
                printf("Carta com valor %d possui %d carta(s) no baralho\n", j + 1, num[j]);

            printf("\n");
        }
    }

    stack *player_a = NULL;
    stack *player_b = NULL;

    for (int i = 0; i < n; i++)
    {
        player_a = push(player_a, cartas[i]);
        player_b = push(player_b, cartas[i]);
    }

    int size_a = count_stack(player_a), size_b = count_stack(player_b);
    ;

    printf("\n------\n");
    while (player_a != NULL && player_b != NULL)
    {
        player_a = shuffle(player_a, size_a);
        player_b = shuffle(player_b, size_b);

        printf("Baralho A: ");
        print_cartas(player_a);
        printf("Baralho B: ");
        print_cartas(player_b);
        printf("\n");

        int a = pop(&player_a);
        int b = pop(&player_b);

        printf("Jogador A tirou o numero %d e jogador B tirou o numero %d.\n", a, b);

        if (a > b)
        {
            size_b -= 1;
            printf("1 - jogador A ganhou a rodada!\n");
            player_a = push(player_a, a);
        }
        else if (a < b)
        {
            size_a -= 1;
            printf("2 - jogador B ganhou a rodada!\n");
            player_b = push(player_b, b);
        }
        else
        {
            size_a -= 1;
            size_b -= 1;
            printf("0 - jogadores empataram a rodada!\n");
        }
        printf("\n");
    }
    printf("------\n\n");

    if (player_a == NULL && player_b == NULL)
    {
        printf("Empate!\n");
    }
    else if (player_a == NULL)
    {
        printf("Jogador B ganhou a partida!\n");
    }
    else
    {
        printf("Jogador A ganhou a partida!\n");
    }

    return 0;
}