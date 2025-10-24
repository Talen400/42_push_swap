/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 19:10:18 by tlavared          #+#    #+#             */
/*   Updated: 2025/10/23 19:15:56 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_BONUS_H
# define CHECKER_BONUS_H

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

// checker utils
void	ft_ss(t_stack *a, t_stack *b);
void	ft_rr(t_stack *a, t_stack *b);
void	ft_rrr(t_stack *a, t_stack *b);

// utils
int		ft_handler_logic(char *str);
void	ft_free_stacks(t_stack *a, t_stack *b);

// parse
int		ft_parse(int argc, char **argv, t_stack *stack);

// parse utils
int		ft_check_repeat(t_node *head);

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

// sort
int		ft_is_sorted(t_stack *stack_a, t_stack *b);

#endif
