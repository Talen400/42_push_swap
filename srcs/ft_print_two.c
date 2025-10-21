/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_two.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:29:24 by tlavared          #+#    #+#             */
/*   Updated: 2025/10/20 13:36:45 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_rr(t_stack *a, t_stack *b)
{
	ft_rotate(a);
	ft_rotate(b);
	write(1, "rr\n", 3);
}

void	ft_rrr(t_stack *a, t_stack *b)
{
	ft_rrotate(a);
	ft_rrotate(b);
	write(1, "rrr\n", 4);
}
