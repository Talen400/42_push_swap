/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 22:03:42 by tlavared          #+#    #+#             */
/*   Updated: 2025/10/21 03:00:00 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdio.h>
# include <time.h>

# include "../libft/libft.h"

# define MAX_INT 2147483647

typedef struct s_node
{
	int				value;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

typedef struct s_stack
{
	t_node	*head;
	t_node	*tail;
	int		size;
}	t_stack;

typedef struct s_lis
{
	int	*is_in_lis;
	int len;
}	t_lis;

// utils
int		ft_handler_logic(char *str);

// parse
int		ft_parse(char **argv, t_stack *stack);
int		ft_check_repeat(t_node *head);

// LIS - Longest increasing subsequence
t_lis	*ft_lis(t_stack *stack);

// sort small
t_node	*ft_highnest_node(t_stack *stack);
void	ft_sort_small(t_stack *a);

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

// print operations
void	ft_pb(t_stack *a, t_stack *b);
void	ft_pa(t_stack *a, t_stack *b);
void	ft_ra(t_stack *a);
void	ft_rb(t_stack *b);

// print swap operations 
void	ft_sa(t_stack *a);
void	ft_sb(t_stack *b);
void	ft_ss(t_stack *a, t_stack *b);

// print reverse operations
void	ft_rra(t_stack *a);
void	ft_rrb(t_stack *b);

// print two operations
void	ft_rr(t_stack *a, t_stack *b);
void	ft_rrr(t_stack *a, t_stack *b);

// binary search
int		*ft_array_binary(t_stack *list);
int		ft_binary_search(int *arr, int search, int len);

// math
int		ft_abs(int n);
int		ft_max(int a, int b);
int		ft_min(int a, int b);

// print
void	ft_print_stacks(t_stack *a, t_stack *b, const char *op);

#endif
