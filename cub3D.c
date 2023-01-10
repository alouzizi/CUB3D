/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 04:55:13 by alouzizi          #+#    #+#             */
/*   Updated: 2023/01/10 04:43:18 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	var_init(t_structs	*g)
{
	g->map = malloc(sizeof(t_map));
	g->player = malloc(sizeof(t_player));
	g->mlx = malloc(sizeof(t_mlx));
	g->ray = malloc(sizeof(t_ray));
	if (!g->map || !g->player || !g->mlx || !g->ray)
		exit(1);
	g->map->row = 12;
	g->map->column = 20;
	g->map->width = g->map->column * 42;
	g->map->height = g->map->row * 42;
	g->player->x = g->map->width /2;
	g->player->y = g->map->height /2;
	g->player->radius = 3;
	g->player->turndirection = 0;
	g->player->walkdirection = 0;
	g->player->rotationangle = M_PI / 2;
	g->player->movespeed = 15;
	g->player->rotationspeed = 15 * (M_PI / 180.0);
	g->ray->fov_angle = 60.0 * (M_PI / 180.0);
	g->ray->stripwidth = 1;
	g->ray->rays = malloc(sizeof(double) * g->ray->num_rays);
	g->ray->num_rays = g->map->width / g->ray->stripwidth;
	g->mlx->mlx = mlx_init();
	g->mlx->win = mlx_new_window(g->mlx->mlx, g->map->width, g->map->height, "SUUUU");
	g->mlx->img = mlx_new_image(g->mlx->mlx, g->map->width, g->map->height);
	g->mlx->addr = mlx_get_data_addr(g->mlx->img, &g->mlx->bits_per_pixel, &g->mlx->line_length,
					&g->mlx->endian);
}

int	render(t_structs *g)
{
	mlx_clear_window(g->mlx->mlx, g->mlx->win);
	draw_map(g);
	draw_player(g);
	cast_all_rays(g);
	mlx_put_image_to_window(g->mlx->mlx, g->mlx->win, g->mlx->img, 0, 0);
	return (0);
}

int main(int ac, char **av)
{
	t_structs	game;
	var_init(&game);
	render(&game);
	mlx_key_hook(game.mlx->win, key_hook, &game);
	mlx_loop_hook(game.mlx->mlx, render, &game);
	mlx_loop(game.mlx->mlx);
}