/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_assets.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 23:43:32 by alouzizi          #+#    #+#             */
/*   Updated: 2023/01/23 16:57:09 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	parsing_assets(t_map *map)
{
	int	i;
	int	type;

	i = 0;
	while (i < 6)
	{
		type = get_type(map->o_map[i]);
		if (!type)
		{
			ft_putstr_fd("Error:\nmap non valid\n", 2);
			return (false);
		}
		if (type == F || type == C)
		{
			if (!find_colors(map, type, i))
				return (false);
		}
		else
		{
			if (!find_texture(map, type, i))
				return (false);
		}
		i++;
	}
	return (true);
}

int	tab_len(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

bool	assets_check(t_map *map)
{
	int	i;

	i = 0;
	if (tab_len(map->o_map) < 9)
	{
		ft_putstr_fd("Error:\nmap non valid\n", 2);
		return (false);
	}
	if (!parsing_assets(map))
		return (false);
	return (true);
}

bool	range_check(int num)
{
	if (num < 0 || num > 255)
		return (false);
	return (true);
}

bool	if_valid(int *tab)
{
	int		i;

	i = 0;
	while (i < 3)
	{
		if (tab[i] == -1 || !range_check(tab[i]))
		{
			printf("this is the tab %d\n", tab[i]);
			return (false);
		}	
		i++;
	}
	return (true);
}
