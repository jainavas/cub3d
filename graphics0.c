/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:50:11 by jainavas          #+#    #+#             */
/*   Updated: 2025/02/16 21:48:27 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	initmlxassets(t_mlx *mlx, t_map *vmap)
{
	char	*tmp;

	imgadd_back(mlx->imgs, imgnew("black"));
	imgaddr(imglast(*mlx->imgs), mlx, "./text/black.xpm");
	imgadd_back(mlx->imgs, imgnew("scope"));
	imgaddr(imglast(*mlx->imgs), mlx, "./text/scope.xpm");
	mlx->win_img = imgnew("win");
	mlx->win_img->i = mlx_new_image(mlx->mlx, WINW, WINH);
	mlx->win_img->addr = mlx_get_data_addr(mlx->win_img->i, &mlx->win_img->bpp, &mlx->win_img->line_len, &mlx->win_img->endian);
	my_mlx_area_put(mlx->win_img, newvector(0,0), newvector(WINW, WINH), 0x0000FF00);
	tmp = ft_strjoin(vmap->pathnorth, ".xpm");
	imgadd_back(mlx->imgs, imgnew("north"));
	imgaddr(imglast(*mlx->imgs), mlx, tmp);
	free(tmp);
	tmp = ft_strjoin(vmap->pathsouth, ".xpm");
	imgadd_back(mlx->imgs, imgnew("south"));
	imgaddr(imglast(*mlx->imgs), mlx, tmp);
	free(tmp);
	tmp = ft_strjoin(vmap->patheast, ".xpm");
	imgadd_back(mlx->imgs, imgnew("east"));
	imgaddr(imglast(*mlx->imgs), mlx, tmp);
	free(tmp);
	tmp = ft_strjoin(vmap->pathwest, ".xpm");
	imgadd_back(mlx->imgs, imgnew("west"));
	imgaddr(imglast(*mlx->imgs), mlx, tmp);
	free(tmp);
}

int	get_dist_color(int color, float ds, int tr)
{
	t_color	c;
	float	dif;

	if (ds < 0)
		ds = 0;
	dif = powf(1.14, ds / 7.5);
	c = new_rgbt(color);
	if (tr)
		c.t -= dif;
	else
		c.t = 256;
	c.r -= dif;
	c.g -= dif;
	c.b -= dif;
	if (c. t < 0)
		c.t = 0;
	if (c.r < 0)
		c.r = 0;
	if (c.g < 0)
		c.g = 0;
	if (c.b < 0)
		c.b = 0;
	return (new_trgb(c));
}

int	new_trgb(t_color c)
{
	return (c.t << 24 | c.r << 16 | c.g << 8 | c.b);
}

t_color	new_rgbt(int col)
{
	t_color	c;

	c.t = (col >> 24) & 0xFF;
	c.r = (col >> 16) & 0xFF;
	c.g = (col >> 8) & 0xFF;
	c.b = col & 0xFF;
	return (c);
}

void	draw_texture(t_mlx *mlx, t_imgx *i, int ray_count, int wall_height)
{
	float	dy;
	float	ds;
	float	cy[2];
	int		z;
	int		color;

	dy = ((float)wall_height * 2) / (float)i->height;
	ds = ((float)WINH / 2) - (float)wall_height;
	cy[1] = ds;
	z = -1;
	while (++z < i->height)
	{
		color = get_tex_color(mlx->vmap, i, z);
		color = get_dist_color(color, ds, 0);
		cy[0] = cy[1];
		while (cy[0] < cy[1] + dy)
		{
			if (cy[0] >= 0 && cy[0] < (float)WINH)
				my_mlx_pixel_put(mlx->win_img, ray_count, (int)cy[0], color);
			cy[0]++;
		}
		cy[1] += dy;
	}
}

void	drawall(t_mlx *mlx, int ray_count, float dis)
{
	int		wall_height;
	float	ds;
	int		j;

	wall_height = (int)(WINH / (1.5 * dis));
	ds = ((float)WINH / 2) - (float)wall_height;
	j = -1;
	while (++j < WINH)
	{
		if (j < ds)
			my_mlx_pixel_put(mlx->win_img, ray_count, j, \
				get_dist_color(new_trgb(mlx->vmap->ceicolor), j, 0));
		else if (j >= (WINH / 2) + wall_height)
			my_mlx_pixel_put(mlx->win_img, ray_count, j, \
				get_dist_color(new_trgb(mlx->vmap->flocolor), WINH - j, 0));
	}
	draw_texture(mlx, get_texture(mlx->vmap, mlx->imgs), ray_count, wall_height);
}

int	close_win(t_mlx *vars)
{
	freeimgs(vars->imgs, vars);
	mlx_destroy_window(vars->mlx, vars->mlx_win);
	mlx_destroy_display(vars->mlx);
	freedoublepointer(vars->vmap->map);
	freedp(vars->vmap->intmap);
	free(vars->vmap->patheast);
	free(vars->vmap->pathwest);
	free(vars->vmap->pathnorth);
	free(vars->vmap->pathsouth);
	free(vars->vmap->ceilingcolor);
	free(vars->vmap->floorcolor);
	free(vars->vmap);
	free(vars->imgs);
	free(vars->mlx);
	free(vars);
	exit(0);
	return (0);
}
