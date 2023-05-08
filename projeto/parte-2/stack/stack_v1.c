#include <stdio.h>
#include <stdlib.h>

typedef struct stack {
	int elem;
	struct stack *next;
} stack;

stack *push_stack (stack *top, int elem)
{
	stack *new_top = (stack *) malloc (sizeof(stack));
	
	if (new_top == NULL)
	{
		printf("Falta de memoria\n");
		exit(1);
	}
	
	new_top->elem = elem;
	new_top->next = top;
	
	return new_top;
}

int pop_stack (stack **top)
{
	if (*top == NULL)
	{
		printf("Pilha vazia!\n");
		exit(1);
	}
	
	stack *aux = *top;
	*top = (*top)->next;
	
	int remove = aux->elem;
	
	aux->next = NULL;
	free(aux);
	
	return remove;
}

int qtd_stack (stack *top)
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

stack *embaralhar (stack *top)
{
	stack *new_top = NULL;
	
	while (top != NULL)
	{
		int r = random() % qtd_stack(top);
		stack *aux = NULL;
		
		while (top != NULL && r + 1 != 0)
		{
			aux = push_stack(aux, pop_stack(&top));
			r -= 1;
		}
		
		new_top = push_stack(new_top, pop_stack(&aux));
		
		while (aux != NULL) 
			top = push_stack (top, pop_stack(&aux));
	}
	
	return new_top;
}

int main ()
{
	//falta tratar o erro
	printf("Digiteo o numero de cartas: ");
	int n;
	scanf("%d", &n);
	
	stack *baralho_a = NULL;
	stack *baralho_b = NULL;
	
	for (int i = 0; i < n; i++)
	{
		int elem;
		scanf("%d", &elem);
		
		baralho_a = push_stack(baralho_a, elem);
		baralho_b = push_stack(baralho_b, elem);
	}
	
	while (baralho_a != NULL && baralho_b != NULL)
	{
		baralho_a = embaralhar (baralho_a);
		baralho_b = embaralhar (baralho_b);
		
		int a = pop_stack(&baralho_a);
		int b = pop_stack(&baralho_b);
		
		printf("Carta jogador a -> %d e carta do jogador b -> %d\n", a, b);
		
		
		if (a > b)
		{
			printf("1\n");
			baralho_a = push_stack (baralho_a, a);
		}
		else if (a < b)
		{
			printf("2\n");
			baralho_b = push_stack (baralho_b, b);
		}
		else
		{
			printf("0\n");
		}
	}
	
	//Saida errada
	if (baralho_a == NULL)
	{
		printf("Jogador A eh o vencendor\n");
	}
	else
	{
		printf("Jogador B eh o vencendor\n");
	}	
		
	return 0;
}
