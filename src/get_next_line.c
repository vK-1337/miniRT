/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 18:19:03 by vda-conc          #+#    #+#             */
/*   Updated: 2024/07/29 17:25:35 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_check_stash(char *str)
{
	ssize_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int	ft_read(char **stash, char *buffer, int fd)
{
	int	bytes_read;
	int	is_line_i;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	buffer[bytes_read] = '\0';
	if (!*stash)
		*stash = ft_gnl_strdup(buffer);
	else
		*stash = ft_gnl_strjoin(*stash, buffer);
	if (bytes_read == 0)
		return (ft_read_return(*stash, buffer));
	is_line_i = ft_check_stash(*stash);
	while (is_line_i == -1 && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		buffer[bytes_read] = '\0';
		if (bytes_read > 0)
		{
			*stash = ft_gnl_strjoin(*stash, buffer);
			is_line_i = ft_check_stash(*stash);
		}
	}
	free(buffer);
	return (is_line_i);
}

void	ft_clean_stash(char **stash, ssize_t index)
{
	ssize_t	i;
	ssize_t	limit;
	char	*new_stash;

	limit = 0;
	while ((*stash)[limit + index])
		limit++;
	new_stash = malloc((limit + 1) * sizeof(char));
	if (!new_stash)
		return ;
	i = 0;
	while (i < limit)
	{
		new_stash[i] = (*stash)[i + index + 1];
		i++;
	}
	free(*stash);
	new_stash[i] = '\0';
	*stash = new_stash;
	return ;
}

char	*ft_fill_line(char **stash, ssize_t index)
{
	ssize_t	i;
	char	*line;

	line = malloc(((index + 1) + 1) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (i <= index)
	{
		line[i] = (*stash)[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd, int err)
{
	t_norme		norme;
	static char	*stash;

	norme.line = NULL;
	norme.buffer = NULL;
	if (err)
		return (free(stash), NULL);
	if (fd < 0 || read(fd, norme.buffer, 0) == -1)
		return (0);
	norme.buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!norme.buffer)
		return (NULL);
	norme.line_index = ft_read(&stash, norme.buffer, fd);
	if (norme.line_index == -1 && ft_gnl_strlen(stash) == 0)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	else if (norme.line_index == -1 && (ft_gnl_strlen(stash) > 0))
		norme.line_index = ft_gnl_strlen(stash) - 1;
	norme.line = ft_fill_line(&stash, norme.line_index);
	if (norme.line == NULL)
		return (NULL);
	return (ft_clean_stash(&stash, norme.line_index), norme.line);
}
