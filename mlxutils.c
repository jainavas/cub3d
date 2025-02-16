/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxutils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 18:58:09 by jainavas          #+#    #+#             */
/*   Updated: 2025/02/16 21:21:06 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_imgx *data, int x, int y, int color)
{
	char	*dst;

	if (!data || !data->addr)
		return;
	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

unsigned int	my_mlx_pixel_get(t_imgx *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	return (*(unsigned int *)dst);
}

void	my_mlx_area_put(t_imgx *d, t_vector p, t_vector dim, int c)
{
	int	x;
	int	y;

	y = -1;
	while (++y < dim.y)
	{
		x = -1;
		while (++x < dim.x)
			my_mlx_pixel_put(d, p.x + x, p.y + y, c);
	}
}

t_vector	newvector(int x, int y)
{
	t_vector h;

	h.x = x;
	h.y = y;
	return (h);
}

void	mlx_img_to_img(int p[2], t_imgx img[2], int c1)
{
	int	xy[2];
	int	color;

	xy[1] = -1;
	while (++xy[1] < img[0].height)
	{
		xy[0] = -1;
		while (++xy[0] < img[0].width)
		{
			if (xy[0] + p[0] >= 0 && xy[1] + p[1] >= 0)
			{
				color = my_mlx_pixel_get(&img[0], xy[0], xy[1]);
				if (color != c1)
					my_mlx_pixel_put(&img[1], xy[0] + p[0], \
						xy[1] + p[1], color);
			}
		}
	}
}

t_imgx	*get_texture(t_map *vmap, t_imgx **img)
{
	t_imgx	*i;
	float	ray_cos;
	float	ray_sin;

	ray_cos = vmap->ray.cos;
	if (ray_cos < 0)
		ray_cos = -ray_cos;
	ray_sin = vmap->ray.sin;
	if (ray_sin < 0)
		ray_sin = -ray_sin;
	i = imgsearch("black", img);
	if (vmap->map[(int)(vmap->ray.y - ray_sin)][(int)vmap->ray.x] != '1')
		i = imgsearch("north", img);
	else if (vmap->map[(int)(vmap->ray.y + ray_sin)][(int)vmap->ray.x] != '1')
		i = imgsearch("south", img);
	else if (vmap->map[(int)vmap->ray.y][(int)(vmap->ray.x + ray_cos)] != '1')
		i = imgsearch("east", img);
	else if (vmap->map[(int)vmap->ray.y][(int)(vmap->ray.x - ray_cos)] != '1')
		i = imgsearch("west", img);
	return (i);
}

int	get_tex_color(t_map *vmap, t_imgx *i, int z)
{
	int	color;

	color = 0x00000000;
	if (vmap->map[(int)vmap->ray.y][(int)vmap->ray.x] == '1')
		color = my_mlx_pixel_get(i, (int)(i->width * (vmap->ray.x + vmap->ray.y)) \
			% i->width, z);
	else if (vmap->map[(int)vmap->ray.y][(int)vmap->ray.x] == 'c')
		color = 0x00FF0000;
	return (color);
}

void	redraw_elem(t_mlx *mlx, t_imgx img, int x, int y)
{
	int		p[2];
	t_imgx	images[2];

	p[0] = x;
	p[1] = y;
	images[0] = img;
	images[1] = *mlx->win_img;
	mlx_img_to_img(p, images, 0xFF000000);
}

