#include <stdio.h>
#include <stdlib.h>

#define true 1 == 1
#define false 1 != 1
typedef int boolean;

typedef struct s_stack {
    char data;
    struct s_stack *next;
} t_stack;

t_stack *Stack = NULL;

boolean push(char c)
{
    t_stack *tmp;
    if (!(tmp = malloc(sizeof(t_stack))))
        return false;
    tmp->data = c;
    if (!Stack)
		tmp->next = NULL;
    else
    	tmp->next = Stack;
	Stack = tmp;
    return true;
}

char pop()
{
	char c = 0;
	t_stack *tmp;
	if (Stack)
	{
		c = Stack->data;
		tmp = Stack;
		Stack = Stack->next;
		free(tmp);
	}
	return c;
}

void parse_brackets(const char *str)
{
    int i = 0;
    char c;
    while (str[i])
    {
        if (str[i] == '(' || str[i] == '{' || str[i] == '[')
        {
			if (!push(str[i]))
				printf("Error - Full stack\n");
		}
        else if (str[i] == ')' || str[i] == '}' || str[i] == ']')
		{
        	c = pop();
			if (!(str[i] == ')' && c == '(') && !(str[i] == '}' && c == '{') && !(str[i] == ']' && c == '['))
			{
				printf("Bracket sequence is incorrect\n");
				return ;
			}
		}
        i++;
    }
    if (!Stack)
		printf("Bracket sequence correct\n");
    else
		printf("Bracket sequence is incorrect\n");
}

t_stack *copy_list(t_stack *lst)
{
	t_stack *res = NULL;
	t_stack *tmp = NULL;
	t_stack *this_res = NULL;
	while (lst)
	{
		if (!(tmp = malloc(sizeof(t_stack))))
			return (NULL);
		tmp->data = lst->data;
		tmp->next = NULL;
		if (!res)
		{
			res = tmp;
			this_res = res;
		}
		else
		{
			this_res->next = tmp;
			this_res = tmp;
		}
		lst = lst->next;
	}
	return (res);
}

void print_stack(t_stack *lst)
{
	t_stack *tmp = lst;
	while (tmp)
	{
		printf("%c ", tmp->data);
		tmp = tmp->next;
	}
	printf("\n");
}

boolean is_sorted(t_stack *lst)
{
	t_stack *res = lst;
	while (res && res->next)
	{
		if (res->data > res->next->data)
			return false;
		res = res->next;
	}
	return true;
}

int main()
{
    // Задание 1
    printf("Task 1\n");
    char string[100];
    printf("Enter a parenthesis expression:");
    scanf("%s", string);
    parse_brackets(string);

    // Подготовка ко второму заданию
    while (pop()) {}

	// Задание 2
	printf("\nTask 2\n");
	t_stack *lst;
	push('d');
	push('c');
	push('b');
	push('a');
	lst = copy_list(Stack);
	print_stack(Stack);
	print_stack(lst);

	// Задание 3
	printf("\nTask 3\n");
	if (is_sorted(Stack))
		printf("Sorted\n");
	else
		printf("No sorted\n");
    return 0;
}
