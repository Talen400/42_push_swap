#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdio.h>
# include <time.h>

# include "../libft/libft.h"

# define MAX_INT 2147483647

typedef struct	s_node
{
	int				value;
	struct	s_node	*next;
	struct	s_node	*prev;
}	t_node;

typedef struct	s_stack
{
	t_node	*head;
	t_node	*tail;
	int		size;
}	t_stack;

typedef struct	s_lis_data
{
	int	*is_in_lis;
	int	lis_lenght;
	int	total_size;
}	t_lis_data;

// utils
int	ft_handler_logic(char *str);

// parse
int	ft_parse(char **argv, t_stack *list);
int	ft_check_repeat(t_node *head);

// stack

t_stack	*ft_stacknew(void);
t_node	*ft_nodenew(int value);
void	ft_stack_push_back(t_stack *stack, int value);
void	ft_stack_free(t_stack *stack);

// operations
void	ft_push(t_stack *from, t_stack *dest);
void	ft_rotate(t_stack *stack);
void	ft_rrotate(t_stack *stack);
void	ft_swap(t_stack *stack);

// print
void	ft_print_stacks(t_stack *a, t_stack *b, const char *op);
#endif
