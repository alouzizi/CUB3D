/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 23:45:21 by alouzizi          #+#    #+#             */
/*   Updated: 2023/01/11 02:08:26 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*ft_read(char *str, int fd)
{
	int		r;
	char	*tmp;
	char	buf[1 + 1];

	r = 1;
	if (!str)
		str = ft_strdup("");
	while (!ft_strchr(str, '\n') && (r > 0))
	{
		r = read(fd, buf, 1);
		if (r == -1)
		{
			free(str);
			str = NULL;
			return (0);
		}
		buf[r] = '\0';
		tmp = str;
		str = ft_strjoin(str, buf);
		free(tmp);
	}
	return (str);
}

static char	*ft_check(int fd, char *str)
{
	if (fd < 0 || 1 <= 0)
		return (NULL);
	str = ft_read(str, fd);
	if (!str)
		return (NULL);
	return (str);
}

void	ft_free(char **str)
{
	free(*str);
	*str = NULL;
}

static char	*get_rest(char *str)
{
	char	*rest;

	rest = ft_strdup(ft_strchr(str, '\n') + 1);
	free(str);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;

	str = ft_check(fd, str);
	if (!str)
		return (NULL);
	if (ft_strlen(str) > 0 && !ft_strchr(str, '\n'))
	{
		line = ft_strdup(str);
		ft_free(&str);
		return (line);
	}
	else if (ft_strchr(str, '\n'))
	{
		line = ft_substr(str, 0, ft_strchr(str, '\n') - str + 1);
		if (*(ft_strchr(str, '\n') + 1) != '\0')
			str = get_rest(str);
		else
			ft_free(&str);
		return (line);
	}
	ft_free(&str);
	return (0);
}
