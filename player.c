/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 02:19:47 by alouzizi          #+#    #+#             */
/*   Updated: 2023/01/08 11:04:46 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player(t_structs *g)
{
	int x;
	int y;
	int x1;
	int y1;

	y = x = 0;
	while (y < 10)
	{
		while (x < 10)
		{
			my_mlx_pixel_put(g->mlx, g->player->x + x, g->player->y + y, 0x00FF00);
			x++;
		}
		x = 0;
		y++;
	}
	g->player->rotationangle += g->player->turndirection * g->player->rotationspeed;
	//x1 = g->player->x + cos(g->player->rotationangle) * 30;
	//y1 = g->player->y + sin(g->player->rotationangle) * 30;
	//dda(g->mlx, g->player->x, g->player->y, x1, y1);
}

int	there_is_wall_at(double x, double y, t_structs *g)
{
	int mapgridindexx;
	int mapgridindexy;

	if (x < 0 || x > g->map->width || y < 0 || y > g->map->height)
		return (1);
	mapgridindexx = x / 42;
	mapgridindexy = y / 42;
	if (mape[mapgridindexy][mapgridindexx] == 0)
		return (0);
	else
		return (1);
}

void cast_all_rays(t_structs *g)
{
	double rayangle;
	int i;

	i = 0;
	rayangle = g->player->rotationangle - (g->ray->fov_angle / 2);
	while (i < g->ray->num_rays)
	{
		cast_ray(rayangle, g);
		rayangle += g->ray->fov_angle / g->ray->num_rays;
		i++;
	}
}
void	cast_ray(double rayangle, t_structs *g)
{
	int	x1;
	int	y1;

	rayangle = normalize_angle(rayangle);

	x1 = g->player->x + cos(rayangle) * 30;
	y1 = g->player->y + sin(rayangle) * 30;
	dda(g->mlx, g->player->x, g->player->y, x1, y1);
}

double normalize_angle(double angle)
{
	angle = remainder(angle, (2 * M_PI));
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	return (angle);
}
