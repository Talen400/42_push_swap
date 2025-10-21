/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_binary_search.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:45:25 by tlavared          #+#    #+#             */
/*   Updated: 2025/10/20 14:00:38 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	*ft_array_binary(t_stack *list)
{
	t_node	*node;
	int		i;
	int		*values;

	node = list->head;
	i = 0;
	values = malloc (sizeof(int ) * list->size);
	if (!values)
		return (NULL);
	while (i < list->size)
	{
		values[i] = node->value;
		node = node->next;
		i++;
	}
	return (values);
}

int	ft_binary_search(int *arr, int search, int len)
{
	int	mid;
	int	left;
	int	right;

	left = 0;
	right = len;
	while (left < right)
	{
		mid = left + (right - left) / 2;
		if (arr[mid] < search)
			left = mid + 1;
		else
			right = mid;
	}
	return (left);
}
