/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 19:11:21 by jainavas          #+#    #+#             */
/*   Updated: 2025/02/16 23:28:06 by jainavas         ###   ########.fr       */
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

typedef struct var
{
	void	*mlx;
	void	*mlx_win;
	t_imgx	*win_img;
	int		height;
	int		width;
	int		moved;
	t_map	*vmap;
	t_imgx	**imgs;
}	t_mlx;

// cubed.c
int	cube_loop(void *param);
// map
int		searchp(t_map *vmap, char **map);
int		checkfloodfill(t_map *vmap);
t_map	*fullmap(int numargs, char *filename);
int		spaces(char str);
void	getpaths(t_map *vmap, int fd);
void	doublechartodoubleint(t_map *vmap);
void	findlongestline(t_map *vmap);
int		checkcolorstruct(t_map *vmap);
// movement.c
int	moves(int key_code, t_mlx *mlx);
// math0.c
double 	degreesToRadians(double degrees);
void	fullraycast(t_map *vmap, t_mlx *vars);
void	initrayvars(t_map *vmap);
// graphics0.c
void	initmlxassets(t_mlx *mlx, t_map *vmap);
int		get_dist_color(int color, float ds, int tr);
int		new_trgb(t_color c);
t_color	new_rgbt(int col);
void	draw_texture(t_mlx *mlx, t_imgx *i, int ray_count, int wall_height);
void	drawall(t_mlx *mlx, int ray_count, float dis);
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
void			mlx_img_to_img(int p[2], t_imgx img[2], int c1);
t_imgx			*get_texture(t_map *vmap, t_imgx **img);
int				get_tex_color(t_map *vmap, t_imgx *i, int z);
void			redraw_elem(t_mlx *mlx, t_imgx img, int x, int y);

#endif