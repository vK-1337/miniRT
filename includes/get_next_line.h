/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vda-conc <vda-conc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 16:28:18 by vda-conc          #+#    #+#             */
/*   Updated: 2024/07/31 11:15:37 by vda-conc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <fcntl.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_norme
{
	char	*line;
	char	*buffer;
	int		line_index;
}			t_norme;

char		*ft_gnl_strdup(char *s);
int			ft_check_stash(char *str);
char		*get_next_line(int fd, int err);
size_t		ft_gnl_strlen(char *str);
char		*ft_gnl_strjoin(char *s1, char *s2);
char		*ft_fill_line(char **stash, ssize_t index);
void		ft_clean_stash(char **stash, ssize_t index);
int			ft_read(char **stash, char *buffer, int fd);
int			ft_read_return(char *stash, char *buffer);

#endif
