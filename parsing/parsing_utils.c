/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 04:55:33 by alouzizi          #+#    #+#             */
/*   Updated: 2023/02/03 06:03:51 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	get_texture(char *line, t_map *map, int i)
{
	int	j;

	j = 2;
	while (line[j] == ' ')
		j++;
	if (i == NO)
		map->no = ft_strdup(&line[j]);
	else if (i == SO)
		map->so = ft_strdup(&line[j]);
	else if (i == WE)
		map->we = ft_strdup(&line[j]);
	else if (i == EA)
		map->ea = ft_strdup(&line[j]);
	return (i);
}

int Get_color(char *line, t_map *map, int i)
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
	return (i);
}


char *ft_calloc(int size)
{
	char *str;
	int i;

	i = 0;
	str = malloc(size);
	while (i < size)
	{
		str[i] = 0;
		i++;
	}
	return (str);
}

char *genarate(int size)
{
	char *str;
	int i;

	i = 0;
	str = malloc(size + 1);
	if (!str)
		return (NULL);
	while (i < size)
	{
		str[i] = ' ';
		i++;
	}
	str[i] = '\n';
	return (str);
}
void Get_map(int fd, t_map *map, char *line)
{
	int i;
	char *tmp;

	i = 0;
	map->row = 0;
	tmp = ft_strdup("");
	map->column = ft_strlen(line);
	while(line)
	{
		tmp = ft_strjoin(tmp, line);
		map->row++;
		line = get_next_line(fd);
	}
	// puts(tmp);
	// while (tmp[i])
	// {
	// 	if (tmp[i] == ' ')
	// 		tmp[i] = '1';
	// 	i++;
	// }
	i = 0;
	map->map =  ft_split(tmp, '\n');
	while(map->map[i])
	{
		if ((int) ft_strlen(map->map[i]) > map->column)
			map->column = ft_strlen(map->map[i]);
		i++;
	}
	//puts("*******************************");
	i = 0;
	while(map->map[i])
	{
		if (((int) ft_strlen(map->map[i])) < map->column)
			map->map[i] = ft_strjoin(map->map[i], genarate(map->column - ft_strlen(map->map[i])));
		//printf("len: %d\n", (int) ft_strlen(map->map[i]));
		i++;
	}
	i =0 ;
	while(map->map[i])
	{
		printf("%s", map->map[i]);
		// printf("len: %d\n", (int) ft_strlen(map->map[i]));
		i++;
	}
}


void Get_data(int fd, t_map *map)
{
	char	*line;
	int		i;
	
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == 'N' && line[1] == 'O')
			i += get_texture(line, map, NO);
		else if (line[0] == 'S' && line[1] == 'O')
			i += get_texture(line, map, SO);
		else if (line[0] == 'W' && line[1] == 'E')
			i += get_texture(line, map, WE);
		else if (line[0] == 'E' && line[1] == 'A')
			i += get_texture(line, map, EA);
		else if (line[0] == 'F')
			i += Get_color(line, map, F);
		else if (line[0] == 'C')
			i += Get_color(line, map, C);
		else if (line[0] == '0' || line[0] == '1' || line[0] == ' ' )
		{
			if (i != 21)
			{
				ft_putstr_fd("Error\nMissing data\n", 2);
				exit(1);
			}
			break;
		}
		free(line);
		line = get_next_line(fd);
	}
	Get_map(fd, map, line);
	free(line);
	puts("******************");
	printf("NO: %s\n", map->no);
	printf("SO: %s\n", map->so);
	printf("WE: %s\n", map->we);
	printf("EA: %s\n", map->ea);
	printf("F: %d\n", map->ff);
	printf("C: %d\n", map->cc);
	// printf("MAP: %s\n", map->map);
	puts("******************");
}