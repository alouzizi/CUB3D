/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 01:37:03 by alouzizi          #+#    #+#             */
/*   Updated: 2023/02/05 11:06:57 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	get_texture(char *line, t_map *map, int i)
{
	int	j;

	j = 2;
	while (line[j] == ' ')
		j++;
	line = get_path(line);
	if (i == NO)
		map->no = ft_strdup(&line[j]);
	else if (i == SO)
		map->so = ft_strdup(&line[j]);
	else if (i == WE)
		map->we = ft_strdup(&line[j]);
	else if (i == EA)
		map->ea = ft_strdup(&line[j]);
	return (1);
}

int	get_color(char *line, t_map *map, int i)
{
	int	j;
	int	r;
	int	g;
	int	b;

	j = 1;
	while (line[j] == ' ')
		j++;
	r = ft_atoi(&line[j]);
	while (line[j] != ',')
		j++;
	j++;
	g = ft_atoi(&line[j]);
	while (line[j] != ',')
		j++;
	j++;
	b = ft_atoi(&line[j]);
	if (i == F)
		map->ff = (r << 16) + (g << 8) + b;
	else if (i == C)
		map->cc = (r << 16) + (g << 8) + b;
	return (1);
}

void	get_map(int fd, t_map *map, char *line)
{
	char	*tmp;
	int		i;
	int		j;

	j = 0;
	i = 0;
	join_lines(map, line, fd);
	while (map->map[i])
	{
		if ((int)ft_strlen(map->map[i]) > map->column)
			map->column = ft_strlen(map->map[i]);
		i++;
	}
	i = 0;
	while (map->map[i])
	{
		if (((int)ft_strlen(map->map[i])) < map->column)
		{
			tmp = genarate(map->column - ft_strlen(map->map[i]));
			map->map[i] = free_strjoin(map->map[i], tmp, 3);
		}
		i++;
	}
	if (check_wall(map->map) == 0)
		error_exit("Error\nMissing wall\n");
}

char	*found_data(char *line, t_map *map, int fd, int i)
{
	int	found[6];

	while (i--)
		found[i] = 0;
	while (line)
	{
		if (line[0] == 'N' && line[1] == 'O')
			found[0] += get_texture(line, map, NO);
		else if (line[0] == 'S' && line[1] == 'O')
			found[1] += get_texture(line, map, SO);
		else if (line[0] == 'W' && line[1] == 'E')
			found[2] += get_texture(line, map, WE);
		else if (line[0] == 'E' && line[1] == 'A')
			found[3] += get_texture(line, map, EA);
		else if (line[0] == 'F')
			found[4] += get_color(line, map, F);
		else if (line[0] == 'C')
			found[5] += get_color(line, map, C);
		else if (line[0] == '0' || line[0] == '1' || line[0] == ' ')
			return (check(found, line));
		free(line);
		line = get_next_line(fd);
	}
	return (NULL);
}

void	get_data(int fd, t_map *map)
{
	char	*line;
	int		i;
	int		j;

	line = get_next_line(fd);
	if (!line)
		error_exit("Error\nMissing data\n");
	line = found_data(line, map, fd, 6);
	if (!line)
		error_exit("Error\nMissing data\n");
	get_map(fd, map, line);
	j = -1;
	while (map->map[++j])
	{
		i = 0;
		while (map->map[j][i])
		{
			if (!valid(&map->map[j][i]) && map->map[j][i] != ' ')
				error_exit("Error\nInvalid map\n");
			i++;
		}
	}
	get_player_position(map);
}
