/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 04:55:13 by alouzizi          #+#    #+#             */
/*   Updated: 2023/01/23 17:23:25 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	var_init(t_structs	*g)
{
	g->player = malloc(sizeof(t_player));
	g->mlx = malloc(sizeof(t_mlx));
	g->cast = malloc(sizeof(t_cast));
	g->ray = malloc(sizeof(t_ray));
	if (!g->player || !g->mlx || !g->cast || !g->ray)
		exit(1);
	g->player->x = (g->map->px + 0.5) * TILE_SIZE;
	g->player->y = (g->map->py + 0.5) * TILE_SIZE;
	g->player->radius = 3;
	g->player->turndirection = 0;
	g->player->walkdirection = 0;
	g->player->rotationangle = get_angle(g->map->map[(int)g->map->py]
		[(int)g->map->px]);
	g->player->movespeed = 15;
	g->player->rotationspeed = 15 * (M_PI / 180.0);
	g->cast->fov_angle = 60.0 * (M_PI / 180.0);
	g->cast->stripwidth = 1;
	g->cast->num_rays = WIDTH / g->cast->stripwidth;
	g->mlx->mlx = mlx_init();
	g->mlx->win = mlx_new_window(g->mlx->mlx, WIDTH,
			HEIGHT, "SUPER CUB3D");
	g->mlx->img = mlx_new_image(g->mlx->mlx, WIDTH, HEIGHT);
	g->mlx->addr = mlx_get_data_addr(g->mlx->img, &g->mlx->bpp,
			&g->mlx->line_len, &g->mlx->endian);
}

int	render(t_structs *g)
{
	g->mlx->img = mlx_new_image(g->mlx->mlx, WIDTH, HEIGHT);
	g->mlx->addr = mlx_get_data_addr(g->mlx->img, &g->mlx->bpp,
			&g->mlx->line_len, &g->mlx->endian);
	cast_all_rays(g);
	mlx_put_image_to_window(g->mlx->mlx, g->mlx->win, g->mlx->img, 0, 0);
	mlx_destroy_image(g->mlx->mlx, g->mlx->img);
	return (0);
}

void	texture_init(t_structs *g)
{
	g->texture = malloc(sizeof(t_texture));
	if (!g->texture)
		exit(1);
	g->texture->img_no = mlx_xpm_file_to_image(g->mlx->mlx, g->map->no,
			&g->texture->width, &g->texture->height);
	g->texture->img_so = mlx_xpm_file_to_image(g->mlx->mlx, g->map->so,
			&g->texture->width, &g->texture->height);
	g->texture->img_we = mlx_xpm_file_to_image(g->mlx->mlx, g->map->we,
			&g->texture->width, &g->texture->height);
	g->texture->img_ea = mlx_xpm_file_to_image(g->mlx->mlx, g->map->ea,
			&g->texture->width, &g->texture->height);
	if (!g->texture->img_no || !g->texture->img_so || !g->texture->img_we
		|| !g->texture->img_ea)
	{
		perror("Error");
		exit(1);
	}
	g->texture->addr_no = mlx_get_data_addr(g->texture->img_no,
			&g->texture->bpp, &g->texture->line_len, &g->texture->endian);
	g->texture->addr_so = mlx_get_data_addr(g->texture->img_so,
			&g->texture->bpp, &g->texture->line_len, &g->texture->endian);
	g->texture->addr_we = mlx_get_data_addr(g->texture->img_we,
			&g->texture->bpp, &g->texture->line_len, &g->texture->endian);
	g->texture->addr_ea = mlx_get_data_addr(g->texture->img_ea,
			&g->texture->bpp, &g->texture->line_len, &g->texture->endian);
}

void	get_color_cf(t_structs *g)
{
	g->texture->color_c = convert_rgb_to_dec(g->map->c[0],
			g->map->c[1], g->map->c[2], 0);
	g->texture->color_f = convert_rgb_to_dec(g->map->f[0],
			g->map->f[1], g->map->f[2], 0);
}

int	main(int ac, char **av)
{
	t_structs	game;

	if (ac == 2)
	{
		if (!check_map(av[1], &game))
			return (1);
		var_init(&game);
		texture_init(&game);
		get_color_cf(&game);
		render(&game);
		mlx_hook(game.mlx->win, 2, 0, key_hook, &game);
		mlx_key_hook(game.mlx->win, key_hook, &game);
		mlx_loop_hook(game.mlx->mlx, render, &game);
		mlx_loop(game.mlx->mlx);
	}
	else
		ft_putstr_fd("Error\nToo many arguments\n", 2);
}
