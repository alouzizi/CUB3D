/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:57:14 by alouzizi          #+#    #+#             */
/*   Updated: 2023/02/05 01:47:21 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_cellin_floor(t_structs *g, int x, double top, double bottom)
{
	double	y;

	y = 0;
	while (y < top)
	{
		my_mlx_pixel_put(g->mlx, x, y, g->map->cc);
		y++;
	}
	y = bottom;
	while (y <= HEIGHT)
	{
		my_mlx_pixel_put(g->mlx, x, y, g->map->ff);
		y++;
	}
}

int	offsetx(t_structs *g)
{
	int	offsetx;

	if (g->cast->findvert)
		offsetx = (int)g->ray->wallhity % TILE_SIZE;
	else
		offsetx = (int)g->ray->wallhitx % TILE_SIZE;
	return (offsetx);
}

char	*witch_texture(t_structs *g)
{
	if (g->cast->findhorz)
	{
		if (g->ray->facingup)
			return (g->texture->addr_no);
		if (g->ray->facingdown)
			return (g->texture->addr_so);
	}
	else
	{
		if (g->ray->facingleft)
			return (g->texture->addr_we);
		if (g->ray->facingright)
			return (g->texture->addr_ea);
	}
	return (NULL);
}

void	texture(t_structs *g, int x, double y, double wallstripheight)
{
	char	*dst;
	char	*texture;
	int		offsety;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		offsety = y + (wallstripheight / 2) - (HEIGHT / 2);
		offsety *= (double)(g->texture->height / wallstripheight);
		dst = g->mlx->addr + ((int)y * g->mlx->line_len + x * g->mlx->bpp / 8);
		texture = witch_texture(g);
		*(unsigned int *)dst = *(unsigned int *)&texture[(offsety
				* g->texture->line_len) + offsetx(g) * (g->texture->bpp / 8)];
	}
}

void	projectionwall(t_structs *g, int id)
{
	double	distanceprojectplane;
	double	correctraydistance;
	double	wallstripheight;
	double	top;
	double	bottom;

	correctraydistance = g->ray->distance
		* cos(g->cast->rayangle - g->player->rotationangle);
	distanceprojectplane = (WIDTH / 2) / tan(g->cast->fov_angle / 2) * 0.8;
	wallstripheight = (TILE_SIZE / correctraydistance) * distanceprojectplane;
	top = (HEIGHT / 2) - (wallstripheight / 2);
	bottom = wallstripheight + top;
	draw_cellin_floor(g, id, top, bottom);
	while (top <= bottom)
	{
		texture(g, id, top, wallstripheight);
		top++;
	}
}
