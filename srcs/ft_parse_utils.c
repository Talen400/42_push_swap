/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 06:24:47 by tlavared          #+#    #+#             */
/*   Updated: 2025/10/23 06:25:20 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

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
