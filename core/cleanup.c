/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhiguera <mhiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 13:08:27 by mhiguera          #+#    #+#             */
/*   Updated: 2025/02/22 14:02:22 by mhiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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

int	close_window(t_mlx *vars)
{
	free_images(vars->imgs, vars);
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
