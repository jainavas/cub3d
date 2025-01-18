/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math0.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 18:39:37 by jainavas          #+#    #+#             */
/*   Updated: 2024/12/18 00:21:02 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int orients(t_map *vmap)
{
	if (vmap->orientation == 'N')
		return (vmap->dirpx = -1, vmap->dirpy = 0, 0);
	if (vmap->orientation == 'S')
		return (vmap->dirpx = 1, vmap->dirpy = 0, 0);
	if (vmap->orientation == 'E')
		return (vmap->dirpx = 0, vmap->dirpy = 1, 0);
	if (vmap->orientation == 'W')
		return (vmap->dirpx = 0, vmap->dirpy = -1, 0);
	return (1);
}

void	calcs(t_map *vmap)
{
	int		i;

	i = -1;
	vmap->planex = 0;
	vmap->planey = 0.66;
	while (++i < 480)
	{
		

	}
}
