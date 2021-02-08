/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaudot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 17:29:58 by abaudot           #+#    #+#             */
/*   Updated: 2021/02/08 20:07:01 by abaudot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SISE
# define BUFFER_SISE 42
#endif

/*
** 	simple littel function
*/

static const char	*find_nl(const char *s)
{
	while (*s)
	{
		if (*s == '\n')
			return (s);
		++s;
	}
	return (s);
}

static void			ft_memcpy(char *d, const char *s, int n)
{
	while (n--)
		*d++ = *s++;
	*d = 0;
}

static void			ft_strcpy(char *d, const char *s)
{
	while (*s)
		*d++ = *s++;
	*d = 0;
}

/*
**	malloc function
*/

static char			ft_join(char **line, const char *bff,
	   	const int line_sz, const int bff_sz)
{
	char *tmp = *line;

	if (!(*line = malloc(line_sz + bff_sz + 1)))
	{
		if (line_sz)
			free(tmp);
	   return (0);	
	}
	ft_memcpy(*line, tmp, line_sz);
	if (line_sz)
		free(tmp);
	ft_memcpy(*line + line_sz, bff, bff_sz);
	return (1);
}

/*
**	return function
*/

static int			add_anl(char **line, char *bff,
	   	const int a_nl, const int line_sz)
{
	if (!(ft_join(line, bff, line_sz, a_nl)))
		return (-1);
	ft_strcpy(bff, bff + a_nl + 1);
	return (1);
}

static int	read_anl(char **line, char *bff, int line_sz, int fd)
{
	int				av_read;
	const char		*a_nl;

	while ((av_read = read(fd, bff, BUFFER_SISE)) > 0)
	{
		bff[av_read] = 0;
		if (*(a_nl = find_nl(bff)))
			return (add_anl(line, bff, a_nl - bff, line_sz));
		if (!ft_join(line, bff, line_sz, av_read))
			return (-1);
		line_sz += av_read;
	}
	*bff = 0;
	if (av_read == -1)
	{
		if (line_sz)
			free(*line);
		return (-1);
	}
	if (!line_sz)
	{
		if (!(*line = malloc(1)))
			return (-1);
		**line = 0;
	}
	return (0);
}

int			get_next_line(int fd, char **line)
{
	static char		bff[BUFFER_SISE];
	const char		*a_nl;

	if (fd < 0 || fd > 1024 || BUFFER_SISE < 1 || !line)
		return (-1);
	if (!*bff)
		return (read_anl(line, bff, 0, fd));
	if (*(a_nl = find_nl(bff)))
		return (add_anl(line, bff, a_nl - bff, 0));
	ft_join(line, bff, 0, a_nl - bff);
	return (read_anl(line, bff, a_nl - bff, fd));
}
