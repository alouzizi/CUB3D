/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 04:06:01 by alouzizi          #+#    #+#             */
/*   Updated: 2023/01/20 13:24:21 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int abs(int n) { return ((n > 0) ? n : (n * (-1))); }

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;
	if ((x >= 0 && x <= WIDTH) && (y >= 0 && y <= HEIGHT))
	{
	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
	}
}

void    dda(t_mlx *mlx,int X0, int Y0, int X1, int Y1)
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
		my_mlx_pixel_put(mlx,round(X), round(Y), 0x0000FF); // put pixel at (X,Y)
        //mlx_pixel_put(mlx->mlx, mlx->win,round(X), round(Y),0x000000); // put pixel at (X,Y)
        X += Xinc; // increment in x at each step
        Y += Yinc; // increment in y at each step
    }
}

int	key_hook(int key, t_structs *g)
{
	if (key == 13)
		g->player->walkdirection = 1;
	if (key == 1)
		g->player->walkdirection = -1;
	if (key == 0)
		g->player->turndirection = -1;
	if (key == 2)
		g->player->turndirection = 1;
	if (key == 124)
		g->player->rotationangle += g->player->rotationspeed;
	if (key == 123)
		g->player->rotationangle -= g->player->rotationspeed;
	if (key == 13 || key == 1 || key == 0 || key == 2)
		update(g);
	return (0);
}

void	update(t_structs *g)
{
	int	step;
	double	x;
	double	y;

	step = g->player->walkdirection * g->player->movespeed;
	x = round(g->player->x + cos(g->player->rotationangle) * step);
	y = round(g->player->y + sin(g->player->rotationangle) * step);
	//step = g->player->turndirection * g->player->movespeed;
	if (g->player->turndirection == 1)
	{
		x = round(g->player->x - sin(g->player->rotationangle) * 10);
		y = round(g->player->y + cos(g->player->rotationangle) * 10);
	}
	if (g->player->turndirection == -1)
	{
		x = round(g->player->x + sin(g->player->rotationangle) * 10);
		y = round(g->player->y - cos(g->player->rotationangle) * 10);
	}
	if (!there(x, y, g)  )
	{
		g->player->x = x;
		g->player->y = y;
	}
	g->player->turndirection = 0;
	g->player->walkdirection = 0;
}
