#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *x, int *y)
{
    int aux = *x;
    *x = *y;
    *y = aux;
}

void quick_sort_v1(int array[], int i, int n, int tam)
{
    if (n > i)
    {
        int l = i, r = n;

        if (r == tam)
            r -= 1;

        while (l < r)
        {
            while (array[l] <= array[i])
                l += 1;

            while (array[r] > array[i])
                r -= 1;

            if (l < r)
                swap(&array[l], &array[r]);
        }

        swap(&array[i], &array[r]);

        quick_sort_v1(array, i, r - 1, tam);
        quick_sort_v1(array, r + 1, n, tam);
    }
}

void quick_sort_v2(int array[], int i, int n, int tam)
{

    if (n > i)
    {
        int l = i, r = n;

        if (r == tam)
            r -= 1;

        printf("teste 1\n");
        
        int cal = (l - r + 1) + l;
        
        if (cal == 0)
            cal += 1;

        if (cal == 1)
            cal += 1;
            
        printf("(l - r + 1) + l = %d\n", (l - r + 1) + l);
        int pivot_index = rand() % cal;
        printf("pivo= %d\n", pivot_index);
        printf("teste 2\n");

        if (pivot_index != i)
            swap(&array[pivot_index], &array[i]);

        for (int k = 0; k < tam; k++)
            printf("%d ", array[k]);

        printf("-> ordenando\n");

        while (l < r)
        {
            while (array[l] <= array[i] && l < n)
                l += 1;

            while (array[r] > array[i] && r >= 0)
                r -= 1;

            if (l < r)
                swap(&array[l], &array[r]);
        }
        
        swap(&array[i], &array[r]);

        quick_sort_v2(array, i, r - 1, tam);
        //quick_sort_v2(array, r + 1, n, tam);
    }
}

void bin_sort_v1(int array[], int n)
{
    for (int i = 0; i < n; i++)
        while (array[i] != i)
            swap(&array[i], &array[array[i]]);
}

typedef struct list
{
    int elem;
    struct list *next;
} list;

void bin_sort_v2(int array[], int n)
{
    list *l[10];

    for (int i = 0; i < 10; i++)
        l[i] = NULL;

    for (int i = 0; i < n; i++)
    {
        int index = array[i] / 10;

        list *aux = l[index];
        list *previous = NULL;

        while (aux != NULL && array[i] > aux->elem)
        {
            previous = aux;
            aux = aux->next;
        }

        list *new_node = (list *)malloc(sizeof(list));

        if (new_node == NULL)
            exit(1);

        new_node->elem = array[i];
        new_node->next = aux;

        if (previous != NULL)
        {
            previous->next = new_node;
        }
        else
        {
            l[index] = new_node;
        }
    }

    int array_index = 0;

    for (int i = 0; i < 10 && array_index < n; i++)
    {
        list *aux = l[i];

        while (aux != NULL)
        {
            array[array_index] = aux->elem;
            array_index += 1;
            aux = aux->next;
        }
    }
}

void merge(int array[], int l, int pivot, int r, int tam)
{
    int aux[tam], index = 0;
    int i = l, j = pivot + 1;

    while (i <= pivot && j <= r)
    {
        if (array[i] <= array[j])
        {
            aux[index] = array[i];
            index += 1;
            i += 1;
        }
        else
        {
            aux[index] = array[j];
            j += 1;
            index += 1;
        }
    }

    while (i <= pivot)
    {
        aux[index] = array[i];
        index += 1;
        i += 1;
    }

    while (j <= r)
    {
        aux[index] = array[j];
        j += 1;
        index += 1;
    }

    for (int i = l, index = 0; i <= r; i++, index++)
        array[i] = aux[index];
}

void merge_sort(int array[], int l, int r, int tam)
{
    int pivot = (l + r) / 2;

    if (l < r)
    {
        merge_sort(array, l, pivot, tam);
        merge_sort(array, pivot + 1, r, tam);
        merge(array, l, pivot, r, tam);
    }
}

void radix_sort(int array[], int n)
{
    int m = array[0];

    for (int i = 1; i < n; i++)
        if (array[i] > m)
            m = array[i];

    for (int exp = 1; m / exp > 0; exp *= 10)
    {
        int output[n];
        int i, count[10] = {0};

        // frequencia que do numero no intervalo [0, 9]
        for (i = 0; i < n; i++)
            count[(array[i] / exp) % 10]++;

        // frequencia acumulada
        for (i = 1; i < 10; i++)
            count[i] += count[i - 1];

        /*printf("count com output: ");
        for (int i = 0; i < 10; i++)
            printf("%d ", count[i]);

        printf("\n");*/

        // construindo saida
        for (i = n - 1; i >= 0; i--)
        {
            output[count[(array[i] / exp) % 10] - 1] = array[i];
            count[(array[i] / exp) % 10]--;
        }

        for (i = 0; i < n; i++)
            array[i] = output[i];

        /*printf("ordenando: ");
        for (int i = 0; i < n; i++)
            printf("%d ", array[i]);

        printf("\n");*/
    }
}

void shell_sort_v1(int array[], int n)
{
    for (int i = n / 2; i > 0; i--)
        for (int j = 0; (j < n) && (j + i != n); j++)
            if (array[j] > array[j + i])
                swap(&array[j], &array[j + i]);
}

void shell_sort_v2(int array[], int n)
{
    int h;
    for (h = 1; h < n; h = 3 * h + 1);

    while (h > 0)
    {
        h = (h - 1) / 3;
        for (int i = h; i < n; i++)
        {
            int aux = array[i];
            int j = i;

            while (array[j - h] > aux)
            {
                array[j] = array[j - h];
                j -= h;
                if (j < h)
                    break;
            }
            array[j] = aux;
        }
    }
}

void bubble_sort_v1(int array[], int n)
{
    for (int i = n - 1; i >= 0; i--)
        for (int j = 0; j < i; j++)
            if (array[j] > array[j + 1])
                swap(&array[j], &array[j + 1]);
}

void bubble_sort_v2(int array[], int n)
{
    for (int i = 0; i < n / 2; i++)
    {
        for (int j = n - i - 1; j > i; j--)
        {
            if (array[j - 1] > array[j])
                swap(&array[j - 1], &array[j]);

            if (array[n - j] < array[n - j - 1])
                swap(&array[n - j], &array[n - j - 1]);
        }
    }
}

void selection_sort_v1(int array[], int n)
{
    for (int i = 0; i < n; i++)
    {
        int menor = i;

        for (int j = i + 1; j < n; j++)
            if (array[j] < array[menor])
                menor = j;

        swap(&array[menor], &array[i]);
    }
}

void selection_sort_v2(int array[], int n)
{
    for (int j = 0; j < n / 2; j++)
    {
        int maior = n - j - 1, menor = j;

        for (int i = j; i < n - j; i++)
        {
            if (array[maior] < array[i])
            {
                maior = i;
            }
            else if (array[menor] > array[i])
            {
                menor = i;
            }
        }

        if (maior == j && menor == n - 1 - j)
        {
            swap(&array[maior], &array[menor]);
        }
        else
        {
            swap(&array[maior], &array[n - 1 - j]);
            swap(&array[menor], &array[j]);
        }
    }
}

void insert_sort_v1(int array[], int n)
{
    for (int i = 1; i < n; i++)
    {
        int j = i;
        while (j >= 1 && array[j - 1] > array[j])
        {
                swap(&array[j], &array[j - 1]);
                j -= 1;
        }
    }
}

void insert_sort_v2(int array[], int n)
{
    for (int i = 1; i <= n / 2; i++)
    {
        int j = n - i;
        int aux = j;

        while (j >= i)
        {
            if (array[j - 1] > array[j])
                swap(&array[j - 1], &array[j]);

            if (array[j] > array[aux])
                aux = j;

            j -= 1;
        }

        if (aux != n - i)
            swap(&array[aux], &array[n - i]);
    }
}

int main()
{
    srand(time(NULL));

    int n;
    scanf("%d", &n);

    int array[n];

    for (int i = 0; i < n; i++)
    {
         array[i] = rand() % n;
        // scanf("%d", &array[i]);
    }

    for (int i = 0; i < n; i++)
        printf("%d ", array[i]);

    printf("-> normal\n");

    /*
        1 - insertion sort
        2 - bubble sort - melhorado
        3 - selection sort - melhorado
        4 - shell sort
        5 - merge sort
        6 - quick sort
        7 - heap sort
        8 - bin sort
        9 - radix sort
        10 - counting sort
    */

    // bubble_sort_v1(array, n);
    // bubble_sort_v2(array, n);
    // selection_sort_v1(array, n);
    // selection_sort_v2(array, n);
    // insert_sort_v1 (array, n);
     insert_sort_v2 (array, n);
    // shell_sort_v1(array, n);
    // shell_sort_v2(array, n);
    // radix_sort(array, n);
    // quick_sort_v1(array, 0, n, n);
    // quick_sort_v2(array, 0, n, n);
    // merge_sort(array, 0, n - 1, n);
    // bin_sort_v1(array, n);
    // bin_sort_v2(array, n);

    for (int i = 0; i < n; i++)
        printf("%d ", array[i]);

    printf("-> ordenado\n");

    return 0;
}