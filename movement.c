/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 21:50:50 by jainavas          #+#    #+#             */
/*   Updated: 2025/02/17 20:28:41 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	moves(int key_code, t_mlx *mlx)
{
	double	nwx;
	double	nwy;

	nwx = cos(degreesToRadians(mlx->vmap->angle)) * 0.6;
	nwy = sin(degreesToRadians(mlx->vmap->angle)) * 0.6;
	if (key_code == leftarrow)
		return (mlx->vmap->angle -= 2, mlx->moved = 1, cube_loop((void *)mlx), 0);
	if (key_code == rightarrow)
		return (mlx->vmap->angle += 2, mlx->moved = 1, cube_loop((void *)mlx), 0);
	if (key_code == w && mlx->vmap->map[(int)(mlx->vmap->pospy + nwy + 0.5)][(int)(mlx->vmap->pospx + nwx + 0.5)] != '1')
		return (mlx->vmap->pospx += nwx, mlx->vmap->pospy += nwy, mlx->moved = 1, cube_loop((void *)mlx), 0);
	if (key_code == s && mlx->vmap->map[(int)(mlx->vmap->pospy - nwy - 0.5)][(int)(mlx->vmap->pospx - nwx - 0.5)] != '1')
		return (mlx->vmap->pospx -= nwx, mlx->vmap->pospy -= nwy, mlx->moved = 1, cube_loop((void *)mlx), 0);
	if (key_code == d && mlx->vmap->map[(int)(mlx->vmap->pospy + (sin(degreesToRadians(mlx->vmap->angle + 90)) * 0.6) + 0.5)][(int)(mlx->vmap->pospx + (cos(degreesToRadians(mlx->vmap->angle + 90)) * 0.6) + 0.5)] != '1')
		return (mlx->vmap->pospx += cos(degreesToRadians(mlx->vmap->angle + 90)) * 0.6, mlx->vmap->pospy += sin(degreesToRadians(mlx->vmap->angle + 90)) * 0.6, mlx->moved = 1, cube_loop((void *)mlx), 0);
	if (key_code == a && mlx->vmap->map[(int)(mlx->vmap->pospy + (sin(degreesToRadians(mlx->vmap->angle - 90)) * 0.6) + 0.5)][(int)(mlx->vmap->pospx + (cos(degreesToRadians(mlx->vmap->angle - 90)) * 0.6) + 0.5)] != '1')
		return (mlx->vmap->pospx += cos(degreesToRadians(mlx->vmap->angle - 90)) * 0.6, mlx->vmap->pospy += sin(degreesToRadians(mlx->vmap->angle - 90)) * 0.6, mlx->moved = 1, cube_loop((void *)mlx), 0);
	if (key_code == ESC)
		close_win(mlx);
	return (0);
}
