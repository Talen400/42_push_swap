/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 05:19:47 by tlavared          #+#    #+#             */
/*   Updated: 2025/10/21 03:22:24 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	ft_pb_non_lis(t_stack *a, t_stack *b, t_lis *lis)
{
	int	i;
	int	len;

	i = 0;
	len = a->size;
	while (i < len)
	{
		if (lis->is_in_lis[i])
			ft_ra(a);
		else
			ft_pb(a, b);
		i++;
	}
}

static void	ft_sort_big(t_stack *a, t_stack *b)
{
	t_lis	*lis;

	lis = ft_lis(a);
	int	i = -1;
	while (++i < a->size)
		printf("lis[%d]: %d\n", i, lis->is_in_lis[i]);
	ft_pb_non_lis(a, b, lis);
	free(lis->is_in_lis);
	free(lis);
	(void ) b;
}

static void	ft_choose_sort(t_stack *a, t_stack *b)
{
	if (a->size < 4)
		ft_sort_small(a);
	else
		ft_sort_big(a, b);
}

int	ft_is_sorted(t_stack *stack_a)
{
	t_node	*current;

	if (!stack_a || !stack_a->head || stack_a->size <= 1)
		return (1);
	current = stack_a->head;
	while (current->next)
	{
		if (current->value > current->next->value)
			return (0);
		current = current->next;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_stack		*a;
	t_stack		*b;

	if (argc < 2)
		return (ft_handler_logic("Error\n"));
	a = ft_stacknew();
	b = ft_stacknew();
	if (!a || !b)
		return (1);
	if (!ft_parse(argv + 1, a))
	{
		ft_stack_free(a);
		ft_stack_free(b);
	}
	if (ft_check_repeat(a->head))
	{
		ft_stack_free(a);
		ft_stack_free(b);
		return ((ft_handler_logic("Error\n")));
	}
	ft_choose_sort(a, b);
	ft_print_stacks(a, b, "final");
	ft_stack_free(a);
	ft_stack_free(b);
	(void ) argc;
}
