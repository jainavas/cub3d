/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:04:15 by jainavas          #+#    #+#             */
/*   Updated: 2024/10/12 20:42:57 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	putwallvert(t_map *vmap, mlx_type *mlxv, t_imgs *imgv)
{
	int	j;

	j = 1;
	while (j < vmap->numlines - 1)
	{
		mlx_put_image_to_window(argverwall1);
		mlx_put_image_to_window(argverwall2);
		j++;
	}
	return (0);
}

int	putwallhor(t_map *vmap, mlx_type *mlxv, t_imgs *imgv)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	mlx_put_image_to_window(arghorwall1);
	mlx_put_image_to_window(arghorwall2);
	mlx_put_image_to_window(arghorwall3);
	mlx_put_image_to_window(arghorwall4);
	while (j < vmap->numlines)
	{
		i = 0;
		while (++i < vmap->numwd)
			if (mapa[j][i] == '1')
				mlx_put_image_to_window(arghorwall5);
		j++;
	}
	return (0);
}

int	putmap(t_map *vmap, mlx_type *mlxv, t_imgs *imgv)
{
	if (posiex == posipx && posiey == posipy && searchcs(vmap, mapa) == 0)
	{
		ft_printf("Felicidades, has hecho %d moves\n", mlxv->vmap->nummoves);
		close_win(mlxv);
	}
	else if (posiex == posipx && posiey == posipy && searchcs(vmap, mapa) != 0)
		mapa[posiey][posiex] = 'P';
	else if (!(posiex == posipx && posiey == posipy))
		mapa[posiey][posiex] = 'E';
	putfloor(vmap, mlxv, imgv);
	return (0);
}

int	moveplayer(int key_code, mlx_type *mlxv)
{
	if (key_code == w && mapa[posipy - 1][posipx] != '1')
	{
		mapa[posipy][posipx] = '0';
		mapa[--posipy][posipx] = 'P';
	}
	else if (key_code == s && mapa[posipy + 1][posipx] != '1')
	{
		mapa[posipy][posipx] = '0';
		mapa[++posipy][posipx] = 'P';
	}
	else if (key_code == a && mapa[posipy][posipx - 1] != '1')
	{
		mapa[posipy][posipx] = '0';
		mapa[posipy][--posipx] = 'P';
	}
	else if (key_code == d && mapa[posipy][posipx + 1] != '1')
	{
		mapa[posipy][posipx] = '0';
		mapa[posipy][++posipx] = 'P';
	}
	else if (key_code == ESC)
		close_win(mlxv);
	else
		return (0);
	return (returnputmap);
}

int	putimg(mlx_type *mlxvars)
{
	mlxvars->imgv = ft_calloc(1, sizeof(t_imgs));
	mlxvars->height = 64;
	mlxvars->width = 64;
	mlxvars->mlx = mlx_init();
	mlxvars->mlx_win = mlx_new_window(argwin);
	imgdefinition(mlxvars, mlxvars->imgv);
	putwallhor(mlxvars->vmap, mlxvars, mlxvars->imgv);
	putwallvert(mlxvars->vmap, mlxvars, mlxvars->imgv);
	putmap(mlxvars->vmap, mlxvars, mlxvars->imgv);
	mlx_key_hook(mlxvars->mlx_win, moveplayer, mlxvars);
	mlx_hook(mlxvars->mlx_win, 17, 1L << 0, close_win, mlxvars);
	mlx_loop(mlxvars->mlx);
	free(mlxvars);
	return (0);
}
