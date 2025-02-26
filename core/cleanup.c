/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 13:08:27 by mhiguera          #+#    #+#             */
/*   Updated: 2025/02/26 20:22:35 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	isunvalidchar(int j)
{
	if (j == '0' || j == '1' || j == 'N' || j == 'S'
		|| j == 'E' || j == 'W' || j == ' ' || j == '\n' || j == '\t')
		return (0);
	return (1);
}

void	free_images(t_imgx **head, t_mlx *mlx)
{
	t_imgx	*aux;

	while (*head && mlx)
	{
		aux = (*head)->next;
		free((*head)->name);
		if ((*head)->i)
			mlx_destroy_image(mlx->mlx, (*head)->i);
		free((*head));
		*head = aux;
	}
	free(mlx->win_img->name);
	mlx_destroy_image(mlx->mlx, mlx->win_img->i);
	free(mlx->win_img);
}

void	freepaths(t_map *vmap)
{
	if (vmap->pathnorth)
		free(vmap->pathnorth);
	if (vmap->pathsouth)
		free(vmap->pathsouth);
	if (vmap->patheast)
		free(vmap->patheast);
	if (vmap->pathwest)
		free(vmap->pathwest);
	if (vmap->ceilingcolor)
		free(vmap->ceilingcolor);
	if (vmap->floorcolor)
		free(vmap->floorcolor);
}

int	close_window(t_mlx *vars)
{
	free_images(vars->imgs, vars);
	mlx_destroy_window(vars->mlx, vars->mlx_win);
	mlx_destroy_display(vars->mlx);
	freedoublepointer(vars->vmap->map);
	freedp(vars->rc->map);
	freepaths(vars->vmap);
	free(vars->vmap);
	free(vars->imgs);
	free(vars->rc);
	free(vars->mlx);
	free(vars);
	exit(0);
	return (0);
}
