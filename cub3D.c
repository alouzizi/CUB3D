/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 04:55:13 by alouzizi          #+#    #+#             */
/*   Updated: 2023/01/18 17:21:46 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	var_init(t_structs	*g)
{
	g->player = malloc(sizeof(t_player));
	g->mlx = malloc(sizeof(t_mlx));
	g->cast = malloc(sizeof(t_cast));
	if (!g->player || !g->mlx || !g->cast)
		exit(1);
	g->map->width = WIDTH;
	g->map->height = HEIGHT;
	g->player->x = (g->map->px + 0.5)* TILE_SIZE;
	g->player->y = (g->map->py + 0.5)* TILE_SIZE;
	g->player->radius = 3;
	g->player->turndirection = 0;
	g->player->walkdirection = 0;
	g->player->rotationangle = M_PI / 2;
	g->player->movespeed = 15;
	g->player->rotationspeed = 15 * (M_PI / 180.0);
	g->cast->fov_angle = 60.0 * (M_PI / 180.0);
	g->cast->stripwidth = 1;
	g->cast->num_rays = g->map->width / g->cast->stripwidth;
	//g->cast->rays = malloc(sizeof(double) * g->cast->num_rays);
	g->ray = malloc(sizeof(t_ray) * g->cast->num_rays);
	if (!g->ray)
		exit(1);
	g->mlx->mlx = mlx_init();
	g->mlx->win = mlx_new_window(g->mlx->mlx, g->map->width, g->map->height, "SUUUU");
	g->mlx->img = mlx_new_image(g->mlx->mlx, g->map->width, g->map->height);
	g->mlx->addr = mlx_get_data_addr(g->mlx->img, &g->mlx->bits_per_pixel, &g->mlx->line_length,
					&g->mlx->endian);
}

int	render(t_structs *g)
{
	//mlx_clear_window(g->mlx->mlx, g->mlx->win);
	g->mlx->img = mlx_new_image(g->mlx->mlx, g->map->width, g->map->height);
	g->mlx->addr = mlx_get_data_addr(g->mlx->img, &g->mlx->bits_per_pixel, &g->mlx->line_length,
					&g->mlx->endian);
	//draw_map(g);
	//draw_player(g);
	
	//puts("helllo");
	cast_all_rays(g);
	//projectionwall(g);
	mlx_put_image_to_window(g->mlx->mlx, g->mlx->win, g->mlx->img, 0, 0);
	
	mlx_destroy_image(g->mlx->mlx, g->mlx->img);
	return (0);
}

void	texture_init(t_structs *g)
{
	g->texture = malloc(sizeof(t_texture));
	if (!g->texture)
		exit(1);
	g->texture->img_no = mlx_xpm_file_to_image(g->mlx->mlx, "W3d_bluewall.xpm", &g->texture->bits_per_pixel, &g->texture->line_length);
	// g->texture->img_so = mlx_xpm_file_to_image(g->mlx->mlx, g->map->so, NULL, NULL);
	// g->texture->img_we = mlx_xpm_file_to_image(g->mlx->mlx, g->map->we, NULL, NULL);
	// g->texture->img_ea = mlx_xpm_file_to_image(g->mlx->mlx, g->map->ea, NULL, NULL);
	g->texture->addr_no = mlx_get_data_addr(g->texture->img_no, &g->texture->bits_per_pixel, &g->texture->line_length,
					&g->texture->endian);
	// g->texture->addr_so = mlx_get_data_addr(g->texture->img_so, &g->texture->bits_per_pixel, &g->texture->line_length,
					// &g->texture->endian);
	// g->texture->addr_we = mlx_get_data_addr(g->texture->img_we, &g->texture->bits_per_pixel, &g->texture->line_length,
					// &g->texture->endian);
	// g->texture->addr_ea = mlx_get_data_addr(g->texture->img_ea, &g->texture->bits_per_pixel, &g->texture->line_length,
					// &g->texture->endian);
}
int main(int ac, char **av)
{
	t_structs	game;
	if (ac == 2)
	{
		if (!check_map(av[1], &game))
			return (1);
		var_init(&game);
		texture_init(&game);
		render(&game);
		mlx_hook(game.mlx->win, 2, 0, key_hook, &game);
		mlx_key_hook(game.mlx->win, key_hook, &game);
		mlx_loop_hook(game.mlx->mlx, render, &game);
		mlx_loop(game.mlx->mlx);	
	}
	else
		printf("Error\nToo many arguments\n");
}