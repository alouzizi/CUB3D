/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.TILE_SIZE.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 05:38:42 by alouzizi          #+#    #+#             */
/*   Updated: 2023/01/11 08:11:22 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void cast_all_rays(t_structs *g)
{
	int i;
	
	// g->ray->rays = malloc(sizeof(double) * g->ray->num_rays);
	i = 0;
	g->cast->rayangle = g->player->rotationangle - (g->cast->fov_angle / 2);
	while (i < g->cast->num_rays)
	{
		cast(i, g);
		//cast_ray(g);
		g->cast->rayangle += g->cast->fov_angle / g->cast->num_rays;
		i++;
	}
}

void cast(int id, t_structs *g)
{
	
	g->cast->rayangle = normalize_angle(g->cast->rayangle);
	//g->ray->rays[0] = g->ray->rayangle;
	double horidistance;
	double vertdistance;
	g->ray[id].facingdown = 0;
	g->ray[id].facingup = 0;
	g->ray[id].facingright = 0;
	g->ray[id].facingleft = 0;
	g->cast->wallhitx = 0;
	g->cast->wallhity = 0;
	g->cast->distance = 0;
	g->cast->xintercept = 0;
	g->cast->yintercept = 0;
	g->cast->xstep = 0;
	g->cast->ystep = 0;
	g->cast->findhorz = 0;
	g->cast->findvert = 0;

	if (g->cast->rayangle > 0 && g->cast->rayangle < M_PI)
		g->ray[id].facingdown = 1;
	else
		g->ray[id].facingup = 1;

	if (g->cast->rayangle < 0.5 * M_PI || g->cast->rayangle > 1.5 * M_PI)
		g->ray[id].facingright = 1;
	else
		g->ray[id].facingleft = 1;
	horizontale(g, id);
	verticale(g, id);
	if(g->cast->findhorz)
		horidistance = distancebetweenpoints(g, g->cast->horizwallhitx, g->cast->horizwallhity);
	else
		horidistance = INT_MAX;
	if(g->cast->findvert)	
		vertdistance = distancebetweenpoints(g, g->cast->vertwallhitx, g->cast->vertwallhity);
	else
		vertdistance = INT_MAX;
	if (horidistance < vertdistance)
	{
		g->ray[id].wallhitx = g->cast->horizwallhitx;
		g->ray[id].wallhity = g->cast->horizwallhity;
		g->ray[id].distance = horidistance;
	}
	else
	{
		g->ray[id].wallhitx = g->cast->vertwallhitx; 
		g->ray[id].wallhity = g->cast->vertwallhity;
		g->ray[id].distance = vertdistance;
	}
	projectionwall(g, id);
	//dda(g->mlx, g->player->x, g->player->y, g->ray[id].wallhitx, g->ray[id].wallhity);
}


void horizontale(t_structs *g, int id)
{

	g->cast->yintercept = floor(g->player->y / TILE_SIZE) * TILE_SIZE; 
	if (g->ray[id].facingdown)
		g->cast->yintercept += TILE_SIZE;
	g->cast->xintercept = g->player->x + (g->cast->yintercept - g->player->y) / tan(g->cast->rayangle);
	g->cast->ystep = TILE_SIZE;
	if (g->ray[id].facingup)
		g->cast->ystep *= -1;
	g->cast->xstep = TILE_SIZE / tan(g->cast->rayangle);
	if (g->ray[id].facingleft && g->cast->xstep > 0)
		g->cast->xstep *= -1;
	if (g->ray[id].facingright && g->cast->xstep < 0)
		g->cast->xstep *= -1;
	g->cast->horizwallhitx= g->cast->xintercept;
	g->cast->horizwallhity = g->cast->yintercept;
	if (g->ray[id].facingup)
		g->cast->horizwallhity--;
	while (g->cast->horizwallhitx >= 0 && g->cast->horizwallhitx <= (g->map->column * TILE_SIZE)
			&& g->cast->horizwallhity >= 0 && g->cast->horizwallhity <= (g->map->row * TILE_SIZE))
	{
		if (there_is_wall_at(g->cast->horizwallhitx, g->cast->horizwallhity, g))
		{
			g->cast->findhorz = 1;
			return;
		}
		else
		{
			g->cast->horizwallhitx+= g->cast->xstep;
			g->cast->horizwallhity += g->cast->ystep;
		}
	}
}

void	verticale(t_structs *g, int id)
{
	g->cast->xintercept = floor(g->player->x / TILE_SIZE) * TILE_SIZE; 
	if (g->ray[id].facingright)
		g->cast->xintercept += TILE_SIZE;
	g->cast->yintercept = g->player->y + (g->cast->xintercept - g->player->x ) * tan(g->cast->rayangle);
	g->cast->xstep = TILE_SIZE;
	if (g->ray[id].facingleft)
		g->cast->xstep *= -1;
	g->cast->ystep = TILE_SIZE * tan(g->cast->rayangle);
	if (g->ray[id].facingup && g->cast->ystep > 0)
		g->cast->ystep *= -1;
	if (g->ray[id].facingdown && g->cast->ystep < 0)
		g->cast->ystep *= -1;
	g->cast->vertwallhitx = g->cast->xintercept;
	g->cast->vertwallhity = g->cast->yintercept;
	if (g->ray[id].facingleft)
		g->cast->vertwallhitx--;
	while (g->cast->vertwallhitx >= 0
			&& g->cast->vertwallhity >= 0 )
	{
		if (there_is_wall_at(g->cast->vertwallhitx, g->cast->vertwallhity, g))
		{
			g->cast->findvert = 1;
			return;
		}
		else
		{
			g->cast->vertwallhitx += g->cast->xstep;
			g->cast->vertwallhity += g->cast->ystep;
			
		}
	}
}