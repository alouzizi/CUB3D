/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alouzizi <alouzizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 02:05:40 by alouzizi          #+#    #+#             */
/*   Updated: 2023/02/05 06:24:56 by alouzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "mlx.h"
# include <stdio.h>
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include <fcntl.h>
# include "libft/libft.h"
# define PI 3.1415926535
# define MINIMAP 0.2
# define TILE_SIZE 63
# define WALL_STRIP_WIDTH 1
# define NO 1
# define SO 2
# define WE 3
# define EA 4
# define F 5
# define C 6
# define WIDTH 1008
# define HEIGHT 462

typedef struct mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;

}t_mlx;

typedef struct texture
{
	void	*img_so;
	void	*img_no;
	void	*img_we;
	void	*img_ea;
	char	*addr_so;
	char	*addr_no;
	char	*addr_we;
	char	*addr_ea;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
	int		color_c;
	int		color_f;
}t_texture;

typedef struct player
{
	float	x;
	float	y;
	float	radius;
	int		turndirection;
	int		walkdirection;
	float	rotationangle;
	float	movespeed;
	float	rotationspeed;
	t_mlx	mlx;
}t_player;

typedef struct map
{
	float	px;
	float	py;
	int		width;
	int		height;
	int		color;
	int		row;
	int		column;
	int		maap[12][20];
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		f[3];
	int		c[3];
	char	**map;
	char	**o_map;
	int		ff;
	int		cc;
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
	float	xintercept;
	float	yintercept;
	float	xstep;
	float	ystep;
	float	horizwallhitx;
	float	horizwallhity;
	float	vertwallhitx;
	float	vertwallhity;
	int		findhorz;
	int		findvert;
	float	*rays;
}t_cast;

typedef struct ray
{
	float	wallhitx;
	float	wallhity;
	float	distance;
	int		facingup;
	int		facingleft;
	int		facingdown;
	int		facingright;
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

typedef union u_color
{
	unsigned char	rgb[4];
	int				color;
}			t_color;

//<----------------- paesing ----------------->

int		get_texture(char *line, t_map *map, int i);
void	get_data(int fd, t_map *map);
int		get_color(char *line, t_map *map, int i);
void	get_map(int fd, t_map *map, char *line);
char	*genarate(int size);
void	get_player_position(t_map *map);
int		check_file_extention(char *file);
char	*free_strjoin(char *s1, char *s2, int o);

//<----------------- mandatory ----------------->
float	get_angle(char c);
void	var_init(t_structs *g);
int		render(t_structs *g);
void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
int		key_hook(int key, t_structs *g);
void	update(t_structs *g);
int		there_is_wall_at(float x, float y, t_structs *g);
void	cast_all_rays(t_structs *g);
float	normalize_angle(float angle);
void	cast_init(t_structs *g);
void	cast(int id, t_structs *g);
void	horizontale(t_structs *g);
void	verticale(t_structs *g);
void	while_wall(t_structs *g, float xstep, float ystep, int i);
float	distancebetweenpoints(t_structs *g, float x, float y);
void	projectionwall(t_structs *g, int id);
char	*get_next_line(int fd);
int		ft_exit(void);
int		check_map(t_structs *g, char *file);
void	error_exit(char *str);
#endif
