/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 02:19:44 by alouzizi          #+#    #+#             */
/*   Updated: 2023/01/08 07:48:43 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_map(t_structs *g)
{
	int x;
	int y;

	y = x = 0;
	while (y < g->map->row)
	{
		while (x < g->map->column)
		{
			if (mape[y][x] == 1)
				draw_wall(g, x * 42, y * 42, 0xFFFFFF);
			else
				draw_wall(g, x * 42, y * 42, 0x00FF0000);
			x++;
		}
		x = 0;
		y++;
	}
}

void draw_wall(t_structs *g, int x, int y, int color)
{
	int i;
	int j;

	i = j = 0;
	while (i < 42)
	{
		while (j < 42)
		{
			if (i == 0)
				my_mlx_pixel_put(g->mlx, x + i, y + j, 0x000000);
			else
				my_mlx_pixel_put(g->mlx, x + i, y + j, color);
			j++;
		}
		my_mlx_pixel_put(g->mlx, x + i, y + (j - 1), 0x000000);
		j = 0;
		i++;
	}
}
