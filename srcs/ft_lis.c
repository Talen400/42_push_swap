/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 02:57:09 by tlavared          #+#    #+#             */
/*   Updated: 2025/10/21 03:32:21 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	ft_dp_prev(t_stack *stack, int *values, int **dp, int **prev)
{
	int	i;
	int	j;

	i = -1;
	while (++i < stack->size)
	{
		j = -1;
		while (++j < i)
		{
			if (values[j] < values[i] && (*dp)[j] + 1 > (*dp)[i])
			{
				(*dp)[i] = (*dp)[j] + 1;
				(*prev)[i] = j;
			}
		}
	}
}

static void	ft_len_lis(t_stack *stack, int *values, int **dp, int **prev)
{
	int	i;

	(*dp) = ft_calloc(stack->size, sizeof(int ));
	(*prev) = ft_calloc(stack->size, sizeof(int ));
	if (!(*dp) || !(*prev))
		return ;
	i = -1;
	while (++i < stack->size)
	{
		(*dp)[i] = 1;
		(*prev)[i] = -1;
	}
	ft_dp_prev(stack, values, dp, prev);
}

static t_lis	*ft_construct_lis(t_stack *stack, int max_len, int max_index,
		int *prev)
{
	t_lis	*lis;
	int		index;

	lis = malloc(sizeof(t_lis));
	if (!lis)
		return (NULL);
	lis->is_in_lis = ft_calloc(stack->size, sizeof(int ));
	if (!lis->is_in_lis)
		return (NULL);
	lis->len = max_len;
	index = max_index;
	while (index != -1)
	{
		lis->is_in_lis[index] = 1;
		index = prev[index];
	}
	return (lis);
}

static t_lis	*ft_reconstruct_lis(t_stack *stack, int *dp, int *prev)
{
	t_lis	*lis;
	int		max_len;
	int		max_index;
	int		i;
	int		len;

	len = stack->size;
	i = 0;
	max_len = 0;
	while (++i < len)
	{
		if (dp[i] > max_len)
		{
			max_len = dp[i];
			max_index = i;
		}
	}
	lis = ft_construct_lis(stack, max_len, max_index, prev);
	if (!lis)
		return (NULL);
	return (lis);
}

t_lis	*ft_lis(t_stack *stack)
{
	t_lis	*lis;
	int		*values;
	int		*dp;
	int		*prev;

	values = ft_array_binary(stack);
	if (!values)
		return (NULL);
	ft_len_lis(stack, values, &dp, &prev);
	free(values);
	if (!dp)
		return (NULL);
	lis = ft_reconstruct_lis(stack, dp, prev);
	free(dp);
	free(prev);
	if (!lis)
		return (NULL);
	return (lis);
}
