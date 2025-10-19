/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 19:47:26 by tlavared          #+#    #+#             */
/*   Updated: 2025/10/19 04:37:57 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	ft_parse(char **argv, t_stack *list)
{
	int	value;

	while (*argv)
	{
		value = ft_atoi(*argv);
		ft_stack_push_back(list, value);
		argv++;
	}
	return (1);
}

int	ft_check_repeat(t_node *head)
{
	t_node	*node;

	while (head)
	{
		node = head->next;
		while (node)
		{
			if (head->value == node->value)
				return (1);
			node = node->next;
		}
		head = head->next;
	}
	return (0);
}

