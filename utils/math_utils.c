/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhiguera <mhiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 13:10:05 by mhiguera          #+#    #+#             */
/*   Updated: 2025/02/22 15:46:56 by mhiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

double	degrees_to_radians(double degrees)
{
	return (degrees * (PI / 180.0));
}

t_vector	create_vector(int x, int y)
{
	t_vector	h;

	h.x = x;
	h.y = y;
	return (h);
}

void	rotate_camera_left(t_mlx *mlx)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = mlx->rc->dir_x;
	mlx->rc->dir_x = mlx->rc->dir_x * cos(-mlx->rc->rot_speed) - mlx->rc->dir_y
		* sin(-mlx->rc->rot_speed);
	mlx->rc->dir_y = old_dir_x * sin(-mlx->rc->rot_speed) + mlx->rc->dir_y
		* cos(-mlx->rc->rot_speed);
	old_plane_x = mlx->rc->plane_x;
	mlx->rc->plane_x = mlx->rc->plane_x * cos(-mlx->rc->rot_speed)
		- mlx->rc->plane_y * sin(-mlx->rc->rot_speed);
	mlx->rc->plane_y = old_plane_x * sin(-mlx->rc->rot_speed) + mlx->rc->plane_y
		* cos(-mlx->rc->rot_speed);
}

void	rotate_camera_right(t_mlx *mlx)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = mlx->rc->dir_x;
	mlx->rc->dir_x = mlx->rc->dir_x * cos(mlx->rc->rot_speed)
		- mlx->rc->dir_y * sin(mlx->rc->rot_speed);
	mlx->rc->dir_y = old_dir_x * sin(mlx->rc->rot_speed)
		+ mlx->rc->dir_y * cos(mlx->rc->rot_speed);
	old_plane_x = mlx->rc->plane_x;
	mlx->rc->plane_x = mlx->rc->plane_x * cos(mlx->rc->rot_speed)
		- mlx->rc->plane_y * sin(mlx->rc->rot_speed);
	mlx->rc->plane_y = old_plane_x * sin(mlx->rc->rot_speed)
		+ mlx->rc->plane_y * cos(mlx->rc->rot_speed);
}
