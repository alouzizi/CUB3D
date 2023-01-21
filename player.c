/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 02:19:47 by alouzizi          #+#    #+#             */
/*   Updated: 2023/01/21 16:41:49 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	key_hook(int key, t_structs *g)
{
	if (key == 13)
		g->player->walkdirection = 1;
	if (key == 1)
		g->player->walkdirection = -1;
	if (key == 0)
		g->player->turndirection = -1;
	if (key == 2)
		g->player->turndirection = 1;
	if (key == 124)
		g->player->rotationangle += g->player->rotationspeed;
	if (key == 123)
		g->player->rotationangle -= g->player->rotationspeed;
	if (key == 13 || key == 1 || key == 0 || key == 2)
		update(g);
	return (0);
}

void	update(t_structs *g)
{
	int		step;
	double	x;
	double	y;

	step = g->player->walkdirection * g->player->movespeed;
	x = round(g->player->x + cos(g->player->rotationangle) * step);
	y = round(g->player->y + sin(g->player->rotationangle) * step);
	if (g->player->turndirection == 1)
	{
		x = round(g->player->x - sin(g->player->rotationangle) * 10);
		y = round(g->player->y + cos(g->player->rotationangle) * 10);
	}
	if (g->player->turndirection == -1)
	{
		x = round(g->player->x + sin(g->player->rotationangle) * 10);
		y = round(g->player->y - cos(g->player->rotationangle) * 10);
	}
	if (!there_is_wall_at(x, y, g))
	{
		g->player->x = x;
		g->player->y = y;
	}
	g->player->turndirection = 0;
	g->player->walkdirection = 0;
}
