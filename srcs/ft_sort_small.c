/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_small.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 19:48:23 by tlavared          #+#    #+#             */
/*   Updated: 2025/10/24 04:57:26 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	ft_sort_four(t_stack *a, t_stack *b)
{
	t_node	*min_node;
	int		min_pos;

	min_node = ft_lownest_node(a);
	min_pos = ft_get_pos(a, min_node);
	if (min_pos == 1)
		ft_sa(a);
	else if (min_pos == 2)
	{
		ft_rra(a);
		ft_rra(a);
	}
	else if (min_pos == 3)
		ft_rra(a);
	ft_pb(a, b);
	ft_sort_small(a, b);
	ft_pa(a, b);
}

static void	ft_sort_five(t_stack *a, t_stack *b)
{
	t_node	*min_node;
	int		min_pos;

	min_node = ft_lownest_node(a);
	min_pos = ft_get_pos(a, min_node);
	if (min_pos <= 2)
	{
		while (min_pos-- > 0)
			ft_ra(a);
	}
	else
	{
		while (min_pos++ < a->size)
			ft_rra(a);
	}
	ft_pb(a, b);
	ft_sort_four(a, b);
	ft_pa(a, b);
}

void	ft_sort_small(t_stack *a, t_stack *b)
{
	t_node	*high;

	if (a->size < 2)
		return ;
	else if (a->size < 3 && a->head->value > a->head->next->value)
		ft_sa(a);
	else if (a->size < 4)
	{
		high = ft_highnest_node(a);
		if (a->head->value == high->value)
			ft_rra(a);
		if (high->value > a->tail->value)
			ft_rra(a);
		if (a->head->value > a->head->next->value)
			ft_sa(a);
	}
	else if (a->size < 5)
		ft_sort_four(a, b);
	else if (a->size < 6)
		ft_sort_five(a, b);
}
