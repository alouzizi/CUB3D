/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 02:19:47 by alouzizi          #+#    #+#             */
/*   Updated: 2023/01/20 16:56:44 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player(t_structs *g)
{
	int	x;
	int	y;
	int	x1;
	int	y1;

	x = 0;
	y = 0;
	while (y < 10)
	{
		while (x < 10)
		{
			my_mlx_pixel_put(g->mlx, g->player->x + x, g->player->y + y,
				0x00FF00);
			x++;
		}
		x = 0;
		y++;
	}
	g->player->rotationangle += g->player->turndirection
		* g->player->rotationspeed;
	x1 = g->player->x + cos(g->player->rotationangle) * TILE_SIZE;
	y1 = g->player->y + sin(g->player->rotationangle) * TILE_SIZE;
	dda(g->mlx, g->player->x, g->player->y, x1, y1);
}

int	there_is_wall_at(float x, float y, t_structs *g)
{
	int	mapgridindexx;
	int	mapgridindexy;

	if (x <= 0 || x >= (g->map->column * TILE_SIZE)
		|| y <= 0 || y >= (g->map->row * TILE_SIZE))
		return (1);
	mapgridindexx = floor(x / TILE_SIZE);
	mapgridindexy = floor(y / TILE_SIZE);
	if (g->map->map[mapgridindexy][mapgridindexx] == '1')
		return (1);
	return (0);
}

int	there(float x, float y, t_structs *g)
{
	int	mapgridindexx;
	int	mapgridindexy;

	if (x <= 0 || x >= (g->map->column * TILE_SIZE)
		|| y <= 0 || y >= (g->map->row * TILE_SIZE))
		return (1);
	mapgridindexx = floor(x / TILE_SIZE);
	mapgridindexy = floor(y / TILE_SIZE);
	if (g->map->map[mapgridindexy][mapgridindexx] == '1')
		return (1);
	return (0);
}

float	distancebetweenpoints(t_structs *g, float x, float y)
{
	return (sqrt(pow(x - g->player->x, 2) + pow(y - g->player->y, 2)));
}

float	normalize_angle(float angle)
{
	angle = remainder(angle, (2 * M_PI));
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	return (angle);
}
