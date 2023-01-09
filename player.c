/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 02:19:47 by alouzizi          #+#    #+#             */
/*   Updated: 2023/01/09 09:32:27 by alouzizi         ###   ########.fr       */
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
	x1 = g->player->x + cos(g->player->rotationangle) * 42;
	y1 = g->player->y + sin(g->player->rotationangle) * 42;
	dda(g->mlx, g->player->x, g->player->y, x1, y1);
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
	//double rayangle;
	int i;
	
	// g->ray->rays = malloc(sizeof(double) * g->ray->num_rays);
	i = 0;
	g->ray->rayangle = g->player->rotationangle - (g->ray->fov_angle / 2);
	// while (i < g->ray->num_rays)
	// {
	printf("g->ray->rayangle ****%f \n ", g->ray->rayangle);
		cast(i, g);
		//cast_ray(g);
		// g->ray->rayangle += g->ray->fov_angle / g->ray->num_rays;
		// i++;
	// }
}

void cast(int id, t_structs *g)
{
	g->ray->rayangle = normalize_angle(g->ray->rayangle);
	g->ray->rays[0] = g->ray->rayangle;
	printf("rayangle = %f\n", g->ray->rays[0]);
	g->ray->facingdown = 0;
	g->ray->facingup = 0;
	g->ray->facingright = 0;
	g->ray->facingleft = 0;
	g->ray->wallhitx = 0;
	g->ray->wallhity = 0;
	g->ray->distance = 0;
	g->ray->xintercept = 0;
	g->ray->yintercept = 0;
	g->ray->xstep = 0;
	g->ray->ystep = 0;
	double x , y;

	x = y =0;
	//*************************************************************//
 
	if (g->ray->rays[0] > 0 && g->ray->rays[0] < M_PI)
		g->ray->facingdown = 1;
	else
		g->ray->facingup = 1;

	if (g->ray->rays[0] < 0.5 * M_PI || g->ray->rays[0] > 1.5 * M_PI)
		g->ray->facingright = 1;
	else
		g->ray->facingleft = 1;

	//*************************************************************//

	g->ray->yintercept = floor(g->player->y / 42) * 42; 
	if (g->ray->facingdown)
		g->ray->yintercept += 42;
	//*************************************************************//

	printf("g->ray->xintercept %f\n", g->ray->xintercept);
	printf("g->ray->yintercept %f\n", g->ray->yintercept);
	printf("g->player->x %f\n", g->player->x);
	printf("test %f\n", g->ray->yintercept - g->player->y) 
			/ tan(g->ray->rays[0]);
	g->ray->xintercept = g->player->x + (g->ray->yintercept - g->player->y) / tan(g->ray->rays[0]);

	//*************************************************************//
	
	g->ray->ystep = 42;
	if (g->ray->facingup)
		g->ray->ystep *= -1;
	//*************************************************************//

	g->ray->xstep = 42 / tan(g->ray->rays[0]);
	if (g->ray->facingleft && g->ray->xstep > 0)
		g->ray->xstep *= -1;
	if (g->ray->facingright && g->ray->xstep < 0)
		g->ray->xstep *= -1;
	//*************************************************************//
	g->ray->wallhitx = g->ray->xintercept;
	g->ray->wallhity = g->ray->yintercept;
	//*************************************************************//
	if (g->ray->facingup)
		g->ray->wallhity--;
	//*************************************************************//
	printf("g->ray->wallhitx = %f || g->ray->hit y = %f \n", g->ray->wallhitx, g->ray->wallhity);
	printf("g->map->width = %d || g->map->height = %d \n", g->map->width, g->map->height);
	while (g->ray->wallhitx >= 0 && g->ray->wallhitx <= g->map->width 
			&& g->ray->wallhity >= 0 && g->ray->wallhity <= g->map->height)
	{
		printf("hoola\n");
		printf("x = %f\n", g->ray->wallhitx);
		printf("y = %f\n", g->ray->wallhity);
		if (there_is_wall_at(g->ray->wallhitx, g->ray->wallhity, g))
		{
			x = g->ray->wallhitx;
			y = g->ray->wallhity;
			printf("***********\n");
			dda(g->mlx, g->player->x, g->player->y, x, y);
			break;
		}
		else
		{
			g->ray->wallhitx += g->ray->xstep;
			g->ray->wallhity += g->ray->ystep;
			
		}
	}
	
	printf("isfacingRight? %d\n", g->ray->facingright);
	//printf("isfacingLeft? %d\n", g->ray->facingleft);
	printf("isfacingUp? %d\n", g->ray->facingup);
}


double normalize_angle(double angle)
{
	angle = remainder(angle, (2 * M_PI));
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	return (angle);
}
