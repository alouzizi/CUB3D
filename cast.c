/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 17:09:37 by alouzizi          #+#    #+#             */
/*   Updated: 2023/01/23 20:31:51 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cast_all_rays(t_structs *g)
{
	int	i;

	i = 0;
	g->cast->rayangle = g->player->rotationangle - (g->cast->fov_angle / 2);
	while (i < g->cast->num_rays)
	{
		cast(i, g);
		g->cast->rayangle += g->cast->fov_angle / g->cast->num_rays;
		i++;
	}
}

void	get_distance(t_structs *g, float horidistance, float vertdistance)
{
	if (horidistance < vertdistance)
	{
		g->cast->findhorz = 1;
		g->cast->findvert = 0;
		g->ray->wallhitx = g->cast->horizwallhitx;
		g->ray->wallhity = g->cast->horizwallhity;
		g->ray->distance = horidistance;
	}
	else
	{
		g->cast->findvert = 1;
		g->cast->findhorz = 0;
		g->ray->wallhitx = g->cast->vertwallhitx;
		g->ray->wallhity = g->cast->vertwallhity;
		g->ray->distance = vertdistance;
	}
}

void	cast(int id, t_structs *g)
{
	float	horidistance;
	float	vertdistance;

	cast_init(g);
	horizontale(g);
	verticale(g);
	if (g->cast->findhorz)
		horidistance = distancebetweenpoints(g, g->cast->horizwallhitx,
				g->cast->horizwallhity);
	else
		horidistance = INT_MAX;
	if (g->cast->findvert)
		vertdistance = distancebetweenpoints(g, g->cast->vertwallhitx,
				g->cast->vertwallhity);
	else
		vertdistance = INT_MAX;
	get_distance(g, horidistance, vertdistance);
	projectionwall(g, id);
}

void	horizontale(t_structs *g)
{
	g->cast->yintercept = floor(g->player->y / TILE_SIZE) * TILE_SIZE;
	if (g->ray->facingdown)
		g->cast->yintercept += TILE_SIZE;
	g->cast->xintercept = g->player->x
		+ (g->cast->yintercept - g->player->y) / tan(g->cast->rayangle);
	g->cast->ystep = TILE_SIZE;
	if (g->ray->facingup)
		g->cast->ystep *= -1;
	g->cast->xstep = TILE_SIZE / tan(g->cast->rayangle);
	if (g->ray->facingleft && g->cast->xstep > 0)
		g->cast->xstep *= -1;
	if (g->ray->facingright && g->cast->xstep < 0)
		g->cast->xstep *= -1;
	g->cast->horizwallhitx = g->cast->xintercept;
	g->cast->horizwallhity = g->cast->yintercept;
	if (g->ray->facingup)
		g->cast->horizwallhity -= 0.001;
	while_wall(g, g->cast->horizwallhitx, g->cast->horizwallhity, 1);
}

void	verticale(t_structs *g)
{
	g->cast->xintercept = floor(g->player->x / TILE_SIZE) * TILE_SIZE;
	if (g->ray->facingright)
		g->cast->xintercept += TILE_SIZE;
	g->cast->yintercept = g->player->y
		+ (g->cast->xintercept - g->player->x) * tan(g->cast->rayangle);
	g->cast->xstep = TILE_SIZE;
	if (g->ray->facingleft)
		g->cast->xstep *= -1;
	g->cast->ystep = TILE_SIZE * tan(g->cast->rayangle);
	if (g->ray->facingup && g->cast->ystep > 0)
		g->cast->ystep *= -1;
	if (g->ray->facingdown && g->cast->ystep < 0)
		g->cast->ystep *= -1;
	g->cast->vertwallhitx = g->cast->xintercept;
	g->cast->vertwallhity = g->cast->yintercept;
	if (g->ray->facingleft)
		g->cast->vertwallhitx -= 0.01;
	while_wall(g, g->cast->vertwallhitx, g->cast->vertwallhity, 0);
}
