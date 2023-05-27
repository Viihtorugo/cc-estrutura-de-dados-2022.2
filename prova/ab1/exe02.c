#include <stdio.h>
#include <stdlib.h>

typedef struct tree tree;

typedef struct tree
{
    char elem;
    tree *first_child;
    tree *next_parent;
}tree;

tree *search (char elem, tree *root)
{
    if (root == NULL)
        return NULL;

    if (root->elem == elem)
    {
        return root;
    }
    else
    {
        tree *aux = search(elem, root->first_child);

        if (aux == NULL)
            aux = search(elem, root->next_parent);

        return aux;
    }
}

void print_tree (tree *root)
{
    if (root == NULL)
    {
        return;
    }

    printf(" %c (", root->elem);
    print_tree(root->first_child);
    printf(")");
    print_tree(root->next_parent);
}

int equal (tree *a, tree *b)
{
    if (a == NULL)
        return 1;

    if (a != NULL && b == NULL)
        return 0;

    if (a->elem == b->elem)
    {
        int r = equal(a->first_child, b->first_child);

        if (r == 1)
            r = equal(a->next_parent, b->next_parent);

        return r;
    }
    else
    {
        return 0;
    }
}

int cont (tree *a, tree *b)
{
    if (b == NULL)
        return 0;

    if (a->elem == b->elem)
    {
        if (equal(a->first_child, b->first_child))
        {
            return 1;
        }
    }

    int r = cont(a, b->first_child);

    if (r == 0)
        r = cont(a, b->next_parent);

    return r;
}

int count_no_tree (tree *root, int count)
{
    if (root == NULL)
    {
        return (count - 1);
    }

    count += 1;
    count = count_no_tree(root->first_child, count);
    count += 1;
    count = count_no_tree(root->next_parent, count);
    
    return count;
}

tree *find_parent_a (tree *root, tree *a)
{
    if (root != NULL)
        return root;
    
    if (root->elem != a->elem)
    {
        root->first_child = find_parent_a(root->first_child, a);
        root->next_parent = find_parent_a(root->next_parent, a);

        return root;
    }
    else
    {
        return root;
    }
}

tree *remove_tree (tree *root_a, tree *parent, tree *a, tree *b, tree *forest[], int *index)
{
    if (a == NULL)
        return a;

    a->first_child = remove_tree (root_a, a, a->first_child, b, forest, index);
    a->next_parent = remove_tree (root_a, a, a->next_parent, b, forest, index);

    if (a->elem == b->elem)
    {
        forest[*index] = find_parent_a (root_a, parent);
        *index += 1;

        parent->first_child = NULL;
        parent->next_parent = NULL
    }
    
    return a;
}

tree *create_tree_intersection (tree *a, tree *b, tree *i)
{
    if (a == NULL)
        return i;

    if (a != NULL && b == NULL)
        return i;

    if (a->elem == b->elem)
    {
        tree *new_root = (tree *) malloc (sizeof(tree));
        new_root->elem = a->elem;
        i = new_root;

        i->first_child = create_tree_intersection(a->first_child, b->first_child, i->first_child);
        i->next_parent = create_tree_intersection(a->next_parent, b->next_parent, i->next_parent);

    }
    
    return i;
}

tree **intersection (tree *a, tree *b, tree *forest[], int *index)
{
    if (a == NULL)
        return forest;


    tree **aux = intersection(a->first_child, b, forest, index);
    tree **aux = intersection(a->next_parent, b, forest, index);

    if (a->elem == b->elem)
    {
        forest[*index] = create_tree_intersection (a, b, forest[*index]);
        *index += 1;
    }

    return aux;
}

tree *union_tree (tree *a, tree *b, tree *u)
{
    if (a == NULL)
        return u;
    
    u = union_tree(a->first_child, b, u);
    u = union_tree(a->next_parent, b, u);

    if (a->elem == b->elem)
    {
        if (a->first_child != NULL)
        {
            printf("\ntest 1\n");
            tree *aux = a->first_child;

            while (aux->next_parent != NULL)
                aux = aux->next_parent;

            aux->next_parent = b->first_child;
            
        }
        else
        {
            printf("\ntest 2\n");
            a->first_child = b->first_child;
        }
    }
    
    return u;
}

tree *insert (char elem, tree *root)
{

    tree *new_root = (tree *) malloc(sizeof(tree));

    new_root->elem = elem;

    if (root == NULL)
    {
        return new_root;
    }
    else
    {
        tree *aux;

        while (1)
        {
            printf("\nElementos da arvore: ");
            print_tree(root);
            printf("\nEscolha o pai: ");

            char parent;
            scanf(" %c", &parent);

            aux = search(parent, root);

            if (aux != NULL)
            {
                break;
            }
            else
            {
                printf("Por favor digite um elemento que esta na arvore\n");
            }   
        }

        if (aux->first_child == NULL)
        {
            aux->first_child = new_root;
        }
        else
        {
            aux = aux->first_child;

            while (aux->next_parent != NULL)
                aux = aux->next_parent;
            
            aux->next_parent = new_root;
        }

        return root;
    }
}

int main ()
{

    int op;
    tree *root = NULL;

    while (1)
    {

        printf("\nMenu\n");
        printf("1 - Arvore A está contido na Arvore B?\n");
        printf("2 - União da Arvore A e B\n");
        printf("Para sair digite qualquer ourtro valor!\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &op);

        if (op == 1)
        {
           tree *a = NULL;
            tree *b = NULL;

            char elem;

            while (1)
            {
                printf("\nPara sair da insercao da arvore a digite 0\n");
                printf("\nDigite uma letra arvore a: ");
                scanf(" %c", &elem);

                if (elem == '0')
                    break;

                a = insert(elem, a);
                
            }

            while (1)
            {
                printf("\nPara sair da insercao da arvore b digite 0\n");
                printf("\nDigite uma letra arvore b: ");
                scanf(" %c", &elem);
                
                if (elem == '0')
                    break;

                b = insert(elem, b);
            }
            
            

            if (cont(a, b))
            {

                if (count_no_tree(a, 1) == count_no_tree(b, 1))
                {
                    printf("Arvore a esta propriamente contido em b\n");
                }
                else
                {
                    printf("Arvore a esta contido em b\n");
                }

            }
            else
            {
                printf("Arvore a não está contido em b\n");
            }

            print_tree(a);
            printf("\n");
            print_tree(b);
            printf("\n");
        }
        else if (op == 2)
        {
            tree *a = NULL;
            tree *b = NULL;

            char elem;

            while (1)
            {
                printf("\nPara sair da insercao da arvore a digite 0\n");
                printf("\nDigite uma letra arvore a: ");
                scanf(" %c", &elem);

                if (elem == '0')
                    break;

                a = insert(elem, a);
                
            }

            while (1)
            {
                printf("\nPara sair da insercao da arvore b digite 0\n");
                printf("\nDigite uma letra arvore b: ");
                scanf(" %c", &elem);
                
                if (elem == '0')
                    break;

                b = insert(elem, b);
            }

            printf("arvore a: ");
            print_tree(a);
            printf("\narvore b: ");
            print_tree(b);

            tree *u = union_tree(a, b, a);


            printf("\narvore uniao: ");
            print_tree(u);
        }
        else
        {
            break;
        }
    }

    return 0;
}