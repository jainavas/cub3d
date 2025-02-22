/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhiguera <mhiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 13:10:01 by mhiguera          #+#    #+#             */
/*   Updated: 2025/02/22 15:37:51 by mhiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

t_imgx	*create_new_image(char *name)
{
	t_imgx	*new;

	new = ft_calloc(1, sizeof(t_imgx));
	new->name = ft_strdup(name);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_imgx	*get_last_image(t_imgx *lst)
{
	t_imgx	*tmp;

	tmp = lst;
	if (tmp)
		while (tmp->next)
			tmp = tmp->next;
	return (tmp);
}

void	add_image_back(t_imgx **lst, t_imgx *new)
{
	t_imgx	*tmp;

	if (!*lst)
		*lst = new;
	else
	{
		tmp = get_last_image(*lst);
		new->next = NULL;
		tmp->next = new;
		new->prev = tmp;
	}
}

void	set_image_address(t_imgx *img, t_mlx *mlx, char *file)
{
	if (!img)
		return ;
	img->i = mlx_xpm_file_to_image(mlx->mlx, file, &img->width, &img->height);
	if (!img->i)
		return (ft_putstr_fd("Error\nInvalid texture file\n", 1),
			ft_putstr_fd(file, 1), exit(1), (void)0);
	img->addr = mlx_get_data_addr(img->i, &img->bpp, \
		&img->line_len, &img->endian);
}

t_imgx	*search_image(char *tolook, t_imgx **head)
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
