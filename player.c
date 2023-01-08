/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 02:19:47 by alouzizi          #+#    #+#             */
/*   Updated: 2023/01/08 04:20:44 by alouzizi         ###   ########.fr       */
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
	x1 = g->player->x + cos(g->player->rotationangle) * 30;
	y1 = g->player->y + sin(g->player->rotationangle) * 30;
	dda(g->mlx, g->player->x, g->player->y, x1, y1);
}