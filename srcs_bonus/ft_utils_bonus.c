/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavared <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 03:00:22 by tlavared          #+#    #+#             */
/*   Updated: 2025/10/23 19:08:19 by tlavared         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/checker_bonus.h"

int	ft_handler_logic(char *str)
{
	ft_putstr_fd(str, 2);
	return (1);
}

void	ft_free_stacks(t_stack *a, t_stack *b)
{
	ft_stack_free(a);
	ft_stack_free(b);
}
