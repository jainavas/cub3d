/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:50:11 by jainavas          #+#    #+#             */
/*   Updated: 2025/02/19 15:59:22 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	initmlxassets(t_mlx *mlx, t_map *vmap)
{
	char	*tmp;

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

int	close_win(t_mlx *vars)
{
	freeimgs(vars->imgs, vars);
	mlx_destroy_window(vars->mlx, vars->mlx_win);
	mlx_destroy_display(vars->mlx);
	freedoublepointer(vars->vmap->map);
	freedp(vars->rc->map);
	free(vars->vmap->patheast);
	free(vars->vmap->pathwest);
	free(vars->vmap->pathnorth);
	free(vars->vmap->pathsouth);
	free(vars->vmap->ceilingcolor);
	free(vars->vmap->floorcolor);
	free(vars->vmap);
	free(vars->imgs);
	free(vars->rc);
	free(vars->mlx);
	free(vars);
	exit(0);
	return (0);
}
