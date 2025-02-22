/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhiguera <mhiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 13:09:31 by mhiguera          #+#    #+#             */
/*   Updated: 2025/02/22 14:46:53 by mhiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	move_forward(t_mlx *mlx)
{
	if (mlx->rc->map[(int)(mlx->rc->pos_y)][(int)(mlx->rc->pos_x
			+ (mlx->rc->dir_x * mlx->rc->move_speed))] != 1)
		mlx->rc->pos_x += mlx->rc->dir_x * mlx->rc->move_speed;
	else
		mlx->rc->pos_x -= mlx->rc->dir_x * (mlx->rc->move_speed / 4);
	if (mlx->rc->map[(int)(mlx->rc->pos_y + mlx->rc->dir_y
			* mlx->rc->move_speed)][(int)(mlx->rc->pos_x)] != 1)
		mlx->rc->pos_y += mlx->rc->dir_y * mlx->rc->move_speed;
	else
		mlx->rc->pos_y -= mlx->rc->dir_y * (mlx->rc->move_speed / 4);
}

void	move_backward(t_mlx *mlx)
{
	if (mlx->rc->map[(int)(mlx->rc->pos_y)][(int)(mlx->rc->pos_x
			- mlx->rc->dir_x * mlx->rc->move_speed)] != 1)
		mlx->rc->pos_x -= mlx->rc->dir_x * mlx->rc->move_speed;
	else
		mlx->rc->pos_x += mlx->rc->dir_x * (mlx->rc->move_speed / 4);
	if (mlx->rc->map[(int)(mlx->rc->pos_y - mlx->rc->dir_y
			* mlx->rc->move_speed)][(int)(mlx->rc->pos_x)] != 1)
		mlx->rc->pos_y -= mlx->rc->dir_y * mlx->rc->move_speed;
	else
		mlx->rc->pos_y += mlx->rc->dir_y * (mlx->rc->move_speed / 4);
}

void	move_right(t_mlx *mlx)
{
	int	new_x;
	int	new_y;

	new_x = (int)(mlx->rc->pos_x - mlx->rc->dir_y * mlx->rc->move_speed);
	new_y = (int)(mlx->rc->pos_y + mlx->rc->dir_x * mlx->rc->move_speed);
	if (mlx->rc->map[(int)mlx->rc->pos_y][new_x] != 1)
		mlx->rc->pos_x -= mlx->rc->dir_y * mlx->rc->move_speed;
	else
		mlx->rc->pos_x += mlx->rc->dir_y * (mlx->rc->move_speed / 4);
	if (mlx->rc->map[new_y][(int)mlx->rc->pos_x] != 1)
		mlx->rc->pos_y += mlx->rc->dir_x * mlx->rc->move_speed;
	else
		mlx->rc->pos_y -= mlx->rc->dir_x * (mlx->rc->move_speed / 4);
}

void	move_left(t_mlx *mlx)
{
	int	new_x;
	int	new_y;

	new_x = (int)(mlx->rc->pos_x + mlx->rc->dir_y * mlx->rc->move_speed);
	new_y = (int)(mlx->rc->pos_y - mlx->rc->dir_x * mlx->rc->move_speed);
	if (mlx->rc->map[(int)mlx->rc->pos_y][new_x] != 1)
		mlx->rc->pos_x += mlx->rc->dir_y * mlx->rc->move_speed;
	else
		mlx->rc->pos_x -= mlx->rc->dir_y * (mlx->rc->move_speed / 4);
	if (mlx->rc->map[new_y][(int)mlx->rc->pos_x] != 1)
		mlx->rc->pos_y -= mlx->rc->dir_x * mlx->rc->move_speed;
	else
		mlx->rc->pos_y += mlx->rc->dir_x * (mlx->rc->move_speed / 4);
}

int	handle_movement(int key_code, t_mlx *mlx)
{
	if (key_code == leftarrow)
		return (rotate_camera_left(mlx), raycast(mlx->rc, mlx), 0);
	if (key_code == rightarrow)
		return (rotate_camera_right(mlx), raycast(mlx->rc, mlx), 0);
	if (key_code == w)
		return (move_forward(mlx), raycast(mlx->rc, mlx), 0);
	if (key_code == s)
		return (move_backward(mlx), raycast(mlx->rc, mlx), 0);
	if (key_code == d)
		return (move_right(mlx), raycast(mlx->rc, mlx), 0);
	if (key_code == a)
		return (move_left(mlx), raycast(mlx->rc, mlx), 0);
	if (key_code == ESC)
		close_window(mlx);
	return (0);
}
