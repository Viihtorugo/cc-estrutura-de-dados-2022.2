#include <stdio.h>
#include <stdlib.h>

/* 
    VERSÃO SALA DE AULA

    1 - Este programa falta tratamento da entrada e tratamento de erros
    2 - Organização da fila e lista de espera
    3 - Falta um menu para o usuario
*/

typedef struct queue
{
    int *array;
    int size;
    int size_max;
} queue;

queue *create_queue(int size_max)
{
    queue *q = (queue *) malloc (sizeof(queue));

    if (q == NULL)
    {
        printf("Erro ao criar a estrutura de fila!\n");
        exit(1);
    }

    q->array = (int *) malloc (size_max * sizeof(int));

    if (q->array == NULL)
    {
        printf("Erro ao criar a estrutura de fila!\n");
        exit(1);
    }

    q->size = 0;
    q->size_max = size_max;

    for (int i = q->size; i < q->size_max; i++)
        q->array[i] = -1;

    return q;
}

void print_queue(queue *q)
{
    printf("Fila: ");

    for (int i = 0; i < q->size; i++)
    {
        if (i + 1 != q->size)
        {
            printf("%d ", q->array[i]);
        }
        else
        {
            printf("%d\n", q->array[i]);
        }
    }
}

int prioridade(int idade)
{
    if (idade < 5 || idade > 80)
    {
        return 0;
    }
    else if ((idade >= 5 && idade < 16) || (idade > 60 && idade <= 80))
    {
        return 1;
    }
    else
    {
        return 2;
    }
}

void print_prioridade(queue *q)
{
    printf("Prioridade: ");

    for (int i = 0; i < q->size; i++)
    {
        if (i + 1 != q->size)
        {
            printf("%d ", prioridade(q->array[i]));
        }
        else
        {
            printf("%d\n", prioridade(q->array[i]));
        }
    }
}

int enqueue(int elem, queue *q)
{
    if (q->size == q->size_max)
    {
        printf("Fila está cheia!\n");
        return 0;
    }
    else
    {
        int i = 0;

        while (i < q->size && prioridade(elem) >= prioridade(q->array[i]))
            i += 1;

        if (q->size == i)
        {
            q->array[q->size] = elem;
        }
        else
        {
            int aux = i, elem_array = q->array[i];

            while (i <= q->size && i + 1 != q->size_max)
            {
                int swap = q->array[i + 1];
                q->array[i + 1] = elem_array;
                elem_array = swap;

                i += 1;
            }

            q->array[aux] = elem;
        }

        q->size += 1;

        return 1;
    }
}

int dequeue(queue *q)
{
    if (q->size <= 0)
    {
        printf("Fila está vazia!\n");
        return -1;
    }
    else
    {
        int dequeued = q->array[0];

        for (int i = 0; (i < q->size) && (i + 1 != q->size); i++)
            q->array[i] = q->array[i + 1];

        q->array[q->size] = -1;

        q->size -= 1;

        return dequeued;
    }
}

int remove_in_queue(int n, queue *q)
{
    if (q->size == 0)
    {
        printf("Filá está vazia!\n");
        return -1;
    }
    else
    {
        n -= 1;

        int aux = q->array[n];

        while (n < q->size && n + 1 != q->size_max)
        {
            q->array[n] = q->array[n + 1];
            n += 1;
        }

        q->array[q->size] = -1;
        q->size -= 1;

        return aux;
    }
}

void remover_paciente(queue *q)
{
    int n = -1;

    while (1)
    {
        printf("\nCaso não queria remover só digitar -> 0\n");
        printf("Quantos pacientes desistiu quando estava na fila: ");
        scanf("%d", &n);

        if (n < 0 || n > q->size)
        {
            printf("\n-----ERRO----\n\nO sistema não suporta números negativo ou números acima de %d!\n", q->size);
        }
        else
        {
            break;
        }
    }

    for (int i = 0; i < n; i++)
    {
        int op = -1;

        while (1)
        {

            printf("\n-----Fila----\n");

            for (int i = 0; i < q->size; i++)
                printf("Pessoa %d: %d anos\n", i + 1, q->array[i]);

            printf("Digite informe o numero da pessoa na fila: ");
            scanf("%d", &op);

            if (op > 0 && op <= q->size)
            {
                break;
            }
            else
            {
                printf("\n-----ERRO----\n\nDigite um número entre 1 até %d!\n", q->size);
            }
        }

        if (remove_in_queue(op, q))
        {
            printf("\n");
            print_queue(q);
        }
        else
        {
            break;
        }
    }
}

void inserir_paciente(queue *q, queue *aux, int j)
{
    int n = -1;

    if (q->size + j >= q->size_max)
        printf("\n---- NÃO POSSUI VAGA PARA HOJE!---\n");

    while (1)
    {
        printf("\nCaso não queria adicionar só digitar, intervalo de 0 até 16 -> 0\n");
        printf("Quantos pacientes chegou: ");
        scanf("%d", &n);

        if (n < 0 || n > 16)
        {
            printf("\n-----ERRO----\n");

            if (n < 0)
                printf("\nO sistema não suporta números negativo numeros ou acima de 16!\n\n\n");
        }
        else
        {
            break;
        }
    }

    if (n > 0)
    {
        int array[n];

        printf("\nPara bebês recenascido digite 0!\n");
        for (int i = 0; i < n; i++)
        {
            int idade = -1;

            while (1)
            {
                printf("Informe a idade do paciente %d: ", i + 1);
                scanf("%d", &idade);

                if (idade < 0 || idade > 125)
                {
                    printf("\n-----ERRO----\n\nO sistema não suporta números negativo ou idade acima de 125 anos!\n");
                }
                else
                {
                    break;
                }
            }
            
            array[i] = idade;
        }
        
        for (int i = 0; i < n; i++)
        {
            if (q->size + j < q->size_max)
            {
                if (j > 8)
                {
                    if (prioridade(array[i]) == 2  && q->size + j + n >= q->size_max)
                    {
                        if (enqueue(array[i], aux))
                        {
                            printf("\n----- LISTA PARA OUTRO DIA -----\n\n");
                            print_queue(aux);
                        }
                        else
                        {
                            printf("\n----- A LISTA PARA OUTRO DIA ESTÁ CHEIA -----\n");
                        }
                    }
                    else
                    {
                        printf("\nPaciente adicionado: %d ano(s)!\n", array[i]);
                        enqueue(array[i], q);
                    }
                }
                else
                {
                    if (enqueue(array[i], q))
                    {
                        printf("\nPaciente adicionado: %d ano(s)!\n", array[i]);
                        print_queue(q);
                    }
                    else
                    {
                        printf("\n--- ERRO ---!\n");
                        exit(1);
                    }
                }
                
            }
            else
            {
                if (enqueue(array[i], aux))
                {
                    printf("\n----- LISTA PARA OUTRO DIA -----\n\n");
                    print_queue(aux);
                }
                else
                {
                    printf("\n----- A LISTA PARA OUTRO DIA ESTÁ CHEIA -----\n");
                }
            }
        }
    }
    

}

int main()
{

    queue *q = create_queue(16);
    queue *aux = create_queue(100);

    while (1)
    {
        printf("\n-------- INICIO DO EXPEDIENTE -------\n");
        int array[16];

        for (int i = 0; i < 16; i++)
        {
            inserir_paciente(q, aux, i);
            int idade = dequeue(q);

            array[i] = idade;
            if (idade == -1)
            {
                printf("\n---- %d consulta: sem paciente ----\n", i + 1);
            }
            else
            {
                printf("\n---- %d consulta: pessoa tem %d anos ----\n", i + 1, idade);
                printf("\n");
                
                if (i + 1 < 16 && q->size != 0)
                {
                    print_queue(q);
                    print_prioridade(q);
                }
            }

            if (i + 1 < 16)
                remover_paciente(q);
            
        }

        printf("\n----FIM DO EXPEDIENTE----\n");

        printf("\n------ FILA HOJE -----\n\n");
        for (int i = 0; i < 16; i++)
        {
            if (array[i] == -1)
            {
                printf("Paciente %d: não houve\n", 1 + 1);
            }
            else
            {
                printf("Paciente %d: %d ano(s)\n", i + 1, array[i]);
            }
        }
        printf("\n");
        

        for (int i = 0; i < q->size_max; i++)
            q->array[i] = -1;

        if (aux->size != 0)
        {
            printf("\n---- FILA PARA AMANHÃ ----\n");
            print_queue(aux);

            int n = -1;

            while (1)
            {
                printf("\nDigite 0 caso não queria adicionar nenhum paciente da lista de espera!\n");
                printf("Escolha entre 1 a 4 pacientes para amanhã: ");
                scanf("%d", &n);

                if (n > 0 && n < 5)
                {
                    break;
                }
                else
                {
                    printf("\n-----ERRO----\n\nO sistema pede um intervalo de 0 até no maximo 4!\n");
                }
            }
            
            for (int i = 0; i < n && aux->size != 0; i++)
            {
                int op = 0;

                printf("\n----- LISTA DE PESSOAS PARA OUTRO DIA -----\n");
                while (1)
                {
                    for (int k = 0; k < aux->size; k++)
                        printf("Pessoa %d: %d anos -> prioridade: %d\n", k + 1, aux->array[k], prioridade(aux->array[k]));

                    printf("Digite informe o numero da pessoa na fila: ");
                    scanf("%d", &op);

                    if (op > 0 && op <= aux->size)
                    {
                        break;
                    }
                    else
                    {
                        printf("\n-----ERRO----\n\nDigite um número entre 1 até %d!\n\n", aux->size);
                    }
                }
                
                int idade = remove_in_queue(op, aux);
                
                if (enqueue(idade, q))
                {
                    printf("\n---- Adicionado para amanhã -----\n");
                    print_queue(q);
                }
                else
                {
                    printf("\n---- FILA ESTA CHEIA -----\n");
                }
                
            }
            

        }
        
        if (aux->size == 0)
            printf("\n----- LISTA DE ESPERA VAZIA -----\n");
    }

    return 0;
}