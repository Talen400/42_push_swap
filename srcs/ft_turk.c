/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_turk.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 03:11:32 by tlavared          #+#    #+#             */
/*   Updated: 2025/10/24 04:11:30 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static int	ft_eval_dir_rr_rrr(int dir_a, int dir_b, int cost_a, int cost_b)
{
	int	total;

	if (dir_a == dir_b)
	{
		if (cost_a > cost_b)
			total = cost_a;
		else
			total = cost_b;
	}
	else
		total = cost_a + cost_b;
	return (total);
}

static void	ft_eval_plan(t_cost *best_cost, t_calc_data data, int dir_a,
	int dir_b)
{
	int	cost_a;
	int	cost_b;
	int	total;

	if (dir_a == 1)
		cost_a = data.cost_ra;
	else
		cost_a = data.cost_rra;
	if (dir_b == 1)
		cost_b = data.cost_rb;
	else
		cost_b = data.cost_rrb;
	total = ft_eval_dir_rr_rrr(dir_a, dir_b, cost_a, cost_b);
	if (total < best_cost->total)
	{
		best_cost->cost_a = cost_a;
		best_cost->dir_a = dir_a;
		best_cost->cost_b = cost_b;
		best_cost->dir_b = dir_b;
		best_cost->total = total;
	}
}

t_cost	ft_calculate_cost(t_stack *a, t_stack *b, t_node *node)
{
	t_cost		best_cost;
	t_calc_data	data;

	data.pos_a = ft_insert_pos(a, node);
	data.pos_b = ft_get_pos(b, node);
	data.cost_ra = data.pos_a;
	data.cost_rra = a->size - data.pos_a;
	data.cost_rb = data.pos_b;
	data.cost_rrb = b->size - data.pos_b;
	best_cost.total = MAX_INT;
	best_cost.target = node;
	ft_eval_plan(&best_cost, data, 1, 1);
	ft_eval_plan(&best_cost, data, -1, -1);
	ft_eval_plan(&best_cost, data, 1, -1);
	ft_eval_plan(&best_cost, data, -1, 1);
	return (best_cost);
}

t_node	*ft_find_cheap_node(t_stack *a, t_stack *b)
{
	t_node	*node;
	t_cost	cost;
	t_cost	min_cost;

	if (!b->head)
		return (NULL);
	node = b->head;
	min_cost = ft_calculate_cost(a, b, node);
	while (node)
	{
		cost = ft_calculate_cost(a, b, node);
		if (cost.total < min_cost.total)
				min_cost = cost;
		node = node->next;
	}
	return (min_cost.target);
}

void	ft_push_b_turk(t_stack *a, t_stack *b)
{
	t_node	*cheap;
	t_cost	cost;

	while (b->size > 0)
	{
		cheap = ft_find_cheap_node(a, b);
		cost = ft_calculate_cost(a, b, cheap);
		ft_execute_operations(a, b, cost);
	}
	ft_final_align(a);
}
