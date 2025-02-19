/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 21:50:50 by jainavas          #+#    #+#             */
/*   Updated: 2025/02/19 16:02:10 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_w(t_mlx *mlx)
{
	if(mlx->rc->map[(int)(mlx->rc->posY)][(int)(mlx->rc->posX + (mlx->rc->dirX * mlx->rc->moveSpeed))] != 1)
		mlx->rc->posX += mlx->rc->dirX * mlx->rc->moveSpeed;
	else
		mlx->rc->posX -= mlx->rc->dirX * (mlx->rc->moveSpeed / 4);
    if(mlx->rc->map[(int)(mlx->rc->posY + mlx->rc->dirY * mlx->rc->moveSpeed)][(int)(mlx->rc->posX)] != 1)
		mlx->rc->posY += mlx->rc->dirY * mlx->rc->moveSpeed;
	else
		mlx->rc->posY -= mlx->rc->dirY * (mlx->rc->moveSpeed / 4);
}

void	move_s(t_mlx *mlx)
{
	if(mlx->rc->map[(int)(mlx->rc->posY)][(int)(mlx->rc->posX - mlx->rc->dirX * mlx->rc->moveSpeed)] != 1)
		mlx->rc->posX -= mlx->rc->dirX * mlx->rc->moveSpeed;
	else
		mlx->rc->posX += mlx->rc->dirX * (mlx->rc->moveSpeed / 4);
    if(mlx->rc->map[(int)(mlx->rc->posY - mlx->rc->dirY * mlx->rc->moveSpeed)][(int)(mlx->rc->posX)] != 1)
		mlx->rc->posY -= mlx->rc->dirY * mlx->rc->moveSpeed;
	else
		mlx->rc->posY += mlx->rc->dirY * (mlx->rc->moveSpeed / 4);
}

void move_d(t_mlx *mlx)
{
    int newX = (int)(mlx->rc->posX - mlx->rc->dirY * mlx->rc->moveSpeed);
    int newY = (int)(mlx->rc->posY + mlx->rc->dirX * mlx->rc->moveSpeed);

    if (mlx->rc->map[(int)mlx->rc->posY][newX] != 1)
        mlx->rc->posX -= mlx->rc->dirY * mlx->rc->moveSpeed;
    else
        mlx->rc->posX += mlx->rc->dirY * (mlx->rc->moveSpeed / 4);

    if (mlx->rc->map[newY][(int)mlx->rc->posX] != 1)
        mlx->rc->posY += mlx->rc->dirX * mlx->rc->moveSpeed;
    else
        mlx->rc->posY -= mlx->rc->dirX * (mlx->rc->moveSpeed / 4);
}

void move_a(t_mlx *mlx)
{
    int newX = (int)(mlx->rc->posX + mlx->rc->dirY * mlx->rc->moveSpeed);
    int newY = (int)(mlx->rc->posY - mlx->rc->dirX * mlx->rc->moveSpeed);

    if (mlx->rc->map[(int)mlx->rc->posY][newX] != 1)
        mlx->rc->posX += mlx->rc->dirY * mlx->rc->moveSpeed;
    else
        mlx->rc->posX -= mlx->rc->dirY * (mlx->rc->moveSpeed / 4);

    if (mlx->rc->map[newY][(int)mlx->rc->posX] != 1)
        mlx->rc->posY -= mlx->rc->dirX * mlx->rc->moveSpeed;
    else
        mlx->rc->posY += mlx->rc->dirX * (mlx->rc->moveSpeed / 4);
}

void	movecamleft(t_mlx *mlx)
{
	double oldDirX;
	double oldPlaneX;

	oldDirX = mlx->rc->dirX;
	mlx->rc->dirX = mlx->rc->dirX * cos(-mlx->rc->rotSpeed) - mlx->rc->dirY * sin(-mlx->rc->rotSpeed);
	mlx->rc->dirY = oldDirX * sin(-mlx->rc->rotSpeed) + mlx->rc->dirY * cos(-mlx->rc->rotSpeed);
	oldPlaneX = mlx->rc->planeX;
	mlx->rc->planeX = mlx->rc->planeX * cos(-mlx->rc->rotSpeed) - mlx->rc->planeY * sin(-mlx->rc->rotSpeed);
	mlx->rc->planeY = oldPlaneX * sin(-mlx->rc->rotSpeed) + mlx->rc->planeY * cos(-mlx->rc->rotSpeed);
}

void	movecamright(t_mlx *mlx)
{
	double oldDirX;
	double oldPlaneX;

	oldDirX = mlx->rc->dirX;
	mlx->rc->dirX = mlx->rc->dirX * cos(mlx->rc->rotSpeed) - mlx->rc->dirY * sin(mlx->rc->rotSpeed);
	mlx->rc->dirY = oldDirX * sin(mlx->rc->rotSpeed) + mlx->rc->dirY * cos(mlx->rc->rotSpeed);
	oldPlaneX = mlx->rc->planeX;
	mlx->rc->planeX = mlx->rc->planeX * cos(mlx->rc->rotSpeed) - mlx->rc->planeY * sin(mlx->rc->rotSpeed);
	mlx->rc->planeY = oldPlaneX * sin(mlx->rc->rotSpeed) + mlx->rc->planeY * cos(mlx->rc->rotSpeed);
}

int	moves(int key_code, t_mlx *mlx)
{
	if (key_code == leftarrow)
		return (movecamleft(mlx), raycast(mlx->rc, mlx), 0);
	if (key_code == rightarrow)
		return (movecamright(mlx), raycast(mlx->rc, mlx), 0);
	if (key_code == w)
		return (move_w(mlx), raycast(mlx->rc, mlx), 0);
	if (key_code == s)
		return (move_s(mlx), raycast(mlx->rc, mlx), 0);
	if (key_code == d)
		return (move_d(mlx), raycast(mlx->rc, mlx), 0);
	if (key_code == a)
		return (move_a(mlx), raycast(mlx->rc, mlx), 0);
	if (key_code == ESC)
		close_win(mlx);
	return (0);
}
