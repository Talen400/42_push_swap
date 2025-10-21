/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:21:54 by tlavared          #+#    #+#             */
/*   Updated: 2025/10/20 13:25:13 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_pb(t_stack *a, t_stack *b)
{
	ft_push(a, b);
	write(1, "pb\n", 3);
}

void	ft_pa(t_stack *a, t_stack *b)
{
	ft_push(b, a);
	write(1, "pa\n", 3);
}

void	ft_ra(t_stack *a)
{
	ft_rotate(a);
	write(1, "ra\n", 3);
}

void	ft_rb(t_stack *b)
{
	ft_rotate(b);
	write(1, "rb\n", 3);
}
