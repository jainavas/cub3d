/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 19:11:21 by jainavas          #+#    #+#             */
/*   Updated: 2024/12/18 00:05:59 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./minilibx-linux/mlx.h"
# include "./minilibx-linux/mlx_int.h"
# include "./libft_ext/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>

typedef struct map
{
	int		numlines;
	int		numwd;
	char	orientation;
	double	pospx;
	double	dirpx;
	double	pospy;
	double	dirpy;
	double	planey;
	double	planex;
	char	*pathnorth;
	char	*pathwest;
	char	*patheast;
	char	*pathsouth;
	char	*ceilingcolor;
	char	*floorcolor;
	char	**map;
	int		**intmap;
	char	**mapcpy;
} t_map;

typedef struct var
{
	void	*mlx;
	void	*mlx_win;
	int		height;
	int		width;
	t_map	*vmap;
}	mlx_type;

// map
int		searchp(t_map *vmap, char **map);
int		checkfloodfill(t_map *vmap);
t_map	*fullmap(int numargs, char *filename);
int		spaces(char str);
void	getpaths(t_map *vmap, int fd);
void	doublechartodoubleint(t_map *vmap);
void	findlongestline(t_map *vmap);


#endif