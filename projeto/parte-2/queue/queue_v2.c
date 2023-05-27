#include <stdio.h>
#include <stdlib.h>

/* 
    VERSÃO CORRIGIDA

    1 - Tratamento de entrada -> get_number(); além de tratamento de erro!
    2 - Reoganização da fila e lista de espera
    3 - Menu para o usuario criado!
*/

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
        printf("\nFila está cheia!\n");
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
        printf("\n\nFila está vazia!\n");
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
        printf("Fila está vazia!\n");
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

void remover_paciente(queue *q, int n)
{
    for (int i = 0; i < n; i++)
    {
        int op = -1;

        while (1)
        {

            printf("\n-----Fila----\n\n");

            for (int i = 0; i < q->size; i++)
                printf("%d - Pessoa com %d ano(s)\n", i + 1, q->array[i]);
            
            printf("\n");

            op = get_number("Digite informe o numero da pessoa na lista: ");

            if (op > 0 && op <= q->size)
            {
                break;
            }
            else
            {
                printf("\n-----ERRO----\n\nDigite um número entre 1 e %d!\n\n", q->size);
            }
        }

        if (remove_in_queue(op, q) != -1)
        {
            printf("Pessoa removida com sucesso!\n\n");
        }
        else
        {
            printf("Erro ao remover a pessoa!\n\n");
        }
    }
}

void inserir_paciente(queue *q, queue *aux, int j, int n, int v)
{
    if (((j + q->size) != q->size_max) && v)
    {
        for (int i = 0; i < n; i++)
        {
            int idade = -1;

            while (1)
            {
                idade = get_number("Digite a idade do paciente (Para recém nascido digite 0): ");

                if (idade < 0 || idade > 125)
                {
                    printf("\n-----ERRO----\n\n1 - O sistema não aceita número negativo;\n");
                    printf("2 - O sistema pode adicionar idade de 0 a 125 anos.\n\n");
                }
                else
                {
                    break;
                }
            }

            if (enqueue(idade, q))
            {
                printf("\nPaciente adicionado com sucesso na fila!\n\n");
            }
            else
            {
                printf("\nErro ao adicionar o paciente!\n\n");
            }
        }
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            int idade;

            while (1)
            {
                idade = get_number("Digite a idade do paciente (Para recém nascido digite 0): ");

                if (idade < 0 || idade > 125)
                {
                    printf("\n-----ERRO----\n\n1 - O sistema não aceita número negativo;\n");
                    printf("2 - O sistema pode adicionar idade de 0 a 125 anos.\n\n");
                }
                else
                {
                    break;
                }
            }

            if (enqueue(idade, aux) )
            {
                printf("\nPaciente adicionado com sucesso na lista de espera!\n\n");
            }
            else
            {
                 printf("\nErro ao adicionar o paciente!\n\n");
            }
        }
    }

}

void menu (queue *q, queue *aux, int i)
{
    while (1)
    {
        printf("\n\n---- MENU -----\n\n");
        printf("1 - adicionar paciente;\n");
        printf("2 - remover paciente;\n");
        printf("3 - adicionar paciente na lista de espera;\n");
        printf("4 - remover paciente na lista de espera;\n");
        printf("0 - atender paciente.\n\n");

        int op = get_number("Digite uma opção: ");

        if (op == 1)
        {
            if (q->size + i == q->size_max)
            {
                printf("\n----- A FILA ESTÁ CHEIA PARA HOJE -----\n\n");
            }
            else
            {
                int n;

                while (1)
                {
                    printf("\n\nVocê pode adicionar até %d paciente(s)!\n", q->size_max - (i + q->size));
                    n = get_number("Digite o número de paciente que deseja adicionar na fila: ");

                    if ((n < 0) || ( n > (q->size_max - (i + q->size) ) ))
                    {
                        printf("\n-----ERRO----\n\n1 - O sistema não aceita número negativo;\n");
                        printf("2 - O sistema pode adicionar apenas %d paciente(s).", q->size_max - (i + q->size));
                    }
                    else
                    {
                        break;
                    }
                }

                if (n != 0)
                {
                    inserir_paciente(q, aux, i, n, 1);
                    
                    print_queue(q);
                    print_prioridade(q);
                }
            }

        }
        else if (op == 2)
        {
            if (q->size == 0)
            {
                printf("\n-----ERRO----\n\nA fila está vazia!\n");
            }
            else
            {
                int n;

                while (1)
                {
                    printf("\n\nVocê pode adicionar até %d paciente(s)!\n", q->size);
                    n = get_number("Digite o número de paciente que deseja remover na fila: ");

                    if (n < 0 || n > q->size)
                    {
                        printf("\n-----ERRO----\n\n1 - O sistema não aceita número negativo;\n");
                        printf("2 - O sistema pode remover apenas %d paciente(s).", q->size);
                    }
                    else
                    {
                        break;
                    }
                }

                remover_paciente(q, n);

                if (q->size != 0)
                {
                    print_queue(q);
                    print_prioridade(q);
                }                
            }
            
        }
        else if (op == 3)
        {
            if (aux->size == aux->size_max)
            {
                printf("\n----- A LISTA DE ESPERA ESTÁ CHEIA -----\n\n");
            }
            else
            {
                int n;

                while (1)
                {
                    printf("\n\nVocê pode adicionar até %d paciente(s)!\n", aux->size_max - aux->size);
                    n = get_number("Digite o número de paciente que deseja adicionar na lista de espera: ");

                    if (n < 0 || (n > (aux->size_max - aux->size)) )
                    {
                        printf("\n-----ERRO----\n\n1 - O sistema não aceita número negativo;\n");
                        printf("2 - O sistema pode adicionar apenas %d paciente(s).", aux->size_max - aux->size);
                    }
                    else
                    {
                        break;
                    }
                }

                if (n != 0)
                {
                    inserir_paciente(q, aux, i, n, 0);
                    
                    print_queue(aux);
                    print_prioridade(aux);
                }
            }

        }
        else if (op == 4)
        {
            if (aux->size == 0)
            {
                printf("\n-----ERRO----\n\nA lista de espera está vazia!\n");
            }
            else
            {
                int n;

                while (1)
                {
                    printf("\n\nVocê pode remover até %d paciente(s)!\n", aux->size);
                    n = get_number("Digite o número de paciente que deseja remover na fila: ");

                    if (n < 0 || n > aux->size)
                    {
                        printf("\n-----ERRO----\n\n1 - O sistema não aceita número negativo;\n");
                        printf("2 - O sistema pode remover apenas %d paciente(s).", aux->size);
                    }
                    else
                    {
                        break;
                    }
                }

                remover_paciente(aux, n);

                if (aux -> size != 0)
                {
                    print_queue(aux);
                    print_prioridade(aux);
                }
            }

        }
        else if (op == 0)
        {
            return;
        }
        else
        {
            printf("\n-----ERRO----\n\n Digite um valor valido do menu -> 1, 2, 3, 4 ou 0\n");
        }

    }


}

int main()
{

    queue *q = create_queue(16);
    queue *aux = create_queue(100);

    while (1)
    {
        printf("\n----------INICIO DO EXPEDIENTE---------\n");
        
        if (q->size != 0)
        {
            printf("\n-------- FILA PARA HOJE -------\n\n");
            
            for (int i = 0; i < q->size_max; i++)
            {
                if (q->array[i] != -1)
                {
                    printf("Consulta %d - Pessoa com %d ano(s), prioridade %d\n", i + 1, q->array[i], prioridade(q->array[i]));
                }
                else
                {
                    printf("Consulta %d - sem paciente!\n", i + 1);
                }
            }
            
            printf("\n");

        }
        else
        {
            printf("\n-------- FILA PARA HOJE ESTÁ VAZIA -------\n");
        }

        int array[16];

        for (int i = 0; i < 16; i++)
        {
            menu(q, aux, i);

            int idade = dequeue(q);
            array[i] = idade;

            if (idade == -1)
            {
                printf("\n---- Consulta %d: sem paciente ----\n", i + 1);
            }
            else
            {
                printf("\n---- Consulta %d: pessoa tem %d anos ----\n", i + 1, idade);
                printf("\n");
                
                if (i + 1 < 16 && q->size != 0)
                {
                    print_queue(q);
                    print_prioridade(q);
                }
            }
        }

        printf("\n----FIM DO EXPEDIENTE----\n");

        //atendimento do dia!
        printf("\n------ FILA HOJE -----\n\n");

        for (int i = 0; i < 16; i++)
        {
            if (array[i] == -1)
            {
                printf("Paciente %d: não houve atendimento!\n", i + 1);
            }
            else
            {
                printf("Paciente %d: %d ano(s)\n", i + 1, array[i]);
            }
        }

        printf("\n");
        
        //esvaziando a fila
        for (int i = 0; i < q->size_max; i++)
            q->array[i] = -1;

        //organizar a fila para amanhã
        if (aux->size != 0)
        {
            printf("\n---- PREPARAR A FILA DE AMANHÃ ----\n");

            int n = -1;

            while (1)
            {
                printf("\n\n%d paciente(s) na lista de espera!\n\n", aux->size);
                n = get_number("Escolha a quantidade para adicionar na fila de amanhã: ");

                if (n >= 0 && n <= aux->size && n <= 16)
                {
                    break;
                }
                else
                {
                    printf("\n-----ERRO----\n\n1 - O sistema possui %d paciente(s);\n", aux->size);
                    printf("2 - A fila pode ter no máximo 16 pacientes!\n");
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

                    printf("\n");

                    op = get_number("Digite informe o numero da pessoa na fila: ");

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
                    printf("\n---- PACIENTE ADICIONADO PARA AMANHÃ -----\n");
                }
                else
                {
                    printf("\n---- ERRO AO ADICIONAR PACIENTE PARA AMANHÃ -----\n");
                }
                
            }
            
        }
        else
        {
            printf("\n----- LISTA DE ESPERA ESTÁ VAZIA -----\n");
        }
    }

    return 0;
}