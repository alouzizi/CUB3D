#include "test.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}


int	main(void)
{
	t_mlx	mlx;
	t_data	img;
	t_player player;
	int i,j;
	int rows = 12;
    int cols = 20;
    int width = cols * 42;
    int height = rows * 42;

	player.x = width / 2;
    player.y = height /2;
    player.radius = 3;
    player.turndirection = 0;
    player.walkdirection = 0;
    player.rotationangle = M_PI / 2;
    player.movespeed = 15.0;
    player.rotationspeed = 15 * (M_PI / 180);
    printf("player.rotationangle = %f\n", player.rotationspeed);
	i = j = 0;
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, width, height, "Hello world!");
	img.img = mlx_new_image(mlx.mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	// mlx_put_image_to_window(mlx.mlx, mlx.win, img.img, 0, 0);
	img.mlx = mlx;
	img.player = player;
	mlx_loop_hook(mlx.mlx, loop_hook, &img);
	mlx_loop(mlx.mlx);
}

int loop_hook(t_data *img, int x, int y)
{
	int i,j;
	int rows = 12;
    int cols = 20;
    int width = cols * 42;
    int height = rows * 42; 

	mlx_clear_window(img->mlx.mlx, img->mlx.win);
	//printf("hello from loop_hook\n");
	i = j = 0;
    while(i < rows)
    { 
        while(j < cols)
        {
            if(mape[i][j] == 1)
            {
               draw_wall(j * 42, i * 42, 42, 42, img, 0xFFFFFF);
            }
            else
            {
                draw_wall(j * 42, i * 42, 42, 42, img, 0x00FF0000);
            }
            j++;
        }
        j = 0;
        i++;
    }
	draw_player(img->player.x, img->player.y, 10, 10, img, 0x00FF00); 
	//int x1 = img->player.x + cos(img->player.rotationangle) * 30;
	//int y1 = img->player.y + sin(img->player.rotationangle) * 30;
	// int x1= 100;
	// int y1 = 100;
	//dda(img, img->player.x, img->player.y, x1, y1);
    // mlx_xpm_file_to_image(img->mlx.mlx, "player.xpm", &x, &y);
	mlx_put_image_to_window(img->mlx.mlx, img->mlx.win, img->img, 0, 0);
	mlx_key_hook(img->mlx.win, relased, &img->player);
	return (0);
}

void update(t_player *player, int j)
{
    int step;
    int x;
    int y;
    step = player->walkdirection * player->movespeed;
    if(j == 1)
    {
        x = round(player->x + cos(player->rotationangle) * step);
        y = round(player->y + sin(player->rotationangle) * step);
    }
    if (j != 1)
    {
        step = player->turndirection * player->movespeed;
        if (player ->turndirection == 1)
        {
            x = round(player->x - sin(player->rotationangle) * 10);
            y = round(player->y + cos(player->rotationangle) * 10);
        }
        if (player ->turndirection == -1)
        {
            x = round(player->x + sin(player->rotationangle) * 10);
            y = round(player->y - cos(player->rotationangle) * 10);
        }
    }  
    player->x = x;
    player->y = y;
    player->turndirection = 0;
    player->walkdirection = 0;
}

t_player rotate_player(t_player p, double angle)
{
    t_player rotated;
    rotated.x = p.x * cos(angle) - p.y * sin(angle);
    rotated.y = p.x * sin(angle) + p.y * cos(angle);
    return rotated;
}

int relased(int key, t_player *player)
{
    printf("hello from key : %d\n", key);
    
    if (key == 13)
    {

    //    player->y += -20;
        player->walkdirection = 1;
        update(player,1);
    }
    if (key == 1)
    {
       // player->y += 20;
        player->walkdirection = -1;
        update(player,1); 
    }
    if (key == 0)
    {
       // player->x -= 20;
     player->turndirection = -1;
        // player->rotationangle += player->rotationspeed;
        update(player,0);
    }
    if(key == 2)
    {
        //player->x += 20;
      player->turndirection = +1;
      update(player,0);
    }
    if(key == 124)
    {
        player->rotationangle += player->rotationspeed;
    }
    if(key ==123)
    {
       player->rotationangle -= player->rotationspeed;
    }
    return(0);
}

void draw_wall(int x, int y, int width, int height, t_data *img, int color)
{
	int i = 0;
	int j = 0;
	while(i < width)
	{
        my_mlx_pixel_put(img, x + i, y + j, 0x0000FF);
		while(j < height)
		{
            if(i == 0)
                my_mlx_pixel_put(img, x + i, y + j, 0x000000);
            else
			    my_mlx_pixel_put(img, x + i, y + j, color);
			j++;
		}
        my_mlx_pixel_put(img, x + i, y + j, 0x0000FF);
		j = 0;
        
        my_mlx_pixel_put(img, x + i, y + j, 0x000000);
		i++;
	}
}

void draw_player(int x, int y , int width, int height, t_data *img, int color)
{
    int i = 0;
    int j = 0;
    while(i < width)
    {
        while(j < height)
        {
            my_mlx_pixel_put(img, x + i, y + j, color);
            j++;
        }
        j = 0;
        i++;
    }
    img->player.rotationangle += img->player.rotationspeed * img->player.turndirection;
    int x1 = x + cos(img->player.rotationangle) * 30;
    int y1 = y + sin(img->player.rotationangle) * 30;
    // img->player.turndirection = 0;
    // img->player.walkdirection = 0;
   dda(img, x, y, x1, y1); 
}


void dda(t_data *data,int X0, int Y0, int X1, int Y1)
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
		my_mlx_pixel_put(data,round(X), round(Y), 0x000000); // put pixel at (X,Y)
        //mlx_pixel_put(mlx->mlx, mlx->win,round(X), round(Y),0x000000); // put pixel at (X,Y)
        X += Xinc; // increment in x at each step
        Y += Yinc; // increment in y at each step
    }
}
