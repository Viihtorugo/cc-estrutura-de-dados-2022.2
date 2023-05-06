#include <stdio.h>
#include <stdlib.h>

typedef struct list_adj
{
    int v;
    struct list_adj *next;
} list_adj;

typedef struct graph {
    int size;
    int *visited;
    list_adj **list_adj;
} graph;

typedef struct queue {
    int v;
    struct queue *next;
} queue;

void enqueue (int v, queue **q)
{
    queue *new_node = (queue *) malloc(sizeof(queue));
    
    if (new_node == NULL)
        exit(1);

    new_node->v = v;
    new_node->next = NULL;

    if (*q == NULL)
    {
        *q = new_node;
    }
    else
    {
        queue *aux = *q;

        while (aux->next != NULL)
            aux = aux->next;

        aux->next = new_node;
    }
}

void enqueue_priority (int v, queue **q)
{
    queue *new_node = (queue *) malloc(sizeof(queue));
    
    if (new_node == NULL)
        exit(1);

    new_node->v = v;
    new_node->next = NULL;

    if (*q == NULL)
    {
        *q = new_node;
    }
    else
    {
        queue *aux = *q;
        queue *previous = NULL;

        while (aux != NULL && v >= aux->v)
        {
            previous = aux;
            aux = aux->next;
        }

        if (previous == NULL)
        {
            new_node->next = *q;
            *q = new_node;
        }
        else
        {
            previous->next = new_node;
            new_node->next = aux;
        }
    }
}

int dequeue (queue **q)
{
    queue *aux = *q;

    int dequeued = aux->v;

    (*q) = (*q)->next;

    aux->next = NULL;
    free(aux);

    return dequeued;
}

list_adj *add_list_adj (int v, list_adj *head)
{
    list_adj *new_node = (list_adj *) malloc(sizeof(list_adj));

    if (new_node == NULL)
        exit(1);

    new_node->v = v;
    new_node->next = NULL;

    if (head == NULL)
    {
        return new_node;
    }
    else
    {
        list_adj *aux = head;
        list_adj *previous = NULL;

        while (aux != NULL && v >= aux->v)
        {
            previous = aux;
            aux = aux->next;
        }

        if (previous == NULL)
        {
            new_node->next = aux;
            head = new_node;
        }
        else
        {
            previous->next = new_node;
            new_node->next = aux;
        }

        return head;
    }

}

graph *create_graph (int size)
{
    graph *g = (graph *) malloc(sizeof(graph));

    if (g == NULL)
        exit(1);

    g->size = size;
    g->visited = malloc(size * sizeof(int));
    g->list_adj = (list_adj **) malloc(size * sizeof(list_adj *));

    for (int i = 0; i < g->size; i++)
    {
        g->visited[i] = 0;
        g->list_adj[i] = NULL;
    }
    
    return g;
}

void add_vertex (int x, int y, graph *g)
{
    g->list_adj[x] = add_list_adj(y, g->list_adj[x]);
}

void dfs (graph *g, int v, int count)
{   
    printf("%d ", v);

    count += 1;
    g->visited[v] = count;

    list_adj *aux = g->list_adj[v];

    while (aux != NULL)
    {
        if (g->visited[aux->v] == 0)
            dfs(g, aux->v, count);
        
        aux = aux->next;
    }   
}

void print_queue (queue *q)
{
    queue *aux = q;

    while (aux != NULL)
    {
        if (aux->next == NULL)
        {
            printf("%d\n", aux->v);
        }
        else
        {
            printf("%d ", aux->v);
        }

        aux = aux->next;
    }
}

void print_graph(graph *g)
{
    for (int i = 0; i < g->size; i++)
    {
        printf("v%d -> ", i);

        list_adj *aux = g->list_adj[i];

        while (aux != NULL)
        {
            if (aux->next == NULL)
            {
                printf("v%d vizinhos", aux->v);
            }
            else
            {
                printf("v%d ", aux->v);
            }

            aux = aux->next;
        }

        printf("\n");
        
    }
    
}

int search (list_adj *l, int elem)
{
    list_adj *aux = l;

    while (aux != NULL && elem != aux->v)
        aux = aux->next;
    
    return (int) (aux == NULL);
}

int bfs_count (graph *g, int v, int d)
{
    int count = 1;

    if (v == d)
        return 0;

    queue *q = NULL;
    enqueue(v, &q);

    while (q != NULL)
    {
        int dequeued = dequeue(&q);
        list_adj *aux = g->list_adj[dequeued];

        if (search(aux, d) == 0)
            return count;


        while (aux != NULL)
        {
            if (g->visited[aux->v] == 0)
            {
                g->visited[aux->v] = 1;
                enqueue(aux->v, &q);
            }

            aux = aux->next;
        }

        count += 1;

        //printf("\nFila: ");
        //print_queue(q);
        //printf("\n");

    }

    return -1;
}

void bfs (graph *g, int v, int d)
{
    queue *q = NULL;
    enqueue(v, &q);
    g->visited[v] = 1;

    while (q != NULL)
    {
        int dequeued = dequeue(&q);
        list_adj *aux = g->list_adj[dequeued];
        
        printf("Iniciando busca em largura a partir de %d\n", dequeued);
        
        while (aux != NULL)
        {

            if (g->visited[aux->v] == 0)
            {
                g->visited[aux->v] = 1;
                enqueue(aux->v, &q);
            }
            
            aux = aux->next;
        }
        
        print_queue(q);
    }

    printf("\n");
    for (int i = 0; i < g->size; i++)
    {
        printf("%d | ", i);

        for (int i = 0; i < g->size; i++)
            g->visited[i] = 0;

        int count = bfs_count(g, v, i);

        if (count == -1)
        {
            printf("- | ");
        }
        else
        {
            printf("%d | ", count);
        }

        if (count == -1)
        {
            printf("-\n");
        }
        else
        {
            printf("%d\n", count);
        }
    }

    printf("\nCaminho entre %d e %d:", v, d);

    printf("\n");
    
}

int main ()
{

    int n, m, e;
    scanf("%d %d %d", &n, &m, &e);
    
    printf("--------\n\n");
    if (n != 0)
    {
        graph *g = create_graph(n);

        for (int i = 0; i < m; i++)
        {
            int x, y;
            scanf("%d %d", &x, &y);
            add_vertex(x, y, g);
        }
        for (int i = 0; i < e; i++)
        {
            int v, d;
            scanf("%d %d", &v, &d);

            printf("\n");
            print_graph(g);
            printf("\n");

            for (int i = 0; i < g->size; i++)
                g->visited[i] = 0;

            printf("Caso de Teste #%d - BFS(%d)\n\n", i + 1, v);
            //print_graph(0, g);
            //dfs(g, 0, 0);
            bfs(g, v, d);
            printf("--------\n\n");
        }

    }

    return 0;
}
