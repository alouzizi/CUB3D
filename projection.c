/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 05:34:04 by alouzizi          #+#    #+#             */
/*   Updated: 2023/01/10 07:37:54 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	projectionwall(t_structs *g)
{
	int		id;
	double	wallstriph;
	double	distanceprojplane;

	id = 0;
	while(id < g->ray->num_rays)
	{
		distanceprojplane = (g->map->width / 2) / tan(g->ray->fov_angle / 2);
		wallstriph = (TILE_SIZE / g->ray->rays[id]) * distanceprojplane;

	}
}
