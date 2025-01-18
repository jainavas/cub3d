/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ..h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 17:01:11 by jainavas          #+#    #+#             */
/*   Updated: 2024/10/11 19:32:27 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "./minilibx-linux/mlx.h"
# include "./minilibx-linux/mlx_int.h"
# include "libft/libft.h"
# include "printf/ft_printf.h"
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>

// structs

typedef struct map
{
	int		nump;
	int		numc;
	int		nume;
	int		numlines;
	int		pospx;
	int		pospy;
	int		posex;
	int		posey;
	int		numwd;
	int		nummoves;
	char	**map;
	char	**mapcpy;
} t_map;

typedef struct imgs
{
	void	*floor;
	void	*hornormwall;
	void	*horconnwall;
	void	*vertwall;
	void	*vertconnwall;
	void	*player;
	void	*colecc;
	void	*exit;
}	t_imgs;

typedef struct var
{
	void	*mlx;
	void	*mlx_win;
	int		height;
	int		width;
	t_map	*vmap;
	t_imgs	*imgv;
}	mlx_type;

enum kcodes{
	ESC = 65307,
	w = 119,
	a = 97,
	s = 115,
	d = 100,
};

// DEFINES

# define posipy mlxv->vmap->pospy
# define posipx mlxv->vmap->pospx
# define posiex mlxv->vmap->posex
# define posiey mlxv->vmap->posey
# define mapa mlxv->vmap->map
# define winsizx 64 * (mlxvars->vmap->numwd + 1)
# define winsizy 64 * mlxvars->vmap->numlines
# define argwin mlxvars->mlx, winsizx, winsizy, "so_long"
# define arghorwall1 mlxv->mlx, mlxv->mlx_win, imgv->vertconnwall, 64 * (vmap->numwd), 64 * j
# define arghorwall2 mlxv->mlx, mlxv->mlx_win, imgv->vertconnwall, 64 * i, 64 * j
# define arghorwall3 mlxv->mlx, mlxv->mlx_win, imgv->horconnwall, 64 * i, 64 * (vmap->numlines - 1)
# define arghorwall4 mlxv->mlx, mlxv->mlx_win, imgv->horconnwall, 64 * vmap->numwd, 64 * (vmap->numlines - 1)
# define arghorwall5 mlxv->mlx, mlxv->mlx_win, imgv->hornormwall, 64 * i, 64 * j
# define argverwall1 mlxv->mlx, mlxv->mlx_win, imgv->vertwall, 64 * 0, 64 * j
# define argverwall2 mlxv->mlx, mlxv->mlx_win, imgv->vertwall, 64 * vmap->numwd, 64 * j
# define argplayer mlxv->mlx, mlxv->mlx_win, imgv->player, 64 * i++, 64 * j
# define argexit mlxv->mlx, mlxv->mlx_win, imgv->exit, 64 * i++, 64 * j
# define argcolecc mlxv->mlx, mlxv->mlx_win, imgv->colecc, 64 * i++, 64 * j
# define argfloor mlxv->mlx, mlxv->mlx_win, imgv->floor, 64 * i++, 64 * j
# define loadimgplayer mlx_xpm_file_to_image(mlxv->mlx, "./textures/player.xpm", &mlxv->height, &mlxv->width)
# define loadimgfloor mlx_xpm_file_to_image(mlxv->mlx, "./textures/floor.xpm", &mlxv->height, &mlxv->width)
# define loadimghornormwall mlx_xpm_file_to_image(mlxv->mlx, "./textures/wall1.xpm", &mlxv->height, &mlxv->width)
# define loadimghorconnwall mlx_xpm_file_to_image(mlxv->mlx, "./textures/wall2.xpm", &mlxv->height, &mlxv->width)
# define loadimgverconnwall mlx_xpm_file_to_image(mlxv->mlx, "./textures/wall3.xpm", &mlxv->height, &mlxv->width)
# define loadimgverwall mlx_xpm_file_to_image(mlxv->mlx, "./textures/wall4.xpm", &mlxv->height, &mlxv->width)
# define loadimgcolecc mlx_xpm_file_to_image(mlxv->mlx, "./textures/colecc.xpm", &mlxv->height, &mlxv->width)
# define loadimgexit mlx_xpm_file_to_image(mlxv->mlx, "./textures/exit.xpm", &mlxv->height, &mlxv->width)
# define returnputmap putmap(mlxv->vmap, mlxv, mlxv->imgv), ft_printf("%d\n", ++mlxv->vmap->nummoves), 0



// graphics
int				imgdestruction(mlx_type  *mlxv);
int				close_win(mlx_type *vars);
int				imgdefinition(mlx_type *mlxv, t_imgs *img);
int				putfloor(t_map *vmap, mlx_type *mlxv, t_imgs *imgv);
int				putwallvert(t_map *vmap, mlx_type *mlxv, t_imgs *imgv);
int				putwallhor(t_map *vmap, mlx_type *mlxv, t_imgs *imgv);
int				putmap(t_map *vmap, mlx_type *mlxv, t_imgs *imgv);
int				moveplayer(int key_code, mlx_type *mlxv);
int				putimg(mlx_type *mlxvars);


// map
int				checkborder(t_map *vmap);
int				searchcs(t_map *vmap, char **map);
int				searchpe(t_map *vmap, char **map);
int				fullmap(mlx_type *mlxv, int numargs, char *filename);
int 			putimg(mlx_type *mlxvars);
void			protectdoublestr(char **split);

#endif