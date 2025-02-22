/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhiguera <mhiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 13:08:57 by mhiguera          #+#    #+#             */
/*   Updated: 2025/02/22 14:31:02 by mhiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_textured_line(t_rayc *rc, t_mlx *mlx, int x, t_imgx *img)
{
	int	y;
	int	tex_y;
	int	color;
	int	pixel;

	y = rc->draw_start - 1;
	while (++y < rc->draw_end)
	{
		tex_y = (int)rc->tex_pos & (img->height - 1);
		rc->tex_pos += rc->step;
		color = *(int *)(img->addr + (tex_y * img->line_len + rc->tex_x
					* (img->bpp / 8)));
		pixel = (y * mlx->win_img->line_len) + (x * (mlx->win_img->bpp / 8));
		*(unsigned int *)(mlx->win_img->addr + pixel) = color;
	}
}

t_imgx	*get_wall_texture(t_rayc *rc, t_mlx *mlx, double ray_dir_x,
				double ray_dir_y)
{
	if (rc->side == 0)
	{
		if (ray_dir_x > 0)
			return (search_image("south", mlx->imgs));
		else
			return (search_image("north", mlx->imgs));
	}
	else
	{
		if (ray_dir_y > 0)
			return (search_image("west", mlx->imgs));
		else
			return (search_image("east", mlx->imgs));
	}
}

int	set_color(t_color c)
{
	return (c.t << 24 | c.r << 16 | c.g << 8 | c.b);
}

t_color	get_color(int col)
{
	t_color	c;

	c.t = (col >> 24) & 0xFF;
	c.r = (col >> 16) & 0xFF;
	c.g = (col >> 8) & 0xFF;
	c.b = col & 0xFF;
	return (c);
}
