/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 05:34:04 by alouzizi          #+#    #+#             */
/*   Updated: 2023/01/18 19:14:00 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_cellin_floor(t_structs *g, int x, double top, double bottom)
{
	double	y;

	y = 0;
	while(y < top)
	{
		my_mlx_pixel_put(g->mlx, x, y, 0x4287f5);
		y++;  
	}
	y = bottom;
	while(y <= HEIGHT)
	{
		my_mlx_pixel_put(g->mlx, x, y, 0xf58742);
		y++;  
	}
}

int	offsetx(t_structs *g, int id)
{
	int	offsetx;

	if (g->cast->findvert)
		offsetx = (int) g->ray[id].wallhity % TILE_SIZE;
	else
		offsetx = (int) g->ray[id].wallhitx % TILE_SIZE;
	return (offsetx);
}

void	projectionwall(t_structs *g ,int id)
{
	double	distanceprojectplane;
	double 	correctraydistance;
	double	wallstripheight;
	double	top;
	double	bottom;
	char	*dst;
	int 	offsety;
	double	y;

	correctraydistance = g->ray[id].distance  * cos(g->cast->rayangle - g->player->rotationangle);
	distanceprojectplane = (WIDTH / 2) / tan(g->cast->fov_angle / 2) * 0.8;
	wallstripheight = (TILE_SIZE / correctraydistance) * distanceprojectplane;
	y = top = (HEIGHT / 2) - (wallstripheight / 2);
	bottom = wallstripheight + top;
	draw_cellin_floor(g, id, top, bottom);;
	while(top <= bottom) 
	{
		if (id >= 0 && id < WIDTH && top >= 0 && top < HEIGHT)
		{
			offsety = top + (wallstripheight / 2) - (HEIGHT / 2);
			offsety *= (g->texture->height / wallstripheight);
			//printf("offsety = %d , offsetx = %d\n", offsety, offsetx(g,id));
			dst = g->mlx->addr + ((int)top * g->mlx->line_length + id * (g->mlx->bits_per_pixel / 8));
			*(unsigned int*)dst = *(unsigned int*)&g->texture->addr_no[(offsety
				* g->texture->line_length + offsetx(g,id) * (g->texture->bits_per_pixel / 8))];
		}
		top++;  
	}
}

	