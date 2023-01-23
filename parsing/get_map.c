/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 23:43:51 by alouzizi          #+#    #+#             */
/*   Updated: 2023/01/23 17:01:23 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	get_map(char *file, t_map *map)
{
	int		i;
	int		fd;
	char	*line;

	if (!ft_check_extention(file))
		return (false);
	fd = open_file(file);
	map->o_map = (char **)malloc(sizeof(char *));
	if (!map->o_map || !fd)
		return (false);
	line = get_next_line(fd);
	i = 0;
	map->o_map[i] = line;
	while (line)
	{
		line = get_next_line(fd);
		if (!is_empty(&line, i))
			continue ;
		i++;
		map->o_map = ft_realoc(map->o_map, i + 1);
		map->o_map[i] = line;
	}
	return (true);
}

bool	ft_check_extention(char *str)
{
	int	i;

	i = ft_strlen(str);
	if (str[i -1] != 'b' || str[i -2] != 'u'
		|| str[i -3] != 'c' || str[i -4] != '.')
	{
		ft_putstr_fd("File extension must be '.cub'\n", 2);
		return (false);
	}
	return (true);
}

bool	is_empty(char **line, int i)
{
	if (*line && i < 6 && *line[0] == '\n')
	{
		free (*line);
		return (false);
	}
	return (true);
}

int	open_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("Error");
		return (0);
	}
	return (fd);
}

char	*trim_n(char *str)
{
	if (str[ft_strlen(str) - 1] == '\n')
		return (ft_substr(str, 0, ft_strlen(str) - 1));
	return (ft_strdup(str));
}
