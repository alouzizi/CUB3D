/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 04:06:01 by alouzizi          #+#    #+#             */
/*   Updated: 2023/02/05 06:31:36 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	if ((x >= 0 && x <= WIDTH) && (y >= 0 && y <= HEIGHT))
	{
		dst = mlx->addr + (y * mlx->line_len + x * (mlx->bpp / 8));
			*(unsigned int *)dst = color;
	}
}

void	cast_init(t_structs *g)
{
	g->cast->rayangle = normalize_angle(g->cast->rayangle);
	g->ray->facingdown = 0;
	g->ray->facingup = 0;
	g->ray->facingright = 0;
	g->ray->facingleft = 0;
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
		g->ray->facingdown = 1;
	else
		g->ray->facingup = 1;
	if (g->cast->rayangle < 0.5 * M_PI || g->cast->rayangle > 1.5 * M_PI)
		g->ray->facingright = 1;
	else
		g->ray->facingleft = 1;
}

void	while_wall(t_structs *g, float wallhitx, float wallhity, int i)
{
	while (1)
	{
		if (there_is_wall_at(wallhitx, wallhity, g))
		{
			if (i == 1)
			{
				g->cast->findhorz = 1;
				g->cast->horizwallhitx = wallhitx;
				g->cast->horizwallhity = wallhity;
			}
			else
			{
				g->cast->findvert = 1;
				g->cast->vertwallhitx = wallhitx;
				g->cast->vertwallhity = wallhity;
			}
			return ;
		}
		else
		{
			wallhitx += g->cast->xstep;
			wallhity += g->cast->ystep;
		}
	}
}

float	get_angle(char c)
{
	if (c == 'W')
		return (M_PI);
	else if (c == 'E')
		return (0);
	else if (c == 'N')
		return ((3 * M_PI) / 2);
	else if (c == 'S')
		return (M_PI / 2);
	return (0);
}

int	ft_exit(void)
{
	exit(0);
	return (0);
}
