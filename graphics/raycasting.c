/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhiguera <mhiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 13:08:44 by mhiguera          #+#    #+#             */
/*   Updated: 2025/02/22 16:02:02 by mhiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	calculate_ray(t_rayc *rc)
{
	if (rc->ray_dir_x < 0)
	{
		rc->step_x = -1;
		rc->side_dist_x = (rc->pos_x - rc->map_x) * rc->delta_dist_x;
	}
	else
	{
		rc->step_x = 1;
		rc->side_dist_x = (rc->map_x + 1.0 - rc->pos_x) * rc->delta_dist_x;
	}
	if (rc->ray_dir_y < 0)
	{
		rc->step_y = -1;
		rc->side_dist_y = (rc->pos_y - rc->map_y) * rc->delta_dist_y;
	}
	else
	{
		rc->step_y = 1;
		rc->side_dist_y = (rc->map_y + 1.0 - rc->pos_y) * rc->delta_dist_y;
	}
}

void	perform_dda(t_rayc *rc)
{
	while (rc->hit == 0)
	{
		if (rc->side_dist_x < rc->side_dist_y)
		{
			rc->side_dist_x += rc->delta_dist_x;
			rc->map_x += rc->step_x;
			rc->side = 0;
		}
		else
		{
			rc->side_dist_y += rc->delta_dist_y;
			rc->map_y += rc->step_y;
			rc->side = 1;
		}
		if (rc->map[rc->map_y][rc->map_x] == 1)
			rc->hit = 1;
	}
	if (rc->side == 0)
		rc->perp_wall_dist = (rc->map_x - rc->pos_x + (1 - rc->step_x) / 2)
			/ rc->ray_dir_x;
	else
		rc->perp_wall_dist = (rc->map_y - rc->pos_y + (1 - rc->step_y) / 2)
			/ rc->ray_dir_y;
}

void	calculate_wall_distance(t_rayc *rc)
{
	rc->line_height = (int)(rc->screen_height / rc->perp_wall_dist);
	rc->draw_start = -rc->line_height / 2 + rc->screen_height / 2;
	if (rc->draw_start < 0)
		rc->draw_start = 0;
	rc->draw_end = rc->line_height / 2 + rc->screen_height / 2;
	if (rc->draw_end >= rc->screen_height)
		rc->draw_end = rc->screen_height - 1;
}

void	calculate_texture_position(t_rayc *rc, t_mlx *mlx)
{
	t_imgx	*img;

	img = get_wall_texture(rc, mlx, rc->ray_dir_x, rc->ray_dir_y);
	if (rc->side == 0)
		rc->wall_x = rc->pos_y + rc->perp_wall_dist * rc->ray_dir_y;
	else
		rc->wall_x = rc->pos_x + rc->perp_wall_dist * rc->ray_dir_x;
	rc->wall_x -= floor(rc->wall_x);
	rc->tex_x = (int)(rc->wall_x * (double)img->width);
	if (rc->side == 0 && rc->ray_dir_x > 0)
		rc->tex_x = (double)img->width - rc->tex_x - 1;
	if (rc->side == 1 && rc->ray_dir_y < 0)
		rc->tex_x = (double)img->width - rc->tex_x - 1;
	rc->step = 1.0 * img->height / rc->line_height;
	rc->tex_pos = (rc->draw_start - rc->screen_height / 2 + rc->line_height / 2)
		* rc->step;
}

void	raycast(t_rayc *rc, t_mlx *mlx)
{
	int	x;

	x = -1;
	draw_background(rc, mlx);
	while (++x < rc->screen_width)
	{
		rc->camera_x = 2 * x / (double)rc->screen_width - 1;
		rc->ray_dir_x = rc->dir_x + rc->plane_x * rc->camera_x;
		rc->ray_dir_y = rc->dir_y + rc->plane_y * rc->camera_x;
		rc->map_x = (int)rc->pos_x;
		rc->map_y = (int)rc->pos_y;
		rc->delta_dist_x = fabs(1 / rc->ray_dir_x);
		rc->delta_dist_y = fabs(1 / rc->ray_dir_y);
		rc->hit = 0;
		calculate_ray(rc);
		perform_dda(rc);
		calculate_wall_distance(rc);
		calculate_texture_position(rc, mlx);
		draw_textured_line(rc, mlx, x,
			get_wall_texture(rc, mlx, rc->ray_dir_x, rc->ray_dir_y));
	}
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->win_img->i, 0, 0);
}
