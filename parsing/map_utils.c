/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 23:44:20 by alouzizi          #+#    #+#             */
/*   Updated: 2023/01/11 01:12:00 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	find_texture(t_map *map, int type, int index)
{
	if (type == NO)
	{
		cut(map->o_map[index] + 3, &map->no);
		if (!if_xpm(map->no))
			return (false);
	}
	if (type == SO)
	{
		cut(map->o_map[index] + 3, &map->so);
		if (!if_xpm(map->so))
			return (false);
	}
	if (type == EA)
	{
		cut(map->o_map[index] + 3, &map->ea);
		if (!if_xpm(map->ea))
			return (false);
	}
	if (type == WE)
	{
		cut(map->o_map[index] + 3, &map->we);
		if (!if_xpm(map->we))
			return (false);
	}
	return (true);
}

bool	if_xpm(char *str)
{
	if (!ft_strncmp(str +(ft_strlen(str) - 4), ".xpm", 4))
		return (true);
	printf("texture invalid xpm");
	return (false);
}

bool	find_colors(t_map *map, int type, int index)
{
	if (type == F)
	{
		if (!get_color(map, index, 'f'))
		{
			printf("floor color invalid\n");
			return (false);
		}
	}
	if (type == C)
	{
		if (!get_color(map, index, 'c'))
		{
			printf("floor color invalid\n");
			return (false);
		}
	}		
	return (true);
}

bool	get_color(t_map *map, int index, char flag)
{
	char	**tmp;
	char	*color;
	int		i;

	i = 0;
	check_commas(map->o_map, index);
	tmp = ft_split(cut(map->o_map[index] + 2, &color), ',');
	free(color);
	if (tab_len(tmp) != 3)
		return (false);
	while (i < 3)
	{
		if (!ft_isdigit(tmp[i]))
			return (false);
		if (flag == 'f')
			map->f[i] = ft_atoi(tmp[i]);
		else
			map->c[i] = ft_atoi(tmp[i]);
		i++;
	}
	free_tab(&tmp);
	return (true);
}
