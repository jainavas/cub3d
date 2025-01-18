/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 19:21:16 by jainavas          #+#    #+#             */
/*   Updated: 2024/10/12 20:45:50 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	imgdestruction(mlx_type *mlxv)
{
	mlx_destroy_image(mlxv->mlx, mlxv->imgv->player);
	mlx_destroy_image(mlxv->mlx, mlxv->imgv->colecc);
	mlx_destroy_image(mlxv->mlx, mlxv->imgv->exit);
	mlx_destroy_image(mlxv->mlx, mlxv->imgv->vertconnwall);
	mlx_destroy_image(mlxv->mlx, mlxv->imgv->vertwall);
	mlx_destroy_image(mlxv->mlx, mlxv->imgv->horconnwall);
	mlx_destroy_image(mlxv->mlx, mlxv->imgv->hornormwall);
	mlx_destroy_image(mlxv->mlx, mlxv->imgv->floor);
	return (0);
}

int	close_win(mlx_type *vars)
{
	imgdestruction(vars);
	mlx_destroy_window(vars->mlx, vars->mlx_win);
	mlx_destroy_display(vars->mlx);
	protectdoublestr(vars->vmap->map);
	free(vars->imgv);
	free(vars->vmap);
	free(vars->mlx);
	free(vars);
	exit(0);
	return (0);
}

int	imgdefinition(mlx_type *mlxv, t_imgs *img)
{
	img->floor = loadimgfloor;
	img->hornormwall = loadimghornormwall;
	img->horconnwall = loadimghorconnwall;
	img->vertconnwall = loadimgverconnwall;
	img->vertwall = loadimgverwall;
	img->player = loadimgplayer;
	img->colecc = loadimgcolecc;
	img->exit = loadimgexit;
	return (0);
}

int	putfloor(t_map *vmap, mlx_type *mlxv, t_imgs *imgv)
{
	int	i;
	int	j;

	j = 0;
	while (j < vmap->numlines)
	{
		i = 0;
		while (i <= vmap->numwd)
		{
			if (mapa[j][i] == 'P')
				mlx_put_image_to_window(argplayer);
			else if (mapa[j][i] == 'E')
				mlx_put_image_to_window(argexit);
			else if (mapa[j][i] == 'C')
				mlx_put_image_to_window(argcolecc);
			else if (mapa[j][i] != 'E' && mapa[j][i] != 'C'
				&& mapa[j][i] != 'P' && mapa[j][i] != '1')
				mlx_put_image_to_window(argfloor);
			else
				i++;
		}
		j++;
	}
	return (0);
}
