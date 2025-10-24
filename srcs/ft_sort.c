/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 20:43:25 by tlavared          #+#    #+#             */
/*   Updated: 2025/10/24 05:00:22 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_pb_non_lis(t_stack *a, t_stack *b, t_lis *lis)
{
	int		i;
	int		len;

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

void	ft_sort_big(t_stack *a, t_stack *b)
{
	t_lis	*lis;

	lis = ft_lis(a);
	ft_pb_non_lis(a, b, lis);
	ft_push_b_turk(a, b);
	free(lis->is_in_lis);
	free(lis);
}

void	ft_choose_sort(t_stack *a, t_stack *b)
{
	if (a->size < 6)
		ft_sort_small(a, b);
	else
		ft_sort_big(a, b);
}

int	ft_is_sorted(t_stack *stack_a, t_stack *b)
{
	t_node	*current;

	if (b->head)
		return (0);
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
