/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 04:55:33 by alouzizi          #+#    #+#             */
/*   Updated: 2023/02/05 09:56:03 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*ft_calloc(int size)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(size);
	while (i < size)
	{
		str[i] = 0;
		i++;
	}
	return (str);
}

char	*genarate(int size)
{
	char	*str;
	int		i;

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

void	get_player_position(t_map *map)
{
	int	found;
	int	y;
	int	x;

	y = 0;
	x = 0;
	found = 0;
	while (map->map[y])
	{
		while (map->map[y][x])
		{
			if (map->map[y][x] == 'N' || map->map[y][x] == 'S'
				|| map->map[y][x] == 'E' || map->map[y][x] == 'W')
			{
				map->px = x;
				map->py = y;
				found += 1;
			}
			x++;
		}
		x = 0;
		y++;
	}
	if (!found || found > 1)
		error_exit("Error\nplayer position notfound or more than one player\n");
}

void	error_exit(char *str)
{
	ft_putstr_fd(str, 2);
	exit(1);
}

char	*check(int found[6], char *line)
{
	int	i;

	i = 6;
	while (i--)
	{
		if (found[i] == 0 || found[i] > 1)
			error_exit("Error\nMissing data\n");
	}
	return (line);
}
