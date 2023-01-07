/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3:D.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 04:55:13 by alouzizi          #+#    #+#             */
/*   Updated: 2023/01/07 08:52:28 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void initial_values(t_mlx *mlx, t_player *player, t_map *map)
{
	mlx->bits_per_pixel = 0;
	mlx->line_length = 0;
	mlx->endian = 0;
	map->row = 12;
	map->column = 20;
	//map->maap = mape;
	map->width = map->column * 42;
	map->height = map->row * 42;
	player->x = map->width / 2;
	player->y = map->height /2;
	player->radius = 3;
	player->turndirection = 0;
	player->walkdirection = 0;
	player->rotationangle = M_PI / 2;
	player->movespeed = 15;
	player->rotationspeed = 15 * (M_PI / 180);
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, map->width, map->height, "SUUUU");
	mlx->img = mlx_new_image(mlx->mlx, 1920, 1080);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length,
								&mlx->endian);
}

int main(int ac, char **av)
{
	t_mlx		mlx;
	t_map		map;
	t_player	player;

	initial_values(&mlx, &player, &map);
	render_map(&map, &player, &mlx);
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
	mlx_loop(mlx.mlx);
}
void render_map(t_map *map, t_player *player, t_mlx *mlx)
{
	int i;
	int j;
	int width;
	int height;

	i = 0;
	j = 0;
	mlx_clear_window(mlx->mlx, mlx->win);
	while(i < map->row)
	{
		while(j < map->column)
		{
			if(mape[i][j] == 1)
				draw_wall(j * 42, i * 42, mlx, 0xFFFFFF);
			else
				draw_wall(j * 42, i * 42, mlx, 0x00FF0000);
			j++;
		}
		j = 0;
		i++;
	}
	render_player(player, mlx, 0x00FF00);
	//mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}
void	render_player(t_player *player, t_mlx *mlx, int color)
{
	int i;
	int j;
	double x1;
	double y1;

	i = 0;
	j = 0;
	while(i < 10)
	{
		while(j < 10)
		{
			if (i == 0)
				my_mlx_pixel_put(mlx, player->x + i, player->y + j, color);
			j++;
		}
		j = 0;
		i++;
	}
	player->rotationangle =+ player->turndirection * player->rotationspeed;
	x1 = player->x + cos(player->rotationangle) * 30;
	y1 = player->y + sin(player->rotationangle) * 30;
	dda(mlx, player->x,player->y,x1,y1);
}

void dda(t_mlx *mlx,int X0, int Y0, int X1, int Y1)
{
    // calculate dx & dy 
    int dx = X1 - X0;
    int dy = Y1 - Y0;
 
    // calculate steps required for generating pixels
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
 
    // calculate increment in x & y for each steps
    float Xinc = dx / (float)steps;
    float Yinc = dy / (float)steps;
 
    // Put pixel for each step
    float X = X0;
    float Y = Y0;
    for (int i = 0; i <= steps; i++) {
		my_mlx_pixel_put(mlx,round(X), round(Y), 0x000000); // put pixel at (X,Y)
        //mlx_pixel_put(mlx->mlx, mlx->win,round(X), round(Y),0x000000); // put pixel at (X,Y)
        X += Xinc; // increment in x at each step
        Y += Yinc; // increment in y at each step
    }
}

void	draw_wall(int x, int y, t_mlx *mlx, int color)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(i < 42)
	{
		my_mlx_pixel_put(mlx, x + i, y + j, 0x0000FF);
		while(j < 42)
		{
			if (i == 0)
				my_mlx_pixel_put(mlx, x + i, y + j, 0X000000);
			else
				my_mlx_pixel_put(mlx, x + i, y + j, color);
			j++;
		}
		my_mlx_pixel_put(mlx, x + i, y + j, 0X000000);
		j = 0;
		my_mlx_pixel_put(mlx, x + i, y + j, 0x000000);
		i++;
	}
}

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}