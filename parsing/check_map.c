/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 23:43:40 by alouzizi          #+#    #+#             */
/*   Updated: 2023/02/03 05:24:11 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	check_p_map(t_map *map)
{
	if (!init_map(map))
	{
		printf("failed to init map!!\n");
		return (false);
	}
	if (!if_map_valid(map))
	{
		printf("player map not valide\n");
		return (false);
	}
	return (1);
}

void	check_new_line(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		if (str[i][0] == '\n' && (str[i + 1] && str[i + 1][0] == '1'))
		{
			ft_putstr_fd("Error\nfound a new line in the map\n", 2);
			exit(0);
		}
		i++;
	}
}

bool	init_map(t_map *map)
{
	int	i;

	i = 0;
	check_new_line(map->o_map);
	map->row = tab_len(map->o_map + 6);
	map->column = max_width(map->o_map + 6);
	map->map = (char **)malloc(sizeof(char *) * (map->row + 1));
	if (!map->map)
		return (false);
	while (i < map->row)
	{
		map->map[i] = str_proc(map->o_map[i + 6], map->column);
		if (!map->map[i])
			return (false);
		i++;
	}
	map->map[i] = NULL;
	return (true);
}

char	*str_proc(char *str, int width)
{
	char	*new;
	char	*spaces;
	char	*line;
	int		i;

	i = 0;
	if (width - (int)get_strlen(str) == 0)
		return (ft_substr(str, 0, get_strlen(str)));
	spaces = malloc(sizeof(char) * (width - get_strlen(str) + 1));
	if (!spaces)
		return (NULL);
	while (i < (width - get_strlen(str)))
		spaces[i++] = ' ';
	spaces[i] = '\0';
	line = trim_n(str);
	new = ft_strjoin(line, spaces);
	free(line);
	free(spaces);
	return (new);
}

int	get_strlen(char *s)
{
	size_t	i;
	char	*str;

	i = 0;
	if (!s)
		return (0);
	str = (char *)s;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}
