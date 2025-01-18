/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:06:37 by jainavas          #+#    #+#             */
/*   Updated: 2024/12/17 18:07:30 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	findlongestline(t_map *vmap)
{
	int	i;
	int	res;

	i = -1;
	res = 0;
	while (vmap->map[++i])
		if (res < (int)ft_strlen(vmap->map[i]))
			res = (int)ft_strlen(vmap->map[i]);
	vmap->numwd = res;
}

void	doublechartodoubleint(t_map *vmap)
{
	int		i;
	int		j;

	vmap->intmap = ft_calloc(vmap->numlines + 2, sizeof(int *));
	i = -1;
	while (++i < vmap->numlines)
		vmap->intmap[i] = ft_calloc(vmap->numwd, sizeof(int));
	vmap->intmap[vmap->numlines] = NULL;
	i = -1;
	while (vmap->map[++i])
	{
		j = -1;
		while (vmap->map[i][++j] != '\0' && vmap->map[i][j] != '\n')
		{
			if (vmap->map[i][j] == ' ')
				vmap->intmap[i][j] = 9;
			else if (ft_isalpha(vmap->map[i][j]))
				vmap->intmap[i][j] = 5;
			else
				vmap->intmap[i][j] = ((int)vmap->map[i][j] - 48);
		}
	}
}