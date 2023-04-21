#include <stdio.h>
#include <stdlib.h>

typedef struct stack_int {
    int *array;
    int tam_max;
    int top;
} stack_int;

typedef struct stack_char {
    char *string;
    int tam_max;
    int top;
} stack_char;

stack_int *create_stack_int (int tam_max)
{
    stack_int *s = (stack_int *) malloc(sizeof(stack_int));

    if (s == NULL)
        exit(1);

    s->array = (int *) malloc(tam_max * sizeof(int));
    s->tam_max = tam_max;
    s->top = -1;

    return s;
}

stack_char *create_stack_char (int tam_max)
{
    stack_char *s = (stack_char *) malloc(sizeof(stack_char));

    if (s == NULL)
        exit(1);

    s->string = (char *) malloc(tam_max * sizeof(char));
    s->tam_max = tam_max;
    s->top = -1;

    return s;
}

void push_int (stack_int *s, int elem)
{
    if (s->top + 1 == s->tam_max)
    {
        printf("Nao foi possivel adicionar o numero - Pilha cheia\n");
        exit(1);
    }
    else
    {
        s->top++;
        s->array[s->top] = elem;
    }
}

int pop_int (stack_int *s)
{
    if (s->top == -1)
    {
        printf("Pilha esta vazia!\n");
        exit(1);
    }
    else
    {
        int aux = s->array[s->top];
        s->array[s->top] = 0;
        s->top -= 1;

        return aux;
    }
}

void push_char (stack_char *s, char elem)
{
    if (s->top + 1 == s->tam_max)
    {
        printf("Pilha esta cheia!\n");
        exit(1);
    }
    else
    {
        s->top++;
        s->string[s->top] = elem;
    }
}

char pop_char (stack_char *s)
{
    if (s->top == -1)
    {
        printf("Pilha esta cheia|\n");
        exit(1);
    }
    else
    {
        char aux = s->string[s->top];
        s->string[s->top] = '\0';
        s->top--;

        return aux;
    }
}

char peek_char (stack_char *s)
{
    return s->string[s->top];
}

int peek_char (stack_char *s)
{
    return s->string[s->top];
}



int char_to_int (char string[], int *i, int num)
{
    if (string[*i] <= 57 && string[*i] >= 48)
    {
        num *= 10;
        num += ((int)string[*i] % 48);
        
        *i = *i + 1;

        return char_to_int(string, i, num);
    }

    return num;
}

void print_stack_int (stack_int *s)
{
    if (s->top == -1)
    {
        printf("Pilha está vazia!\n");
        exit(1);
    }

    for (int i = s->top; i >= 0; i--)
    {
        if (i == 0)
        {
            printf("%d\n", s->array[i]);
        }
        else
        {
            printf("%d ", s->array[i]);
        }
    }
    
}

void print_stack_char (stack_char *s)
{
    if (s->top == -1)
    {
        printf("Pilha está vazia!\n");
        exit(1);
    }

    for (int i = s->top; i >= 0; i--)
    {
        if (i == 0)
        {
            printf("%c\n", s->string[i]);
        }
        else
        {
            printf("%c ", s->string[i]);
        }
    }
    
}

int prioridy (char c)
{
    if (c == '+' || c == '-')
    {
        return 0;
    }
    else if (c == '*' || c == '/')
    {
        return 1;
    }
}

int main()
{
    char string[100];
    scanf("%[^\n]s", string);
    
    stack_int *s_int    = create_stack_int(50);
    stack_char *s_char  = create_stack_char(50);
    stack_int *aux_int    = create_stack_int(50);
    stack_char *aux_char  = create_stack_char(50);

    for (int i = 0; (string[i] != '\0') && (i < 100); i++)
    {
        if (string[i] >= 48 && string[i] <= 57)
        {
            int num = char_to_int(string, &i, 0);
            push_int(s_int, num);
        }

        if (string[i] == '+' || string[i] == '-' || 
            string[i] == '*' || string[i] == '/')
        {
            if (prioridy(string[i]) > prioridy(s_char->string[s_char->top]))
            {
                push_char(s_char, string[i]);
            }
            else
            {
                
            }
        }
    }
    
    print_stack_int(s_int);
    print_stack_char(s_char);

    printf("%s\n", string);

    return 0;
}