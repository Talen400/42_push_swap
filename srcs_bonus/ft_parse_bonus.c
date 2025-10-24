/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 19:47:26 by tlavared          #+#    #+#             */
/*   Updated: 2025/10/23 18:24:02 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/checker_bonus.h"

static int	ft_convert(char *str, int i, long long *num_ll)
{
	if (str[i] == '\0' || !ft_isdigit(str[i]))
		return (0);
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		*num_ll = (*num_ll * 10) + (str[i] - '0');
		i++;
	}
	return (1);
}

static int	ft_valid(char *str, int *result_ptr)
{
	long long	num_ll;
	int			sign;
	int			i;

	num_ll = 0;
	sign = 1;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (!ft_convert(str, i, &num_ll))
		return (0);
	num_ll *= sign;
	if (num_ll > MAX_INT || num_ll < MIN_INT)
		return (0);
	*result_ptr = (int)num_ll;
	return (1);
}

static int	ft_parse_array(char **array, t_stack *stack)
{
	int	value;

	while (*array)
	{
		if (!ft_valid(*array, &value))
			return (1);
		ft_stack_push_back(stack, value);
		array++;
	}
	return (0);
}

static int	ft_split_and_parse(char *arg, t_stack *stack)
{
	char	**s_nums;
	int		err;

	s_nums = ft_split(arg, ' ');
	if (!s_nums || !s_nums[0])
	{
		if (s_nums)
			ft_free_split(s_nums);
		return (1);
	}
	err = ft_parse_array(s_nums, stack);
	ft_free_split(s_nums);
	return (err);
}

int	ft_parse(int argc, char **argv, t_stack *stack)
{
	int	i;
	int	value;

	if (argc < 2)
		return (0);
	i = 0;
	while (argv[i])
	{
		if (ft_strchr(argv[i], ' '))
		{
			if (ft_split_and_parse(argv[i], stack))
				return (1);
		}
		else
		{
			if (!ft_valid(argv[i], &value))
				return (1);
			ft_stack_push_back(stack, value);
		}
		i++;
	}
	if (ft_check_repeat(stack->head))
		return (1);
	return (0);
}
