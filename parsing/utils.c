/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 04:55:33 by alouzizi          #+#    #+#             */
/*   Updated: 2023/02/05 01:39:28 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


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
	str[i] = '\0';
	return (str);
}


void get_player_position(t_map *map)
{
	int y;
	int x;

	y = 0;
	x = 0;
	while(map->map[y])
	{
		while(map->map[y][x])
		{
			if (map->map[y][x] == 'N' || map->map[y][x] == 'S' || map->map[y][x] == 'E' || map->map[y][x] == 'W')
			{
				map->px = x;
				map->py = y;
				// map->player_dir = map->map[y][x];
				// map->map[y][x] = '0';
			}
			x++;
		}
		x = 0;
		y++;
	}
}
