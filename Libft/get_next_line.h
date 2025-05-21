/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbasak <tbasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:55:18 by lsaiti            #+#    #+#             */
/*   Updated: 2025/05/20 13:03:44 by tbasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include "libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 500
# endif

typedef struct s_buffer
{
	char	buffer[BUFFER_SIZE];
	long	buff_pos;
	long	bytesread;
	long	buff_read;
}	t_buffer;

typedef struct s_string
{
	char	*str;
}	t_string;

char	*get_next_line(int fd);
char	*get_next_line_buff(int fd, t_buffer *b, t_string *s);
char	*get_next_line_buff_set(int fd, t_string *s, t_buffer *b);
void	get_next_line_read(int fd, t_buffer *b);
char	*get_next_line_onebuff(int fd, t_string *s, t_buffer *b);
void	*ft_freestr(char **str);
char	*ft_strjoin_ledion(char *s1, char const *s2, long n);
void	reset_gnl(t_buffer b[]);

#endif
