#ifndef CUB3D_H
#define CUB3D_H

#include "mlx.h"
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>

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

typedef struct structs
{
    t_mlx		*mlx;
    t_map		*map;
    t_player	*player;
}t_structs;

void    var_init(t_structs	*g);
int     render(t_structs *g);
void    draw_map(t_structs *g);
void	draw_player(t_structs *g);
void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
void    draw_wall(t_structs *g, int x, int y, int color);
void    dda(t_mlx *mlx,int X0, int Y0, int X1, int Y1);
int     key_hook(int key, t_structs *g);
void    update(t_structs *g, int j);
#endif