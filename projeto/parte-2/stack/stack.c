#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct stack{
    int elem;
    struct stack *next;
} stack;

int is_empty (stack *top)
{
    return (int) (top == NULL);
}

stack *push (stack *top, int elem)
{
    stack *new_top = (stack *) malloc (sizeof(stack));

    if (is_empty(new_top))
    {
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }

    new_top->elem = elem;
    new_top->next = top;

    return new_top;
}

int pop (stack **top)
{
    stack *aux = *top;
    int r = aux->elem;

    *top = (*top)->next;
    aux->next = NULL;

    free(aux);

    return r;
}

int count_stack (stack *top)
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

stack *shuffle (stack *top, int size)
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

int main ()
{
    srand(time(NULL));
    
    int n = 0;

    while (n <= 0 || n > 100)
    {
        printf("Digite a quantidade de cartas: ");
        scanf("%d", &n);

        if (n <= 0 || n > 100)
            printf("O numero de cartas deve ser maior que 0 e menor que 101!\n");
    }

    stack *player_a = NULL;
    stack *player_b = NULL;
    
    printf("Digite %d numeros: ", n);
    int elem;

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &elem);
        player_a = push(player_a, elem);
        player_b = push(player_b, elem);
    }
    
    int size_a = count_stack(player_a), size_b = count_stack(player_b);;

    printf("\n------\n");
    while (player_a != NULL && player_b != NULL)
    {
        player_a = shuffle(player_a, size_a);
        player_b = shuffle(player_b, size_b);

        int a = pop(&player_a);
        int b = pop(&player_b);

        printf("Jogador A tirou o numero %d e jogador B tirou o numero %d.\n", a, b);

        if (a > b)
        {
            size_a -= 1;
            printf("1 - jogador A ganhou a rodada!\n");
            player_b = push(player_b, b);
        }
        else if (a < b)
        {
            size_b -= 1;
            printf("2 - jogador B ganhou a rodada!\n");
            player_a = push(player_a, a);
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
        printf("Jogador A ganhou a partida!\n");
    }
    else
    {
        printf("Jogador B ganhou a partida!\n");
    }

    return 0;
}