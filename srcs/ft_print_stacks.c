/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_stacks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 20:08:24 by tlavared          #+#    #+#             */
/*   Updated: 2025/10/18 23:55:29 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_print_stacks(t_stack *a, t_stack *b, const char *op)
{
	t_node	*node_a;
	t_node	*node_b;
	int	i;

	i = 0;
	printf("%-10s%-10s(%d)%-10s(%d) (%s)\n", "index", "a", a->size, "b", b->size, op);
	node_a = a->head;
	node_b = b->head;
	while (node_a || node_b)
	{
		printf("node[%-2d]: ", i);
		if (node_a)
		{
			printf("%-10d", node_a->value);
			node_a = node_a->next;
		}
		else
			printf("%-10s", "");
		if (node_b)
		{
			printf("%-10d", node_b->value);
			node_b = node_b->next;
		}
		else
			printf("%-10s", "");
		printf("\n");
		i++;
	}
	printf("-------------------------------\n");
}

