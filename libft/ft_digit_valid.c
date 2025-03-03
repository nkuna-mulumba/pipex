/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_digit_valid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <jcongolo@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-04 14:26:18 by jcongolo          #+#    #+#             */
/*   Updated: 2025-02-04 14:26:18 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_digit_valid(const char *str)
{
	int	i;
	int	has_sign;

	if (!str || str[0] == '\0')
		return (0);
	has_sign = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '-' || str[i] == '+')
		{
			if (has_sign || (i > 0 && str[i - 1] != ' ') || str[i + 1] == '\0')
				return (0);
			has_sign = 1;
		}
		else if (!ft_isdigit(str[i]) && str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
