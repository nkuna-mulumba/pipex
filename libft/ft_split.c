/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 22:51:46 by jcongolo          #+#    #+#             */
/*   Updated: 2024/10/18 16:41:05 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_substrings(char const *s, char c)
{
	int	i;
	int	is_substring;
	int	num_substrings;

	if (!s || *s == '\0')
		return (0);
	i = 0;
	is_substring = 0;
	num_substrings = 0;
	while (s[i])
	{
		if (s[i] != c && is_substring == 0)
		{
			is_substring = 1;
			num_substrings++;
		}
		else if (s[i] == c)
			is_substring = 0;
		i++;
	}
	if (num_substrings == 0)
		return (0);
	return (num_substrings);
}

void	ft_freememoria(char **split_strings, int allocated)
{
	int	i;

	if (!split_strings)
		return ;
	i = 0;
	while (i < allocated)
	{
		if (split_strings[i])
		{
			free(split_strings[i]);
			split_strings[i] = NULL;
		}
		i++;
	}
	free(split_strings);
}

int	ft_fill_substrings(const char *s, char c, char **split_strings)
{
	int	i;
	int	substr_start;
	int	index_substr;

	i = -1;
	substr_start = -1;
	index_substr = 0;
	while (s[++i])
	{
		if (s[i] != c && substr_start < 0)
			substr_start = i;
		if ((s[i] == c || s[i + 1] == '\0') && (substr_start >= 0))
		{
			split_strings[index_substr] = ft_substr(s, substr_start,
					i - substr_start + (s[i] != c));
			if (!split_strings[index_substr])
			{
				ft_freememoria(split_strings, index_substr);
				return (0);
			}
			index_substr++;
			substr_start = -1;
		}
	}
	return (split_strings[index_substr] = NULL, 1);
}

char	**ft_split(char const *s, char c)
{
	char	**split_strings;
	int		num_substrings;

	if (!s)
		return (NULL);
	num_substrings = ft_count_substrings(s, c);
	if (num_substrings == 0)
		return (NULL);
	split_strings = malloc((num_substrings + 1) * sizeof(char *));
	if (!split_strings)
		return (NULL);
	if (!ft_fill_substrings(s, c, split_strings))
	{
		ft_freememoria(split_strings, num_substrings);
		return (NULL);
	}
	return (split_strings);
}

/*
static int	ft_count_substrings(char const *s, char c)
{
	int	i;
	int	is_substring;
	int	num_substrings;

	if (!s)
		return (0);
	i = 0;
	is_substring = 0;
	num_substrings = 0;
	while (s[i])
	{
		if (s[i] != c && is_substring == 0)
		{
			is_substring = 1;
			num_substrings++;
		}
		else if (s[i] == c)
			is_substring = 0;
		i++;
	}
	return (num_substrings);
}

int	ft_fill_substrings(const char *s, char c, char **split_strings)
{
	int	i;
	int	substr_start;
	int	index_substr;

	i = 0;
	substr_start = -1;
	index_substr = 0;
	while (s[i])
	{
		if (s[i] != c && substr_start < 0)
			substr_start = i;
		if ((s[i] == c || s[i + 1] == '\0') && (substr_start >= 0))
		{
			split_strings[index_substr++] = ft_substr(s, substr_start,
					i - substr_start + (s[i] != c));
			substr_start = -1;
			if (!split_strings[index_substr - 1])
				return (0);
		}
		i++;
	}
	split_strings[index_substr] = NULL;
	return (1);
}

void	ft_freememoria(char **split_strings)
{
	int	i;

	if (!split_strings)
 		return;
	i = 0;
	while (split_strings[i])
	{
		free(split_strings[i]);
		split_strings[i] = NULL;
		i++;
	}
	free(split_strings);
	split_strings = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**split_strings;

	if (!s)
		return (0);
	split_strings = malloc((ft_count_substrings(s, c) + 1) * sizeof(char *));
	if (!split_strings)
		return (NULL);
	if (!ft_fill_substrings(s, c, split_strings))
	{
		ft_freememoria(split_strings);
		return (NULL);
	}
	return (split_strings);
}
int main()
{
	const char	*input_string = "Eu sou Mangop";
	char	delimiter = ' ';
	char	**substrings_array = ft_split(input_string, delimiter);
	int	i = 0;

	if (substrings_array)
	{
		while (substrings_array[i] != NULL)
		{
			printf("%s\n", substrings_array[i]);
			free(substrings_array[i]);
			i++;
		}
		free(substrings_array);
	}
	else
	{
		return (0);
	}
	return 0;
}
*/
