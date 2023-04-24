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

        while (aux->next != NULL)
            aux = aux->next;

        aux->next = new_node;
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
    g->list_adj[y] = add_list_adj(x, g->list_adj[y]);
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

int main ()
{

    int n, m;
    scanf("%d %d", &n, &m);

    graph *g = create_graph(n);

    for (int i = 0; i < m; i++)
    {
        int x, y;
        scanf("%d %d", &x, &y);
        add_vertex(x, y, g);
    }

    dfs(g, 0, 0);
    printf("\n");

    return 0;
}
