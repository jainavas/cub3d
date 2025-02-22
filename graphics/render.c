/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhiguera <mhiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 13:08:51 by mhiguera          #+#    #+#             */
/*   Updated: 2025/02/22 16:02:30 by mhiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	put_pixel(t_imgx *data, int x, int y, int color)
{
	char	*dst;

	if (!data || !data->addr)
		return ;
	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

unsigned int	get_pixel(t_imgx *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	return (*(unsigned int *)dst);
}

void	draw_area(t_imgx *d, t_vector p, t_vector dim, int c)
{
	int	x;
	int	y;

	y = -1;
	while (++y < dim.y)
	{
		x = -1;
		while (++x < dim.x)
			put_pixel(d, p.x + x, p.y + y, c);
	}
}

void	draw_half(t_rayc *rc, t_mlx *mlx, int start_y, int end_y)
{
	int		x;
	int		y;
	int		pixel;
	t_color	color;

	y = start_y - 1;
	if (start_y < rc->screen_height / 2)
		color = mlx->vmap->ceicolor;
	else
		color = mlx->vmap->flocolor;
	while (++y < end_y)
	{
		x = -1;
		while (++x < rc->screen_width)
		{
			pixel = y * mlx->win_img->line_len + x * mlx->win_img->bpp / 8;
			*(unsigned int *)(mlx->win_img->addr + pixel)
				= set_color(color);
		}
	}
}

// Draws sky and floor, first half top (sky) then half bottom (floor)
void	draw_background(t_rayc *rc, t_mlx *mlx)
{
	draw_half(rc, mlx, 0, rc->screen_height / 2);
	draw_half(rc, mlx, rc->screen_height / 2, rc->screen_height);
}
