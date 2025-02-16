/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 21:50:50 by jainavas          #+#    #+#             */
/*   Updated: 2025/02/16 23:27:41 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	moves(int key_code, t_mlx *mlx)
{
	double	nwx;
	double	nwy;

	nwx = mlx->vmap->pospx + cos(degreesToRadians(mlx->vmap->angle)) * 0.6;
	nwy = mlx->vmap->pospy + sin(degreesToRadians(mlx->vmap->angle)) * 0.6;
	if (key_code == leftarrow)
		return (mlx->vmap->angle -= 2, mlx->moved = 1, cube_loop((void *)mlx), 0);
	if (key_code == rightarrow)
		return (mlx->vmap->angle += 2, mlx->moved = 1, cube_loop((void *)mlx), 0);
	if (key_code == w && mlx->vmap->map[(int)(mlx->vmap->pospy - 0.6)][(int)(mlx->vmap->pospx)])
		return (mlx->vmap->pospx = nwx, mlx->vmap->pospy = nwy, mlx->moved = 1, cube_loop((void *)mlx), 0);
	if (key_code == s && mlx->vmap->map[(int)(mlx->vmap->pospy + 0.6)][(int)(mlx->vmap->pospx)])
		return (mlx->vmap->pospx = nwx, mlx->vmap->pospy = nwy, mlx->moved = 1, cube_loop((void *)mlx), 0);
	if (key_code == d && mlx->vmap->map[(int)(mlx->vmap->pospy)][(int)(mlx->vmap->pospx + 0.6)])
		return (mlx->vmap->pospx = nwx, mlx->vmap->pospy = nwy, mlx->moved = 1, cube_loop((void *)mlx), 0);
	if (key_code == a && mlx->vmap->map[(int)(mlx->vmap->pospy)][(int)(mlx->vmap->pospx - 0.6)])
		return (mlx->vmap->pospx = nwx, mlx->vmap->pospy = nwy, mlx->moved = 1, cube_loop((void *)mlx), 0);
	if (key_code == ESC)
		close_win(mlx);
	return (0);
}