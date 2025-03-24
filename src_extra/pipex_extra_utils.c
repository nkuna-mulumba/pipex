/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_extra_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcongolo <jcongolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 11:39:26 by jcongolo          #+#    #+#             */
/*   Updated: 2025/03/23 12:58:10 by jcongolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static int	ft_len(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

static char	*strjoin_and_free(char *s1, char *s2)
{
	char	*joined;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	joined = (char *)malloc(sizeof(char) * (ft_len(s1) + ft_len(s2) + 1));
	if (!joined)
		return (NULL);
	if (s1)
	{
		while (s1[i])
		{
			joined[i] = s1[i];
			i++;
		}
	}
	while (s2[j])
	{
		joined[i++] = s2[j++];
	}
	joined[i] = '\0';
	free(s1);
	return (joined);
}

static char	*update_line(char *line, char buffer[], int *buffer_pos)
{
	char	temp[2];

	temp[0] = buffer[(*buffer_pos)++];
	temp[1] = '\0';
	return (strjoin_and_free(line, temp));
}

char	*ft_get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	static int	buffer_read = 0;
	static int	buffer_pos = 0;
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		if (buffer_pos >= buffer_read)
		{
			buffer_read = read(fd, buffer, BUFFER_SIZE);
			buffer_pos = 0;
			if (buffer_read <= 0)
				break ;
		}
		line = update_line(line, buffer, &buffer_pos);
		if (!line)
			return (NULL);
		if (line[ft_len(line) - 1] == '\n')
			break ;
	}
	return (line);
}
