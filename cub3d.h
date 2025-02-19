/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 19:11:21 by jainavas          #+#    #+#             */
/*   Updated: 2025/02/19 16:03:28 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define PI 3.14159265358979323846
# define WINW 640
# define WINH 480

# include "./minilibx-linux/mlx.h"
# include "./libft_ext/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>

enum kcodes{
	ESC = 65307,
	w = 119,
	a = 97,
	s = 115,
	d = 100,
	uparrow = 65362,
	rightarrow = 65363,
	downarrow = 65364,
	leftarrow = 65361,
};

typedef struct posi
{
	double	x;
	double	y;
} t_vector;

typedef struct s_color
{
	long	t;
	long	r;
	long	g;
	long	b;
}				t_color;

typedef struct s_myimg
{
	char			*name;
	int				height;
	int				width;
	void			*i;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
	struct s_myimg	*next;
	struct s_myimg	*prev;
}				t_imgx;

typedef struct ray
{
	double	cos;
	double	sin;
	double	x;
	double	y;
} t_ray;

typedef struct map
{
	int		numlines;
	int		numwd;
	char	orientation;
	double	pospx;
	double	pospy;
	double	x;
	double	y;
	t_ray	ray;
	int		fov;
	int		halfov;
	double	angle;
	double	accangle;
	double	precision;
	double	viewlimit;
	int		poscenter;
	char	*pathnorth;
	char	*pathwest;
	char	*patheast;
	char	*pathsouth;
	char	*ceilingcolor;
	t_color	ceicolor;
	char	*floorcolor;
	t_color	flocolor;
	char	**map;
	int		**intmap;
	char	**mapcpy;
} t_map;

typedef struct {
	// Player position
	double posX;
	double posY;
	// Player direction vector
	double dirX;
	double dirY;	
	// Camera plane (for field of view)
	double planeX;
	double planeY;	
	// Time and oldTime for frame timing
	double time;
	double oldTime;	
	// Map dimensions
	int mapWidth;
	int mapHeight;	
	// Map data (2D array)
	int **map;	
	// Screen dimensions
	int screenWidth;
	int screenHeight;	
	// Raycasting variables
	double cameraX;      // x-coordinate in camera space
	double rayDirX;      // ray direction vector
	double rayDirY;
	int mapX;            // current square of the map the ray is in
	int mapY;
	double sideDistX;    // length of ray from current position to next x or y-side
	double sideDistY;
	double deltaDistX;   // length of ray from one x or y-side to next x or y-side
	double deltaDistY;
	double perpWallDist; // perpendicular distance to the wall
	int stepX;           // what direction to step in x or y-direction (either +1 or -1)
	int stepY;
	int hit;             // was there a wall hit?
	int side;            // was a NS or a EW wall hit?	
	// Texture variables
	int texNum;          // texture number
	int texX;            // x coordinate on the texture
	double wallX;        // where exactly the wall was hit
	double step;        // where exactly the wall was hit
	double texPos;        // where exactly the wall was hit
	int texWidth;        // texture width
	int texHeight;       // texture height
	int	lineHeight;
	int	drawStart;
	int	drawEnd;
	int	color;
	int	pixel;
	// Color variables
	// Movement and rotation speeds
	double moveSpeed;
	double rotSpeed;
	// Key states (for movement)
	int keyW;
	int keyS;
	int keyA;
	int keyD;
	int keyLeft;
	int keyRight;
} t_rayc;

typedef struct var
{
	void	*mlx;
	void	*mlx_win;
	t_imgx	*win_img;
	int		height;
	int		width;
	int		moved;
	t_rayc	*rc;
	t_map	*vmap;
	t_imgx	**imgs;
}	t_mlx;

// cubed.c
// map
int		searchp(t_map *vmap, char **map);
int		checkfloodfill(t_map *vmap);
t_map	*fullmap(int numargs, char *filename);
int		spaces(char str);
void	getpaths(t_map *vmap, int fd);
int		**doublechartodoubleint(t_map *vmap);
void	findlongestline(t_map *vmap);
int		checkcolorstruct(t_map *vmap);
// movement.c
int	moves(int key_code, t_mlx *mlx);
// math0.c
double 	degreesToRadians(double degrees);
void 	raycast(t_rayc *rc, t_mlx *mlx);
t_rayc	*initrayvars(t_map *vmap);
// graphics0.c
void	initmlxassets(t_mlx *mlx, t_map *vmap);
int		new_trgb(t_color c);
t_color	new_rgbt(int col);
int		close_win(t_mlx *vars);
// imglisthandle.c
t_imgx	*imgnew(char *name);
t_imgx	*imglast(t_imgx *lst);
void	imgadd_back(t_imgx **lst, t_imgx *new);
void	imgaddr(t_imgx *img, t_mlx *mlx, char *file);
t_imgx	*imgsearch(char *tolook, t_imgx **head);
void	freeimgs(t_imgx **head, t_mlx *mlx);
// mlxutils.c
void			my_mlx_pixel_put(t_imgx *data, int x, int y, int color);
unsigned int	my_mlx_pixel_get(t_imgx *data, int x, int y);
void			my_mlx_area_put(t_imgx *d, t_vector p, t_vector dim, int c);
t_vector		newvector(int x, int y);

#endif