/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 23:44:10 by alouzizi          #+#    #+#             */
/*   Updated: 2023/01/11 01:21:18 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	check_map(char *str, t_structs *g)
{
	g->map = malloc(sizeof(t_map));
	if (!g->map)
	{
		printf("Erro Malloc failed\n");
		exit(1);
	}
	init_data(g->map);
	if (!get_map(str, g->map))
		return (false);
	if (!assets_check(g->map))
		return (false);
	if (!check_p_map(g->map))
		return (false);
	return (true);
}

bool	check_sides(char **player_map, int i, int j)
{
	if (i == 0 || j == 0 || i == tab_len(player_map) - 1
		|| j == max_width(player_map) - 1)
		return (false);
	if (player_map[i - 1][j] == ' ')
	{
		return (false);
	}
	if (player_map[i + 1][j] == ' ')
		return (false);
	if (player_map[i][j - 1] == ' ')
		return (false);
	if (player_map[i][j + 1] == ' ')
		return (false);
	return (true);
}

int	get_type(char *type)
{
	if (!ft_strncmp(type, "NO ", 3))
		return (NO);
	if (!ft_strncmp(type, "SO ", 3))
		return (SO);
	if (!ft_strncmp(type, "WE ", 3))
		return (WE);
	if (!ft_strncmp(type, "EA ", 3))
		return (EA);
	if (!ft_strncmp(type, "F ", 2))
		return (F);
	if (!ft_strncmp(type, "C ", 2))
		return (C);
	return (0);
}

bool	check_commas(char **str, int index)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[index][i])
	{
		if (str[index][i] == ',')
		{
			count++;
			if (count > 2)
			{
				printf("Too many commas in color\n");
				exit(1);
			}
		}
		i++;
	}
	return (true);
}
