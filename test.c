#include "test.h"

int main(){
    t_mlx mlx;
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
    player.movespeed = 2.0;
    player.rotationspeed = 2 * (M_PI / 180);

    i = j = 0; 
    mlx.mlx = mlx_init();
    mlx.win = mlx_new_window(mlx.mlx, width, height, "SUUUU");
    // while(i < rows)
    // { 
    //     while(j < cols)
    //     {
    //         if(map[i][j] == 1)
    //             mlx.img = mlx_xpm_file_to_image(mlx.mlx,"w.xpm", &width, &height);
    //         else
    //             mlx.img = mlx_xpm_file_to_image(mlx.mlx,"black.xpm", &width, &height);
    //         mlx_put_image_to_window(mlx.mlx, mlx.win,mlx.img, j *  42, i * 42);
    //         j++;
    //     }
    //     j = 0;
    //     i++;
    // }
    // mlx.img = mlx_xpm_file_to_image(mlx.mlx,"r.xpm",&width, &height);
    // mlx_put_image_to_window(mlx.mlx, mlx.win,mlx.img, player.x, player.y);
    // mlx_loop_hook(mlx.mlx);
    // int x2 = player.x + (cos(player.rotationangle) * 30);
    // int y2 = player.y + (sin(player.rotationangle) * 30);
    // dda(&mlx, player.x, player.y, x2, y2);
    mlx_key_hook(mlx.win,key_hook, &player);
    player.mlx = mlx;
    mlx_loop_hook(mlx.mlx, update_player, &player);
    mlx_loop(mlx.mlx);
}


int key_hook(int key, t_player *player)
{
    printf("hello from key : %d\n", key);
    if (key == 126)
        player->walkdirection = 1;
    if (key == 125)
         player->walkdirection = -1;
    if(key == 124)
        player->turndirection = 1;
    if (key == 123)
        player->turndirection = -1;
return(0);
};

int update_player(t_player *player)
{

    mlx_clear_window(player->mlx.mlx, player->mlx.win);
    int i,j;
    int rows = 12;
    int cols = 20;
    int width = cols * 42;
    int height = rows * 42;

    i = j =0;
    while(i < rows)
    { 
        while(j < cols)
        {
            if(map[i][j] == 1)
                player->mlx.img = mlx_xpm_file_to_image(player->mlx.mlx,"w.xpm", &width, &height);
            else
                player->mlx.img = mlx_xpm_file_to_image(player->mlx.mlx,"black.xpm", &width, &height);
            mlx_put_image_to_window(player->mlx.mlx, player->mlx.win,player->mlx.img, j *  42, i * 42);
            j++;
        }
        j = 0;
        i++;
    }
    player->mlx.img = mlx_xpm_file_to_image(player->mlx.mlx,"r.xpm",&width, &height);
    mlx_put_image_to_window(player->mlx.mlx, player->mlx.win,player->mlx.img, player->x, player->y);
    // mlx_get_data_addr();
    player->rotationangle += player->turndirection * player->rotationspeed;
    
    player->mlx.img = mlx_xpm_file_to_image(player->mlx.mlx,"r.xpm",&width, &height);
    mlx_put_image_to_window(player->mlx.mlx, player->mlx.win,player->mlx.img, player->x, player->y);
    mlx_key_hook(player->mlx.win,relased, player);
    return(0);
} 

int relased(int key, t_player *player)
{
    printf("hello from key : %d\n", key);
    
    if (key == 126)
        player->walkdirection = 1;
    if (key == 125)
        player->walkdirection = -1;
    if(key == 124)
        player->turndirection = 1;
    if (key == 123)
        player->turndirection = -1;
    return(0);
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
        mlx_pixel_put(mlx->mlx, mlx->win,round(X), round(Y),0xff0a00); // put pixel at (X,Y)
        X += Xinc; // increment in x at each step
        Y += Yinc; // increment in y at each step
    }
}
