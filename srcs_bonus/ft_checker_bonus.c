/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checker_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 18:08:17 by tlavared          #+#    #+#             */
/*   Updated: 2025/10/23 19:35:05 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/checker_bonus.h"

static int	ft_str_op(t_stack *a, t_stack *b, char *line)
{
	if (ft_strcmp("pb\n", line) == 0)
		ft_push(a, b);
	else if (ft_strcmp("pa\n", line) == 0)
		ft_push(b, a);
	else if (ft_strcmp("rb\n", line) == 0)
		ft_rotate(b);
	else if (ft_strcmp("ra\n", line) == 0)
		ft_rotate(a);
	else if (ft_strcmp("rrb\n", line) == 0)
		ft_rrotate(b);
	else if (ft_strcmp("rra\n", line) == 0)
		ft_rrotate(a);
	else if (ft_strcmp("sb\n", line) == 0)
		ft_swap(b);
	else if (ft_strcmp("sa\n", line) == 0)
		ft_swap(a);
	else if (ft_strcmp("ss\n", line) == 0)
		ft_ss(a, b);
	else if (ft_strcmp("rr\n", line) == 0)
		ft_rr(a, b);
	else if (ft_strcmp("rrr\n", line) == 0)
		ft_rrr(a, b);
	else
		return (1);
	return (0);
}

static int	ft_while_sort(t_stack *a, t_stack *b)
{
	char	*line;

	while (1)
	{
		line = get_next_line(0);
		if (!line)
			break ;
		if (ft_str_op(a, b, line))
		{
			free(line);
			return (1);
		}
		free(line);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_stack		*a;
	t_stack		*b;

	if (argc < 2)
		return (1);
	a = ft_stacknew();
	b = ft_stacknew();
	if (!a || !b)
		return (1);
	if (ft_parse(argc, argv + 1, a))
	{
		ft_free_stacks(a, b);
		return (ft_handler_logic("Error\n"));
	}
	if (ft_while_sort(a, b))
	{
		ft_free_stacks(a, b);
		return (ft_handler_logic("Error\n"));
	}
	if (ft_is_sorted(a, b))
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
	ft_free_stacks(a, b);
	return (0);
}
