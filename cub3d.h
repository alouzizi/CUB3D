#ifndef CUB3D_H
#define CUB3D_H

#include "mlx.h"
#include <stdio.h>
#include <math.h>
#include <unistd.h>
int abs(int n) { return ((n > 0) ? n : (n * (-1))); }
int mape[12][20] =
{
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1 },
    { 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
};

typedef struct mlx
{
    void *mlx;
    void *win;
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;

}t_mlx;

typedef struct player
{
    double  x;
    double  y;
    double  radius;
    int     turndirection;
    int     walkdirection;
    double  rotationangle;
    double  movespeed;
    double  rotationspeed;
    t_mlx   mlx;
}t_player;


typedef struct map
{
    double  x;
    double  y;
    int     width;
    int     height;
    int     color;
    int     row;
    int     column;
    int		maap[12][20];
	char    *no;
	char    *so;
	char    *we;
	char    *ea;
}t_map;

void	initial_values(t_mlx *mlx, t_player *player, t_map *map);
void	render_map(t_map *map, t_player *player, t_mlx *mlx);
void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
void	draw_wall(int x, int y, t_mlx *mlx, int color);
void	dda(t_mlx *mlx,int X0, int Y0, int X1, int Y1);
void	render_player(t_player *player, t_mlx *mlx, int color);

#endif