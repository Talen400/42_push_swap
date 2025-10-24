/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 22:03:42 by tlavared          #+#    #+#             */
/*   Updated: 2025/10/24 04:51:14 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdio.h>
# include <time.h>

# include "../libft/libft.h"

# define MAX_INT 2147483647
# define MIN_INT -2147483648

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
	int	len;
}	t_lis;

typedef struct s_cost
{
	int		cost_a;
	int		cost_b;
	int		dir_a;
	int		dir_b;
	int		total;
	t_node	*target;
}	t_cost;

typedef struct s_calc_data
{
	int	pos_a;
	int	pos_b;
	int	cost_ra;
	int	cost_rra;
	int	cost_rb;
	int	cost_rrb;
}	t_calc_data;

// utils
int		ft_handler_logic(char *str);
void	ft_free_stacks(t_stack *a, t_stack *b);

// parse
int		ft_parse(int argc, char **argv, t_stack *stack);

// parse utils
int		ft_check_repeat(t_node *head);

// LIS - Longest increasing subsequence
t_lis	*ft_lis(t_stack *stack);

// Turk
void	ft_push_b_turk(t_stack *a, t_stack *b);
t_node	*ft_find_cheap_node(t_stack *a, t_stack *b);
t_cost	ft_calculate_cost(t_stack *a, t_stack *b, t_node *node);

// Turk operations
void	ft_execute_operations(t_stack *a, t_stack *b, t_cost cost);

// Align
void	ft_final_align(t_stack *stack);

// finders
t_node	*ft_lownest_node(t_stack *stack);
t_node	*ft_highnest_node(t_stack *stack);
int		ft_get_pos(t_stack *stack, t_node *search);
int		ft_insert_pos(t_stack *stack, t_node *inset);

// small sort (to size <= 3)
void	ft_sort_small(t_stack *a, t_stack *b);

// sort 
void	ft_pb_non_lis(t_stack *a, t_stack *b, t_lis *lis);
void	ft_sort_big(t_stack *a, t_stack *b);
void	ft_choose_sort(t_stack *a, t_stack *b);
int		ft_is_sorted(t_stack *stack_a, t_stack *b);

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

// qsort
void	ft_qsort(int *arr, int low, int high);

// normalize stack
int		ft_normalize_values(t_stack *stack);

#endif
