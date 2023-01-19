/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 02:05:40 by alouzizi          #+#    #+#             */
/*   Updated: 2023/01/19 16:52:22 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "mlx.h"
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <fcntl.h>
#include "libft/libft.h"
#define PI 3.1415926535
#define MINIMAP 0.2
#define TILE_SIZE 64
#define WALL_STRIP_WIDTH 1
# define NO 1
# define SO 2
# define WE 3
# define EA 4
# define F 5
# define C 6
#define WIDTH 1008
#define HEIGHT 462

static int mape[12][20] ={
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

typedef struct texture
{
    void *img_so;
    void *img_no;
    void *img_we;
    void *img_ea;
    char *addr_so;
    char *addr_no;
    char *addr_we;
    char *addr_ea;
    int bits_per_pixel;
    int line_length;
    int endian;
    int width;
    int height;
}t_texture;

typedef struct player
{
    float  x;
    float  y;
    float  radius;
    int     turndirection;
    int     walkdirection;
    float  rotationangle;
    float  movespeed;
    float  rotationspeed;
    t_mlx   mlx;
}t_player;

typedef struct map
{
    float  px;
    float  py;
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
	int		f[3];
	int		c[3];
    char	**map;
    char	**o_map;
}t_map;

typedef struct cast
{
	int		num_rays;
	float	rayangle;
	int		stripwidth; 
	float	fov_angle;
	float	wallhitx;
	float	wallhity;
	float	distance;
	float  xintercept;
	float  yintercept;
	float  xstep;
	float  ystep;
	float	horizwallhitx;
	float	horizwallhity;
	float	vertwallhitx;
	float	vertwallhity;
	int		findhorz;
	int		findvert;
	float *rays;
}t_cast;

typedef struct ray
{
	float	wallhitx;//
	float	wallhity;//
	float	distance;//
    int     facingup;//
    int     facingleft;//
    int     facingdown;//
    int     facingright;//
}t_ray;



typedef struct structs
{
    t_mlx		*mlx;
    t_map		*map;
    t_player	*player;
	t_ray		*ray;
    t_cast		*cast;
    t_texture	*texture;
}t_structs;

void	var_init(t_structs	*g);
int		render(t_structs *g);
void	draw_map(t_structs *g);
void	draw_player(t_structs *g);
void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
void	draw_wall(t_structs *g, int x, int y, int color);
void	dda(t_mlx *mlx,int X0, int Y0, int X1, int Y1);
int		key_hook(int key, t_structs *g);
void	update(t_structs *g);
int		there_is_wall_at(float x, float y, t_structs *g);
void	cast_all_rays(t_structs *g);
void	cast_ray(t_structs *g);
float	normalize_angle(float angle);
void cast(int id, t_structs *g);
void horizontale(t_structs *g, int id);
void	verticale(t_structs *g, int id);
float distancebetweenpoints(t_structs *g , float x, float y);
void	projectionwall(t_structs *g , int id);
int	there(float x, float y, t_structs *g);
bool	get_map(char *file, t_map *map);
bool	ft_check_extention(char *str);
int	open_file(char *file);
bool	is_empty(char **line, int i);


bool	parsing_assets(t_map *map);
bool	assets_check(t_map *map);
int	tab_len(char **s);
bool	if_valid(int *tab);
bool	range_check(int num);


bool	check_p_map(t_map *map);
void	init_data(t_map *map);
char	*str_proc(char *str, int width);
int	get_strlen(char *s);
char	*trim_n(char *str);


bool	init_map(t_map *map);


bool	check_map(char *str, t_structs *g);
bool	check_sides(char **player_map, int i, int j);
int	get_type(char *type);
bool	check_commas(char **str, int index);


bool	find_texture(t_map *map, int type, int index);
bool	if_xpm(char *str);
bool	find_colors(t_map *map, int type, int index);
bool	get_color(t_map *map, int index, char flag);

bool	if_map_valid(t_map	*map);
bool	check_elem(int *player_count, t_map *map, int i, int j);
bool	if_player(char c);


void	free_tab(char ***tab);
int	max_width(char **s);
char	*cut(char *str, char **dist);

char	*get_next_line(int fd);
#endif