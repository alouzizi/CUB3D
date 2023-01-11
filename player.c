/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 02:19:47 by alouzizi          #+#    #+#             */
/*   Updated: 2023/01/11 01:56:54 by alouzizi         ###   ########.fr       */
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
	if (g->map->map[mapgridindexy][mapgridindexx] == '0' || g->map->map[mapgridindexy][mapgridindexx] == 'W')
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
	while (i < g->ray->num_rays)
	{
		cast(i, g);
		//cast_ray(g);
		g->ray->rayangle += g->ray->fov_angle / g->ray->num_rays;
		i++;
	}
}

void cast(int id, t_structs *g)
{
	
	g->ray->rayangle = normalize_angle(g->ray->rayangle);
	g->ray->rays[0] = g->ray->rayangle;
	double horidistance;
	double vertdistance;
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
	g->ray->findhorz = 0;
	g->ray->findvert = 0;

	if (g->ray->rays[0] > 0 && g->ray->rays[0] < M_PI)
		g->ray->facingdown = 1;
	else
		g->ray->facingup = 1;

	if (g->ray->rays[0] < 0.5 * M_PI || g->ray->rays[0] > 1.5 * M_PI)
		g->ray->facingright = 1;
	else
		g->ray->facingleft = 1;
	horizontale(g);
	verticale(g);
	if(g->ray->findhorz)
		horidistance = distancebetweenpoints(g, g->ray->horizwallhitx, g->ray->horizwallhity);
	else
		horidistance = INT_MAX;
	if(g->ray->findvert)	
		vertdistance = distancebetweenpoints(g, g->ray->vertwallhitx, g->ray->vertwallhity);
	else
		vertdistance = INT_MAX;
	if (horidistance < vertdistance)
	{
		g->cast[id].wallhitx = g->ray->horizwallhitx;
		g->cast[id].wallhity = g->ray->horizwallhity;
	}
	else
	{
		g->cast[id].wallhitx = g->ray->vertwallhitx; 
		g->cast[id].wallhity = g->ray->vertwallhity;
	}
	dda(g->mlx, g->player->x, g->player->y, g->cast[id].wallhitx, g->cast[id].wallhity);
}

double distancebetweenpoints(t_structs *g , double x, double y)
{
	return (sqrt(pow(x - g->player->x, 2) + pow(y - g->player->y, 2)));
}

void horizontale(t_structs *g)
{

	g->ray->yintercept = floor(g->player->y / 42) * 42; 
	if (g->ray->facingdown)
		g->ray->yintercept += 42;
	g->ray->xintercept = g->player->x + (g->ray->yintercept - g->player->y) / tan(g->ray->rays[0]);
	g->ray->ystep = 42;
	if (g->ray->facingup)
		g->ray->ystep *= -1;
	g->ray->xstep = 42 / tan(g->ray->rays[0]);
	if (g->ray->facingleft && g->ray->xstep > 0)
		g->ray->xstep *= -1;
	if (g->ray->facingright && g->ray->xstep < 0)
		g->ray->xstep *= -1;
	g->ray->horizwallhitx= g->ray->xintercept;
	g->ray->horizwallhity = g->ray->yintercept;
	if (g->ray->facingup)
		g->ray->horizwallhity--;
	while (g->ray->horizwallhitx>= 0 && g->ray->horizwallhitx<= g->map->width 
			&& g->ray->horizwallhity >= 0 && g->ray->horizwallhity <= g->map->height)
	{
		if (there_is_wall_at(g->ray->horizwallhitx, g->ray->horizwallhity, g))
		{
			g->ray->findhorz = 1;
			return;
		}
		else
		{
			g->ray->horizwallhitx+= g->ray->xstep;
			g->ray->horizwallhity += g->ray->ystep;
		}
	}
}

void	verticale(t_structs *g)
{

	g->ray->xintercept = floor(g->player->x / 42) * 42; 
	if (g->ray->facingright)
		g->ray->xintercept += 42;
	g->ray->yintercept = g->player->y + (g->ray->xintercept - g->player->x ) * tan(g->ray->rays[0]);
	g->ray->xstep = 42;
	if (g->ray->facingleft)
		g->ray->xstep *= -1;
	g->ray->ystep = 42 * tan(g->ray->rays[0]);
	if (g->ray->facingup && g->ray->ystep > 0)
		g->ray->ystep *= -1;
	if (g->ray->facingdown && g->ray->ystep < 0)
		g->ray->ystep *= -1;
	g->ray->vertwallhitx = g->ray->xintercept;
	g->ray->vertwallhity = g->ray->yintercept;
	if (g->ray->facingleft)
		g->ray->vertwallhitx--;
	while (g->ray->vertwallhitx >= 0 && g->ray->vertwallhitx <= g->map->width 
			&& g->ray->vertwallhity >= 0 && g->ray->vertwallhity <= g->map->height)
	{
		if (there_is_wall_at(g->ray->vertwallhitx, g->ray->vertwallhity, g))
		{
			g->ray->findvert = 1;
			return;
		}
		else
		{
			g->ray->vertwallhitx += g->ray->xstep;
			g->ray->vertwallhity += g->ray->ystep;
			
		}
	}
}

double normalize_angle(double angle)
{
	angle = remainder(angle, (2 * M_PI));
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	return (angle);
}
