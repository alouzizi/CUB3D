#ifndef TEST_H
#define TEST_H

#include "mlx.h"
#include <stdio.h>
#include <math.h>
#include <unistd.h>
int abs(int n) { return ((n > 0) ? n : (n * (-1))); }
int map[12][20] =
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

}t_mlx;


typedef struct player
{
    double  x;
    double  y;
    double radius;
    int turndirection;
    int walkdirection;
    double rotationangle;
    double  movespeed;
    double  rotationspeed;
    t_mlx    mlx;
}t_player;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
    t_mlx    mlx;
    t_player player;
}				t_data;

int key_hook(int key, t_player *player);
int update_player(t_player *player);
void dda(t_data *data,int X0, int Y0, int X1, int Y1);
// void dda(t_mlx *mlx,int X0, int Y0, int X1, int Y1);
int relased(int key, t_player *player);
void draw_wall(int x, int y, int width, int height, t_data *img, int color);
int loop_hook(t_data *img, int x, int y);
void draw_player(int x, int y , int width, int height, t_data *img, int color);
#endif