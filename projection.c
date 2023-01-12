/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 05:34:04 by alouzizi          #+#    #+#             */
/*   Updated: 2023/01/12 05:59:29 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	projectionwall(t_structs *g ,int id)
{
	double	distanceprojectplane;
	double 	raydistance;
	double	wallstripheight;
	double	top;
	double	bottom;
	
	raydistance = g->ray[id].distance;
	distanceprojectplane = (WIDTH / 2) / tan(g->cast->fov_angle / 2) * 0.8;
	wallstripheight = (TILE_SIZE / raydistance) * distanceprojectplane;
	top = (HEIGHT / 2) - (wallstripheight / 2);

	bottom = wallstripheight + top;
	while(top <= bottom)
	{
		my_mlx_pixel_put(g->mlx, id, top, 0x00FF0000);
		top++;
	}

}
