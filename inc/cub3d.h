/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 19:11:21 by jainavas          #+#    #+#             */
/*   Updated: 2025/02/26 19:37:54 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define PI 3.14159265358979323846
# define WINW 1024
# define WINH 768

# include "../minilibx-linux/mlx.h"
# include "../libft_ext/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>

enum	e_kcodes
{
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
}	t_vector;

typedef struct s_color
{
	long	t;
	long	r;
	long	g;
	long	b;
}	t_color;

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
}	t_ray;

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
	int		lastmapline;
	int		fmpl;
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
}	t_map;

typedef struct s_rayc
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;	
	double	plane_x;
	double	plane_y;	
	double	time;
	double	old_time;	
	int		map_width;
	int		map_height;	
	int		**map;	
	int		screen_width;
	int		screen_height;	
	// Raycasting variables
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	// Texture variables
	int		tex_num;
	int		tex_x;
	double	wall_x;
	double	step;
	double	tex_pos;
	int		tex_width;
	int		tex_height;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		color;
	int		pixel;
	// Movement and rotation speeds
	double	move_speed;
	double	rot_speed;
}	t_rayc;

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
int				find_player(t_map *vmap, char **map);
int				check_flood_fill(t_map *vmap);
t_map			*init_map(int numargs, char *filename);
int				check_spaces(char str);
void			get_textures_paths(t_map *vmap, int fd);
int				**convert_to_int_map(t_map *vmap);
void			get_map_dimensions(t_map *vmap);
int				validate_colors(t_map *vmap);
int				colorparser(char *line, t_color *color);
// movement.c
int				handle_movement(int key_code, t_mlx *mlx);
// math0.c
double			degrees_to_radians(double degrees);
void			raycast(t_rayc *rc, t_mlx *mlx);
t_rayc			*init_raycasting(t_map *vmap);
// graphics0.c
void			init_resources(t_mlx *mlx, t_map *vmap);
int				set_color(t_color c);
t_color			get_color(int col);
int				close_window(t_mlx *vars);
// imglisthandle.c
t_imgx			*create_new_image(char *name);
t_imgx			*get_last_image(t_imgx *lst);
void			add_image_back(t_imgx **lst, t_imgx *new);
void			set_image_address(t_imgx *img, t_mlx *mlx, char *file);
t_imgx			*search_image(char *tolook, t_imgx **head);
void			freepaths(t_map *vmap);
void			free_images(t_imgx **head, t_mlx *mlx);
// mlxutils.c
void			put_pixel(t_imgx *data, int x, int y, int color);
unsigned int	get_pixel(t_imgx *data, int x, int y);
void			draw_area(t_imgx *d, t_vector p, t_vector dim, int c);
t_vector		create_vector(int x, int y);
int				set_player_orientation(t_map *vmap, t_rayc *rc);
t_imgx			*get_wall_texture(t_rayc *rc, t_mlx *mlx,
					double ray_dir_x, double ray_dr_y);
void			draw_background(t_rayc *rc, t_mlx *mlx);
void			draw_textured_line(t_rayc *rc, t_mlx *mlx, int x, t_imgx *img);
void			rotate_camera_left(t_mlx *mlx);
void			rotate_camera_right(t_mlx *mlx);
int				count_map_lines(char *filename, int *nred);
int				parse_map_content(t_map *vmap, char *filename,
					int fd, int nred);
void			putmapinwidth(t_map *vmap);

#endif