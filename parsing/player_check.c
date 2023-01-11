/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 23:44:35 by alouzizi          #+#    #+#             */
/*   Updated: 2023/01/11 01:12:00 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	if_map_valid(t_map	*map)
{
	int	i;
	int	j;
	int	player_n;

	i = -1;
	player_n = 0;
	while (map->map[++i])
	{
		j = -1;
		while (map->map[i][++j])
		{
			if (!check_elem(&player_n, map, i, j))
				return (false);
		}
	}
	if (player_n != 1)
		return (printf("player position(number) !valid\n"), false);
	return (true);
}

bool	check_elem(int *player_count, t_map *map, int i, int j)
{
	if (map->map[i][j] == '0')
	{
		if (!check_sides(map->map, i, j))
			return (printf("map not closed !!\n"), false);
	}
	else if (if_player(map->map[i][j]))
	{
		if ((++(*player_count)) != 1)
			return (printf("player (number) not valid\n"), false);
		if (!check_sides(map->map, i, j))
			return (printf("player position not valid\n"), false);
		map->px = j;
		map->py = i;
	}
	else if (map->map[i][j] != ' ' && map->map[i][j] != '1')
	{
		return (printf("caracter not valid\n"), false);
	}	
	return (true);
}

bool	if_player(char c)
{
	if (c == 'S' || c == 'N' || c == 'W' || c == 'E')
		return (true);
	return (false);
}
