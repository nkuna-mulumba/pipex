/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_valid_argument.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <jcongolo@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-12 14:24:42 by jcongolo          #+#    #+#             */
/*   Updated: 2025-02-12 14:24:42 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_valid_argument(const char *str)
{
	char	**args;
	int		i;
	int		num_args;

	if (!str || str[0] == '\0')
		return (0);
	if (!ft_digit_valid(str))
		return (0);
	args = ft_split(str, ' ');
	if (!args)
		return (0);
	num_args = ft_count_substrings(str, ' ');
	i = 0;
	while (args[i] != NULL)
	{
		if (!ft_digit_valid(args[i]))
		{
			ft_freememoria(args, num_args);
			return (0);
		}
		i++;
	}
	ft_freememoria(args, num_args);
	return (1);
}
