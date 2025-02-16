/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imglisthandle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:47:39 by jainavas          #+#    #+#             */
/*   Updated: 2025/02/16 21:48:53 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_imgx	*imgnew(char *name)
{
	t_imgx	*new;

	new = ft_calloc(1, sizeof(t_imgx));
	new->name = ft_strdup(name);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_imgx	*imglast(t_imgx *lst)
{
	t_imgx	*tmp;

	tmp = lst;
	if (tmp)
		while (tmp->next)
			tmp = tmp->next;
	return (tmp);
}

void	imgadd_back(t_imgx **lst, t_imgx *new)
{
	t_imgx	*tmp;

	if (!*lst)
		*lst = new;
	else
	{
		tmp = imglast(*lst);
		new->next = NULL;
		tmp->next = new;
		new->prev = tmp;
	}
}

void	imgaddr(t_imgx *img, t_mlx *mlx, char *file)
{
	if (!img)
		return;
	img->i = mlx_xpm_file_to_image(mlx->mlx, file, &img->width, &img->height);
	if (!img->i)
		return;
	img->addr = mlx_get_data_addr(img->i, &img->bpp, \
		&img->line_len, &img->endian);
}

void	freeimgs(t_imgx **head, t_mlx *mlx)
{
	t_imgx	*aux;

	while (*head && mlx)
	{
		aux = (*head)->next;
		free((*head)->name);
		mlx_destroy_image(mlx->mlx, (*head)->i);
		free((*head));
		*head = aux;
	}
	free(mlx->win_img->name);
	mlx_destroy_image(mlx->mlx, mlx->win_img->i);
	free(mlx->win_img);
}

t_imgx	*imgsearch(char *tolook, t_imgx **head)
{
	t_imgx	*tmp;

	tmp = *head;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, tolook, ft_strlen(tolook)))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
