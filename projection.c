/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 05:34:04 by alouzizi          #+#    #+#             */
/*   Updated: 2023/01/18 09:59:15 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	projectionwall(t_structs *g ,int id)
{
	double	distanceprojectplane;
	double 	correctraydistance;
	double	wallstripheight;
	double	top;
	double	bottom;
	
	correctraydistance = g->ray[id].distance  * cos(g->cast->rayangle - g->player->rotationangle);
	distanceprojectplane = (WIDTH / 2) / tan(g->cast->fov_angle / 2) * 0.8;
	wallstripheight = (TILE_SIZE / correctraydistance) * distanceprojectplane;
	top = (HEIGHT / 2) - (wallstripheight / 2);
	bottom = wallstripheight + top;
	while(top <= bottom)
	{
		my_mlx_pixel_put(g->mlx, id, top, 0x00FF0000);
		top++;  
	}

}
