#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int elem;
    struct node *next;
} node;

int is_empty_list (node *head)
{
    return (int) (head == NULL);
}

void add_node (node **head, int elem)
{
    node *new_node = (node *) malloc(sizeof(node));
    
    if (is_empty_list(new_node))
    {
        printf("Erro na alocação de memória\n");
        exit(1);
    }

    new_node->elem = elem;
    new_node->next = NULL;

    if (is_empty_list(*head))
    {
        *head = new_node;
    }
    else
    {
        node *aux = *head;
        
        while (aux->next != NULL)
            aux = aux->next;

        aux->next = new_node;
    }
}

int search (node *head, int elem)
{
    while (head != NULL && head->elem != elem)
        head = head->next;

    return !is_empty_list(head);
}

void remove_node (node **head, int elem)
{
    if (search(*head, elem))
    {
        node *aux      = *head;
        node *previous = NULL;

        while (aux != NULL && aux->elem != elem)
        {
            previous = aux;
            aux = aux->next;
        }

        if (is_empty_list(previous))
        {
            (*head) = (*head)->next;
        }
        else
        {
            previous->next = aux->next;

            aux->next = NULL;
            free(aux);
        }
        
    }
    else
    {
        printf("Elemento não pertence a lista!\n");
    }
}

void print_list (node *head)
{
    if (is_empty_list(head))
    {
        printf("Lista está vazia\n");
        return;
    }
    

    while (!is_empty_list(head))
    {
        if (is_empty_list(head->next))
        {
            printf("%d\n", head->elem);
        }
        else
        {
            printf("%d ", head->elem);
        }

        head = head->next;
    }
    
}

int main ()
{
    node *head = NULL;

    add_node(&head, 10);
    add_node(&head, 20);
    add_node(&head, 30);
    add_node(&head, 40);

    print_list(head);

    remove_node(&head, 2);
    remove_node(&head, 20);
    print_list(head);
    remove_node(&head, 40);
    print_list(head);
    remove_node(&head, 10);
    print_list(head);
    remove_node(&head, 30);
    remove_node(&head, 4);

    print_list(head);

    return 0;
}