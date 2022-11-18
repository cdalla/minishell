#include <stdio.h>
#include <stdlib.h>

typedef struct s_list
{
	int	value;
	struct s_list *next;
}				t_list;



int	modify(t_list *node)
{
	node->value = 1;
	return(0);
}

t_list *new_node(int value)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (0);
	new->value = value;
	new->next = 0;
	return (new);
}

int main(void)
{
	t_list	*node;

	node = new_node(0);
	printf("%d\n", node->value);
	modify(node);
	printf("%d\n", node->value);
	return(0);

}