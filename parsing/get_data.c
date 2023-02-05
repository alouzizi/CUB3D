/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 01:37:03 by alouzizi          #+#    #+#             */
/*   Updated: 2023/02/05 06:29:46 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*get_path(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == ' ' || line[i] == '\n')
			line[i] = '\0';
		i++;
	}
	return (line);
}

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

	i = 0;
	map->row = 0;
	tmp = ft_strdup("");
	map->column = ft_strlen(line);
	while (line)
	{
		tmp = free_strjoin(tmp, line, 3);
		map->row++;
		line = get_next_line(fd);
	}
	i = 0;
	while (tmp[i])
	{
		if (tmp[i] == '\n' && tmp[i + 1] == '\n')
			error_exit("Error\nMissing data\n");
		i++;
	}
	i = 0;
	map->map = ft_split(tmp, '\n');
	free(tmp);
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
			map->map[i] = free_strjoin(map->map[i], genarate(map->column - ft_strlen(map->map[i])), 3);
		i++;
	}
	// if (!check_wall(map->map, map->row, map->column))
	// {
	// 	ft_putstr_fd("Error\nMissing wall\n", 2);
	// 	exit(1);
	// }
}

// int check_wall(char **map ,int row, int col)
// {
// 	int x;
// 	int y;

// 	x = 0;
// 	y = 0;
// 	row -= 1;
// 	col -= 1;
// 	while(map[y])
// 	{
// 		while(map[y][x])
// 		{
// 			if (map[y][x] == 0 && (y == 0  || x == 0 || x  == row || y == col ))
// 				return (0);
// 		}
// 		y++;
// 	}
// }

void	get_data(int fd, t_map *map)
{
	char	*line;
	int		i;
	int		found[7];

	i = 7;
	line = get_next_line(fd);
	while (i--)
		found[i] = 0;
	if (!line)
		error_exit("Error\nMissing data\n");
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
		{
			i = 6;
			while (i--)
			{
				if (found[i] == 0 || found[i] > 1)
					error_exit("Error\nMissing data\n");
			}
			found[6] = 1;
			break ;
		}
		free(line);
		line = get_next_line(fd);
	}
	if (found[6] == 0)
		error_exit("Error\nMissing data\n");
	get_map(fd, map, line);
	//free(line);
	get_player_position(map);
}
